import json
from tonsdk.contract.wallet import WalletVersionEnum, Wallets
from tonsdk.contract.token.nft import NFTCollection, NFTItem
from tonsdk.boc import Cell


item_content_uri = "https://puzzlemania-154aa.kxcdn.com/products/2024/puzzle-schmidt-1000-pieces-random-galaxy.webp"
nft_item_code_hex = ""
# --- Load wallet from JSON ---
def load_wallet_from_json(filename):
    with open(filename) as f:
        data = json.load(f)
    mnemonics = data["mnemonics"]
    _, _, _, wallet = Wallets.from_mnemonics(
        mnemonics, WalletVersionEnum.v3r2, 0
    )
    return wallet

wallet = load_wallet_from_json("wallet1.json")
wallet_address = wallet.address.to_string(True, True, True)

import asyncio
from tonsdk.utils import to_nano, Address
from tonsdk.contract.token.nft import NFTCollection, NFTItem
from pytonlib import TonlibClient, TonlibNoResponse
import requests
from pathlib import Path

async def get_client():
    url = 'https://ton.org/testnet-global.config.json'
    config = requests.get(url).json()
    keystore_dir = '/tmp/ton_keystore'
    Path(keystore_dir).mkdir(parents=True, exist_ok=True)
    client = TonlibClient(ls_index=7, config=config, keystore=keystore_dir, tonlib_timeout=10)
    await client.init()
    return client

async def get_seqno(client: TonlibClient, address: str):
    data = await client.raw_run_method(method='seqno', stack_data=[], address=address)
    return int(data['stack'][0][1], 16)


async def get_seqno_with_retry(client, address, retries=3):
    for retry in range(retries):
        try:
            return await get_seqno(client, address)
        except TonlibNoResponse:
            print("attempt %d failed\ntrying again...", retry)
            await asyncio.sleep(5)
    raise RuntimeError("Failed to get seqno after retries")

def create_collection():
    royalty_base = 1000
    royalty_factor = 55

    from pathlib import Path

    boc_bytes = Path("nft-item-output.boc").read_bytes()
    nft_item_code_hex = boc_bytes.hex()
    assert len(nft_item_code_hex) % 2 == 0
    assert all(c in '0123456789abcdefABCDEF' for c in nft_item_code_hex), "Невалидный hex в коде NFT Item!"
    print("Код валиден, длина:", len(nft_item_code_hex))
    collection = NFTCollection(
        royalty_base=royalty_base,
        royalty_factor=royalty_factor,
        royalty_address=Address(wallet_address),  # Или другой адрес для роялти
        owner_address=Address(wallet_address),
        collection_content_uri='https://s.getgems.io/nft/b/c/62fba50217c3fe3cbaad9e7f/meta.json',
        nft_item_content_base_uri='https://s.getgems.io/nft/b/c/62fba50217c3fe3cbaad9e7f/',
        nft_item_code_hex=nft_item_code_hex
    )
    return collection

async def deploy_collection(collection):

    code = collection.options['nft_item_code_hex']
    print(type(code))
    print(len(code))
    print(code[:100])
    client = await get_client()
    state_init = collection.create_state_init()['state_init']
    seqno = await get_seqno_with_retry(client, wallet_address, 10)
    query = wallet.create_transfer_message(
        to_addr=collection.address.to_string(),
        amount=to_nano(0.05, 'ton'),  # Комиссия для деплоя
        seqno=seqno,
        state_init=state_init
    )

    data = await client.raw_run_method(method='get_account_state', stack_data=[], address=wallet_address)
    print(data)
    await client.raw_send_message(query['message'].to_boc(False))
    print(f"Адрес коллекции: {collection.address.to_string(True, True, True)}")

async def create_mint(collection, item_content_uri):
    from pathlib import Path

    payload_boc = Path("nft-mint.boc").read_bytes()
    client = await get_client()
    seqno = await get_seqno_with_retry(client, wallet_address, 10)

    msg = wallet.create_transfer_message(
        to_addr=collection.address.to_string(),
        amount=to_nano(0.01, 'ton'),  # gas for mint
        seqno=seqno,
        payload=payload_boc
    )

    await client.raw_send_message(msg['message'].to_boc(False))


if __name__ == '__main__':
    collection = create_collection()
    asyncio.run(deploy_collection(collection))
    asyncio.run(create_mint(collection, item_content_uri))
