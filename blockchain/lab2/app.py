import asyncio
import aiohttp
import json
from tonsdk.contract.wallet import Wallets, WalletVersionEnum
from tonsdk.crypto import mnemonic_new
from pytonlib import TonlibClient
from tonsdk.utils import to_nano


mnemonic, pub_key, priv_key, wallet= Wallets.create(version=WalletVersionEnum.v3r2,workchain=0)

print("Mnemonic: ", mnemonic)
print("Wallet address: ", wallet.address.to_string(True, True, True))


async def load_config():
    url = "https://ton-blockchain.github.io/testnet-global.config.json"
    async with aiohttp.ClientSession() as session:
        async with session.get(url) as resp:
            return await resp.json()

async def init_client():
    client = TonlibClient(
        ls_index = 0,
        config='https://ton-blockchain.github.io/testnet-global.config.json',  # конфиг для testnet
        keystore='ton_keystore',
        # tonlib_path = "./tonlibjson/libtonlibjson.x86_64.so"
    )
    await client.init()
    return client

client = asyncio.run(init_client())

deploy_msg = wallet.create_init_external_message()

boc = deploy_msg["message"].to_boc(False)

result = asyncio.run(client.send_message(boc))
print("Deploy result: ", result)

addr = wallet.address.to_string(True, True, True)
balance = asyncio.run(client.get_account_balance(addr))
print("Balance: ", balance)

transfer = wallet.create_transfer_message(
    to_addr = 'EQC...',
    amount = to_nano(0.1, 'ton'),
    seqno = 1,
    payload = "Hello from tonsdk",
    state_init = None
)

boc = transfer["message"].to_boc(False)

result = asyncio.run(client.send_message(boc))
print("Send result:", result)
