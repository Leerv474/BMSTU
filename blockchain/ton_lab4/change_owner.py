import base64
import requests

from tonsdk.contract.token.nft import NFTCollection, NFTItem
from tonsdk.contract import Address
from tonsdk.utils import to_nano

from wallet_data import wallet, wallet_address
from collection_mint import create_collection_mint

API_URL = "https://testnet.toncenter.com/api/v2/"


def api_post(method: str, json_body: dict):
    resp = requests.post(API_URL + method, json=json_body)
    data = resp.json()
    if not data.get("ok", False):
        raise RuntimeError(f"Toncenter POST error in {method}: {data}")
    return data["result"]


def change_collection_owner():
    # Загружаем коллекцию (та же, что ты деплоил)
    collection = create_collection_mint()
    print("Адрес коллекции:", collection.address.to_string(True, True, True, True))

    # НОВЫЙ ВЛАДЕЛЕЦ КОЛЛЕКЦИИ (второй кошелёк)
    new_owner_address = Address("kQCWvjb966Oe-M3KiihUzBG1TOC-rbkMK8seZthT6jWmujXp")

    # ВАЖНО: здесь параметр называется new_owner_address
    body = collection.create_change_owner_body(
        new_owner_address=new_owner_address
    )

    # Берём seqno твоего кошелька
    seq_data = api_post("runGetMethod", {
        "address": wallet_address,
        "method": "seqno",
        "stack": []
    })
    seqno = int(seq_data["stack"][0][1], 16)
    print("seqno:", seqno)

    # Формируем и отправляем сообщение на адрес коллекции
    query = wallet.create_transfer_message(
        to_addr=collection.address.to_string(True, True, True, True),
        amount=to_nano(0.03, "ton"),
        seqno=seqno,
        payload=body
    )

    boc = base64.b64encode(query["message"].to_boc(False)).decode()
    send_res = api_post("sendBoc", {"boc": boc})
    print("Результат смены владельца:", send_res)


if __name__ == "__main__":
    change_collection_owner()
