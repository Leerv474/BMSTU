import base64
import requests
import argparse  # <-- добавили

from tonsdk.contract.token.nft import NFTCollection
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


def batch_mint(start_index: int = 3, count: int = 5, owner_addr: str = None):
    """
    Минтим несколько NFT ОДНОЙ транзакцией.
    start_index – с какого индекса начинать (0,1,2 уже заняты).
    count – сколько новых NFT создать.
    """
    if owner_addr is None:
        owner_addr = wallet_address

    collection: NFTCollection = create_collection_mint()
    owner = Address(owner_addr)

    contents_and_owners = []

    # Мы используем учебную коллекцию TSC#2, там все метаданные одинаковые,
    # поэтому для надёжности подставим один и тот же суффикс "1/meta.json".
    for i in range(start_index, start_index + count):
        item_suffix = "1/meta.json"   # все токены будут с одинаковым контентом
        contents_and_owners.append((item_suffix, owner))

    body = collection.create_batch_mint_body(
        from_item_index=start_index,
        contents_and_owners=contents_and_owners,
        amount_per_one=to_nano(0.01, "ton")  # по 0.01 TON на каждый NFT
    )

    # берём текущий seqno кошелька
    seq_data = api_post("runGetMethod", {
        "address": wallet_address,
        "method": "seqno",
        "stack": []
    })
    seqno = int(seq_data["stack"][0][1], 16)
    print("seqno перед batch-минтом:", seqno)

    query = wallet.create_transfer_message(
        to_addr=collection.address.to_string(True, True, True, True),
        amount=to_nano(0.2, "ton"),   # чуть с запасом на все NFT и газ
        seqno=seqno,
        payload=body
    )

    boc = base64.b64encode(query["message"].to_boc(False)).decode()
    send_res = api_post("sendBoc", {"boc": boc})
    print("Результат массового минта:", send_res)


if __name__ == "__main__":
    # разбор аргументов командной строки
    parser = argparse.ArgumentParser(description="Batch mint NFT in TON collection")
    parser.add_argument(
        "--start",
        type=int,
        default=3,
        help="Начальный индекс NFT в коллекции (по умолчанию 3)"
    )
    parser.add_argument(
        "--count",
        type=int,
        default=5,
        help="Сколько NFT заминтить одной транзакцией (по умолчанию 5)"
    )
    parser.add_argument(
        "--owner",
        type=str,
        default=wallet_address,
        help="Адрес владельца, на которого минтятся NFT (по умолчанию твой кошелёк)"
    )

    args = parser.parse_args()

    print(f"Запускаю batch-mint: start={args.start}, count={args.count}, owner={args.owner}")
    batch_mint(start_index=args.start, count=args.count, owner_addr=args.owner)
