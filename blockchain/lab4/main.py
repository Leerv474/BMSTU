import json
from tonsdk.contract.wallet import WalletVersionEnum, Wallets
from tonsdk.contract.token.nft import NFTCollection, NFTItem

# --- Load wallet from JSON ---
def load_wallet_from_json(filename):
    with open(filename) as f:
        data = json.load(f)
    mnemonics = data["mnemonics"]
    _, _, _, wallet = Wallets.from_mnemonics(
        mnemonics, WalletVersionEnum.v4r2, 0
    )
    return wallet

wallet = load_wallet_from_json("wallet1.json")
wallet_address = wallet.address.to_string(True, True, True)

import asyncio
from tonsdk.utils import to_nano, Address
from tonsdk.contract.token.nft import NFTCollection, NFTItem
from pytonlib import TonlibClient
import requests
from pathlib import Path

async def get_client():
    url = 'https://ton.org/testnet-global.config.json'
    config = requests.get(url).json()
    keystore_dir = '/tmp/ton_keystore'
    Path(keystore_dir).mkdir(parents=True, exist_ok=True)
    client = TonlibClient(ls_index=2, config=config, keystore=keystore_dir, tonlib_timeout=10)
    await client.init()
    return client

async def get_seqno(client: TonlibClient, address: str):
    data = await client.raw_run_method(method='seqno', stack_data=[], address=address)
    return int(data['stack'][0][1], 16)

def create_collection():
    royalty_base = 1000
    royalty_factor = 55
    NFT_ITEM_CODE_HEX = "b5ee9c7201010401003e000114ff00f4a413f4bcf2c80b0102016202030202cc04050015a70f605da89a1f401f481f481a9a30201ce06070201280a0b02f70831c02497c138007434c0c05c6c2544d7c0fc07783e903e900c7e800c5c75c87e800c7e800c1cea6d0000b4c7c076cf16cc8d0d0d09208403e29fa96ea68c1b088d978c4408fc06b809208405e351466ea6cc1b08978c840910c03c06f80dd6cda0841657c1ef2ea7c09c6c3cb4b01408eebcb8b1807c073817c160080900113e910c30003cb85360005c804ff833206e953080b1f833de206ef2d29ad0d30731d3ffd3fff404d307d430d0fa00fa00"
    assert all(c in '0123456789abcdefABCDEF' for c in NFT_ITEM_CODE_HEX), "Невалидный hex в коде NFT Item!"
    print("Код валиден, длина:", len(NFT_ITEM_CODE_HEX))
    collection = NFTCollection(
        royalty_base=royalty_base,
        royalty_factor=royalty_factor,
        royalty_address=Address(wallet_address),  # Или другой адрес для роялти
        owner_address=Address(wallet_address),
        collection_content_uri='https://s.getgems.io/nft/b/c/62fba50217c3fe3cbaad9e7f/meta.json',
        nft_item_content_base_uri='https://s.getgems.io/nft/b/c/62fba50217c3fe3cbaad9e7f/',
        nft_item_code_hex=NFT_ITEM_CODE_HEX
    )
    return collection

async def deploy_collection(collection):
    client = await get_client()
    state_init = collection.create_state_init()['state_init']
    seqno = await get_seqno(client, wallet_address)
    query = wallet.create_transfer_message(
        to_addr=collection.address.to_string(),
        amount=to_nano(0.05, 'ton'),  # Комиссия для деплоя
        seqno=seqno,
        state_init=state_init
    )
    await client.raw_send_message(query['message'].to_boc(False))
    print(f"Адрес коллекции: {collection.address.to_string(True, True, True)}")

if __name__ == '__main__':
    collection = create_collection()
    asyncio.run(deploy_collection(collection))
