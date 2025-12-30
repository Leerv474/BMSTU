import json
from tonsdk.contract.wallet import WalletVersionEnum, Wallets
from tonsdk.contract.token.nft import NFTCollection, NFTItem
from tonsdk.boc import Cell
from tonsdk.contract import Address


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
    client = TonlibClient(ls_index=4, config=config, keystore=keystore_dir, tonlib_timeout=60)
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
        royalty_address=Address(wallet_address),
        owner_address=Address(wallet_address),
        collection_content_uri='https://example.com/collection_meta.json',
        nft_item_content_base_uri='https://example.com/nft_base_uri/',
        nft_item_code_hex=nft_item_code_hex
    )    
    return collection

async def deploy_collection(client, collection):

    code = collection.options['nft_item_code_hex']
    print(type(code))
    print(len(code))
    print(code[:100])
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

async def create_mint(client, collection):
    from pathlib import Path

    payload_boc = Path("mint.boc").read_bytes()
    seqno = await get_seqno_with_retry(client, wallet_address, 10)

    msg = wallet.create_transfer_message(
        to_addr=collection.address.to_string(),
        amount=to_nano(0.1, 'ton'),
        seqno=seqno,
        payload=payload_boc
    )

    await client.raw_send_message(msg['message'].to_boc(False))


import base64
import requests

from tonsdk.contract.token.nft import NFTCollection
from tonsdk.contract import Address
from tonsdk.utils import to_nano


API_URL = "https://testnet.toncenter.com/api/v2/"


import time

def api_post(method: str, json_body: dict, retries=5, delay=2):
    import time
    import requests

    for attempt in range(retries):
        try:
            resp = requests.post(API_URL + method, json=json_body, timeout=10)
            data = resp.json()
            if data.get("ok", False):
                return data["result"]
            elif data.get("code") == 429:
                print(f"Rate limit hit on {method}, retrying in {delay}s...")
                time.sleep(delay)
                delay *= 2
            else:
                raise RuntimeError(f"Toncenter POST error in {method}: {data}")
        except requests.exceptions.JSONDecodeError:
            print(f"Empty or invalid JSON response from {method}, retrying in {delay}s...")
            time.sleep(delay)
            delay *= 2
        except requests.exceptions.RequestException as e:
            print(f"Request error {e}, retrying in {delay}s...")
            time.sleep(delay)
            delay *= 2
    raise RuntimeError(f"Toncenter POST failed after {retries} retries for {method}")


async def mint_one(client, collection):
    res = api_post("runGetMethod", {
        "address": collection.address.to_string(),
        "method": "get_netx_item_index",
        "stack": []
    })
    last_index = int(res["stack"][0][1], 16)
    next_index = last_index#+1  # next available index

    item_uri = f"https://a.com/1.json"

    # Create mint payload
    body = collection.create_mint_body(
        item_index=next_index,
        new_owner_address=Address(wallet_address),
        item_content_uri=item_uri,
        amount=to_nano(0.02, "ton")
    )

    seqno = await get_seqno_with_retry(client, wallet_address)

    fund_msg = wallet.create_transfer_message(
        to_addr=collection.address.to_string(True, True, True, True),
        amount=to_nano(0.2, 'ton'),  # enough to cover storage fees
        seqno=seqno
    )
    await client.raw_send_message(fund_msg['message'].to_boc(False))

    # while True:
    #     state = api_post("getAccountState", {"address": collection.address.to_string()})
    #     if int(state["balance"], 16) >= to_nano(0.2, "ton"):
    #         break
    await asyncio.sleep(3)

    state = api_post("runGetMethod", {"address": collection.address.to_string(), "method": "get_nft_items_count", "stack": []})
    print("STATE: ", state)

    seqno = await get_seqno_with_retry(client, wallet_address)
    print(f"Minting NFT #{next_index}, current seqno: {seqno}")
    # Create and send transfer message
    query = wallet.create_transfer_message(
        to_addr=collection.address.to_string(True, True, True, True),
        amount=to_nano(0.2, "ton"),
        seqno=seqno,
        payload=body
    )

    boc = base64.b64encode(query["message"].to_boc(False)).decode()
    send_res = api_post("sendBoc", {"boc": boc})
    print(f"NFT #{next_index} sent:", send_res)

async def main():
    collection = create_collection()
    client = await get_client()
    await deploy_collection(client, collection)
    await mint_one(client, collection)


if __name__ == '__main__':
    asyncio.run(main())
