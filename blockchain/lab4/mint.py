import base64
import requests

from tonsdk.contract.token.nft import NFTCollection
from tonsdk.contract import Address
from tonsdk.utils import to_nano


API_URL = "https://testnet.toncenter.com/api/v2/"


def api_post(method: str, json_body: dict):
    resp = requests.post(API_URL + method, json=json_body)
    data = resp.json()
    if not data.get("ok", False):
        raise RuntimeError(f"Toncenter POST error in {method}: {data}")
    return data["result"]


def mint_one(index: int, owner_addr: str):
    """
    Минт ОДНОГО NFT с заданным index.
    Каждый запуск скрипта = одна транзакция.
    """
    collection: NFTCollection = create_collection_mint()
    owner = Address(owner_addr)

    item_uri = f"{index + 1}/meta.json"

    body = collection.create_mint_body(
        item_index=index,
        new_owner_address=owner,
        item_content_uri=item_uri,
        amount=to_nano(0.02, "ton")
    )

    # Берём актуальный seqno один раз
    seq_data = api_post("runGetMethod", {
        "address": wallet_address,
        "method": "seqno",
        "stack": []
    })
    seqno = int(seq_data["stack"][0][1], 16)
    print("Текущий seqno:", seqno)

    query = wallet.create_transfer_message(
        to_addr=collection.address.to_string(True, True, True, True),
        amount=to_nano(0.04, "ton"),
        seqno=seqno,
        payload=body
    )

    boc = base64.b64encode(query["message"].to_boc(False)).decode()
    send_res = api_post("sendBoc", {"boc": boc})
    print(f"NFT #{index} отправлен:", send_res)


if __name__ == "__main__":
    # доминтим только NFT с индексом 2
    mint_one(2, wallet_address)
