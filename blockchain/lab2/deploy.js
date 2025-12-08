const { TonClient, WalletContractV4, internal, toNano } = require('@ton/ton');
const { Address, Cell, beginCell } = require('@ton/core');
const { compile } = require('@ton/blueprint'); // Нужен для компиляции

function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function deploy() {
    console.log('Starting deployment...');
    
    const client = new TonClient({
        endpoint: 'https://testnet.toncenter.com/api/v2/jsonRPC',
       
    });

    const deployPrivateKeyHex = 'b01713898223fc5a52dfc044d94dad72093956d57206b6bc65107932edc69a53557742e502f9ffbc70e671c623c2f4a303050e305197a0926716102ddbd43490';
    const deployPrivateKey = Buffer.from(deployPrivateKeyHex, 'hex');
    const publicKey = deployPrivateKey.subarray(32, 64);
    
    const wallet = WalletContractV4.create({ 
        workchain: 0, 
        publicKey: publicKey
    });
    
    const deployAddress = wallet.address;
    console.log('Deploy address:', deployAddress.toString());

    await delay(5000);

    try {
        const balance = await client.getBalance(deployAddress);
        console.log('Balance:', Number(balance) / 1000000000, 'TON');

        if (balance < toNano('0.3')) {
            console.log('Not enough balance! Need at least 0.3 TON');
            return;
        }

        const fs = require('fs');
        const path = require('path');
        
        let codeCell = Cell.EMPTY;
        let dataCell = Cell.EMPTY; 
        
        const buildPath = path.join(__dirname, 'build', 'counter.compiled.json');
        
        if (fs.existsSync(buildPath)) {
            const compiled = JSON.parse(fs.readFileSync(buildPath, 'utf8'));
            codeCell = Cell.fromBoc(Buffer.from(compiled.hex, 'hex'))[0];
            dataCell = beginCell().storeUint(0, 64).endCell();
            console.log('Loaded compiled contract code');
        } else {
            console.log('Using minimal test contract');
            
            const minimalCode = 'B5EE9C72410101010044000084FF0020DDA4F260810200D71820D70B1FED44D0D31FD3FFD15112BAF2A122F901541044F910F2A2F80001D31F3120D74A96D307D402FB00DED1A4C8CB1FCBFFC9ED5441FDF089';
            codeCell = Cell.fromBoc(Buffer.from(minimalCode, 'hex'))[0];
            
            dataCell = beginCell().storeUint(0, 64).endCell();
        }
        
        const stateInit = beginCell()
            .storeBit(0)      
            .storeBit(0)     
            .storeBit(1)    
            .storeRef(codeCell)
            .storeBit(1)   
            .storeRef(dataCell)
            .storeBit(0)  
            .endCell();

        const contractAddress = new Address(0, stateInit.hash());
        console.log('Contract address:', contractAddress.toString());

        const contract = client.open(wallet);
        
        const deployMessage = internal({
            value: toNano('0.1'), 
            to: contractAddress,
            bounce: false, 
            init: { 
                code: codeCell,
                data: dataCell
            },
            body: beginCell()
                .storeUint(0, 32) 
                .storeUint(0, 64)
                .endCell()
        });

        await delay(3000);
        
        const seqno = await contract.getSeqno();
        console.log('Current seqno:', seqno);
        
        const transfer = contract.createTransfer({
            secretKey: deployPrivateKey,
            seqno: seqno,
            messages: [deployMessage]
        });

        await delay(3000);
        
        await contract.send(transfer);
        
        console.log('\n Transaction sent! Waiting for confirmation...');
        
        await delay(30000);
        
        const contractState = await client.getContractState(contractAddress);
        console.log('\n Contract state check:');
        console.log('- State:', contractState.state);
        console.log('- Balance:', Number(contractState.balance) / 1000000000, 'TON');
        console.log('- Has code:', !!contractState.code);
        console.log('- Has data:', !!contractState.data);
        
        if (contractState.state === 'active') {
            console.log('\n ✓ Contract deployed successfully!');
            
            const fs = require('fs');
            fs.writeFileSync('contract-address.txt', contractAddress.toString());
            console.log('Address saved to contract-address.txt');
        } else {
            console.log('\n ✗ Contract deployment failed!');
        }
        
    } catch (error) {
        console.error('Deployment failed:', error.message);
        if (error.response?.data) {
            console.error('Error details:', error.response.data);
        }
    }
}

deploy();
