import base64
import requests

from tonsdk.contract.token.nft import NFTCollection, NFTItem
from tonsdk.contract import Address
from tonsdk.utils import to_nano

from wallet_data import wallet, wallet_address

API_URL = "https://testnet.toncenter.com/api/v2/"


def api_get(method: str, params: dict):
    resp = requests.get(API_URL + method, params=params)
    data = resp.json()
    if not data.get("ok", False):
        raise RuntimeError(f"Toncenter GET error in {method}: {data}")
    return data["result"]


def api_post(method: str, json_body: dict):
    resp = requests.post(API_URL + method, json=json_body)
    data = resp.json()
    if not data.get("ok", False):
        raise RuntimeError(f"Toncenter POST error in {method}: {data}")
    return data["result"]


def create_collection_mint() -> NFTCollection:
    """
    Создаём объект NFTCollection с роялти и URI.
    """
    royalty_base = 1000        # база
    royalty_factor = 55        # "процент" от базы (5.5%)

    owner = Address(wallet_address)

    # Коллекция из методички TEP-64 (можно не менять)
    collection_content_uri = (
        "https://s.getgems.io/nft/b/c/62fba50217c3fe3cbaad9e7f/meta.json"
    )
    nft_item_content_base_uri = (
        "https://s.getgems.io/nft/b/c/62fba50217c3fe3cbaad9e7f/"
    )

    collection = NFTCollection(
        royalty_base=royalty_base,
        royalty=royalty_factor,
        royalty_address=owner,
        owner_address=owner,
        collection_content_uri=collection_content_uri,
        nft_item_content_base_uri=nft_item_content_base_uri,
        nft_item_code_hex=NFTItem.code
    )

    print("Адрес коллекции:", collection.address.to_string(True, True, True, True))
    return collection


def deploy_collection():
    """
    Деплой коллекции через toncenter (без pytonlib, без lite-server).
    """
    collection = create_collection_mint()

    # state_init коллекции
    state_init = collection.create_state_init()["state_init"]

    # получаем seqno кошелька через toncenter
    seq_data = api_post(
        "runGetMethod",
        {
            "address": wallet_address,
            "method": "seqno",
            "stack": []
        }
    )
    seqno = int(seq_data["stack"][0][1], 16)
    print("Текущий seqno кошелька:", seqno)

    # формируем internal transfer на адрес коллекции + state_init
    query = wallet.create_transfer_message(
        to_addr=collection.address.to_string(True, True, True, True),
        amount=to_nano(0.05, "ton"),  # немного TON на деплой
        seqno=seqno,
        state_init=state_init
    )

    boc_bytes = query["message"].to_boc(False)
    boc_b64 = base64.b64encode(boc_bytes).decode()

    send_res = api_post("sendBoc", {"boc": boc_b64})
    print("Результат отправки деплоя:", send_res)


if __name__ == "__main__":
    deploy_collection()
