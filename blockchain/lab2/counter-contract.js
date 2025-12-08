const { TonClient, WalletContractV4, internal, toNano } = require('@ton/ton');
const { Address, Cell, beginCell } = require('@ton/core');

function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function retryWithDelay(fn, maxRetries = 3, delayMs = 2000) {
    for (let i = 0; i < maxRetries; i++) {
        try {
            return await fn();
        } catch (error) {
            if (error.response?.status === 429 && i < maxRetries - 1) {
                console.log(`Rate limited. Retrying in ${delayMs}ms... (attempt ${i + 1}/${maxRetries})`);
                await delay(delayMs * (i + 1));
                continue;
            }
            throw error;
        }
    }
}

async function incrementOnly() {
    console.log('Starting increment only...');
    
    // Ваш API ключ
    const API_KEY = '4c105d722fcb20ba84694647e086244fdc4270b07be527c3568dcc725fff2195';
    
    const client = new TonClient({
        endpoint: 'https://testnet.toncenter.com/api/v2/jsonRPC',
        apiKey: API_KEY // Ключ добавлен!
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

    const fs = require('fs');
    if (!fs.existsSync('contract-address.txt')) {
        console.log('contract-address.txt not found! Deploy contract first.');
        return;
    }
    
    const contractAddress = Address.parse(fs.readFileSync('contract-address.txt', 'utf8').trim());
    console.log('Contract address:', contractAddress.toString());

    console.log('Initial delay before starting...');
    await delay(5000); // Уменьшил начальную задержку

    try {
        console.log('Checking balance...');
        const balance = await retryWithDelay(() => client.getBalance(deployAddress));
        console.log('Balance:', Number(balance) / 1000000000, 'TON');

        if (balance < toNano('0.1')) {
            console.log('Not enough balance! Minimum 0.1 TON required');
            return;
        }

        const contract = client.open(wallet);
        
        // Увеличиваем газ для надежности
        const incrementMessage = internal({
            value: toNano('0.08'), // Увеличено с 0.05
            to: contractAddress,
            bounce: false,
            body: beginCell()
                .storeUint(1, 32)  // op = 1 для increment
                .storeUint(0, 64)  // query_id
                .endCell()
        });

        console.log('Getting seqno...');
        await delay(2000);
        
        const seqno = await retryWithDelay(() => contract.getSeqno());
        console.log('Current seqno:', seqno);
        
        const incrementTransfer = contract.createTransfer({
            secretKey: deployPrivateKey,
            seqno: seqno,
            messages: [incrementMessage]
        });

        console.log('Sending transaction...');
        await delay(2000);
        
        // Отправляем с обработкой ответа
        try {
            const result = await retryWithDelay(() => contract.send(incrementTransfer), 3, 2000);
            console.log(' Transaction sent successfully');
            console.log('Result:', result);
            
            if (result && typeof result === 'object') {
                console.log('Transaction hash available in result object');
            }
        } catch (sendError) {
            console.error(' Send failed:', sendError.message);
            // Продолжаем - иногда транзакция все равно проходит
        }
        
        // Проверяем, изменился ли seqno
        console.log('Checking if transaction was processed...');
        await delay(10000); // Ждем 10 секунд
        
        const newSeqno = await retryWithDelay(() => contract.getSeqno());
        console.log('New seqno after tx:', newSeqno);
        
        if (newSeqno > seqno) {
            console.log(' Transaction confirmed! Seqno increased from', seqno, 'to', newSeqno);
        } else {
            console.log('  Seqno not changed. Transaction might be pending or failed');
        }
        
        // Проверяем состояние контракта
        console.log('Checking contract state...');
        await delay(3000);
        
        const contractState = await retryWithDelay(() => client.getContractState(contractAddress));
        console.log('📊 Contract State:');
        console.log('- Status:', contractState.state);
        console.log('- Balance:', Number(contractState.balance) / 1000000000, 'TON');
        console.log('- Last transaction LT:', contractState.lastTransaction.lt);
        console.log('- Timestamp:', new Date(contractState.timestampt * 1000).toLocaleString());
        
        // Читаем данные контракта (значение счетчика)
        console.log('\nReading counter value...');
        try {
            // Попробуем прочитать данные контракта
            const contractData = contractState.data;
            if (contractData && contractData.length >= 24) {
                // Последние 8 байт - это счетчик (uint64 в little-endian)
                const counterBytes = contractData.slice(contractData.length - 8);
                const counterValue = counterBytes.readBigUInt64LE(0);
                console.log(' Counter value:', counterValue.toString());
            } else {
                console.log('Could not parse counter value from contract data');
            }
        } catch (parseError) {
            console.log('Error reading counter:', parseError.message);
        }
        
    } catch (error) {
        console.error(' Increment failed:', error.message);
        if (error.response) {
            console.error('Status:', error.response.status);
            console.error('Response data:', error.response.data);
        }
    }
    
    console.log('\n Check transactions in explorer:');
    console.log(`Wallet: https://testnet.tonviewer.com/EQCWDZBEwVWkpVRRYPjCfDvTAYf52M2xDu_kue2uE0GrMAWa`);
    console.log(`Contract: https://testnet.tonviewer.com/EQBojskVWht8kp9UNIXdNbyWm1IVBUnzDn3BKh2CqxAEtHnN`);
}

// Запуск
console.log('Script starting in 3 seconds...');
setTimeout(() => {
    incrementOnly();
}, 3000);
