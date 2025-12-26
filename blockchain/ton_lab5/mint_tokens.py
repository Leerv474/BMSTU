import base64
import requests

from tonsdk.contract.token.ft import JettonMinter, JettonWallet
from tonsdk.contract import Address
from tonsdk.utils import to_nano

from wallet_data import wallet, wallet_address

API_URL = "https://testnet.toncenter.com/api/v2/"


def api_post(method: str, json_body: dict):
    resp = requests.post(API_URL + method, json=json_body)
    data = resp.json()
    if not data.get("ok", False):
        raise RuntimeError(f"Toncenter POST error in {method}: {data}")
    return data["result"]


# -----------------------------
# 1. Создаём тело операции mint
# -----------------------------
def create_mint_body():
    # Адрес минтера 
    jetton_address = "kQCIkj9ZxCUUNA-P-jx6bHdr39wOZeRx5zYcM0gLz23KbN_4"   

    minter = JettonMinter(
        admin_address=Address(wallet_address),
        jetton_content_uri="https://raw.githubusercontent.com/yungwine/pyton-lessons/master/lesson-6/token_data.json",
        jetton_wallet_code_hex=JettonWallet.code
    )

    body = minter.create_mint_body(
        destination=Address(wallet_address),     # кому начисляем TST
        jetton_amount=to_nano(100000, "ton")    # сколько токенов создать
    )

    return body, jetton_address


# -----------------------------
# 2. Отправляем транзакцию
# -----------------------------
def mint_tokens():
    body, jetton_address = create_mint_body()

    # seqno
    seq_data = api_post("runGetMethod", {
        "address": wallet_address,
        "method": "seqno",
        "stack": []
    })
    seqno = int(seq_data["stack"][0][1], 16)
    print("seqno:", seqno)

    query = wallet.create_transfer_message(
        to_addr=jetton_address,
        amount=to_nano(0.05, "ton"),   # газ + отправка
        seqno=seqno,
        payload=body
    )

    boc = base64.b64encode(query["message"].to_boc(False)).decode()
    send_res = api_post("sendBoc", {"boc": boc})

    print("Результат минта:", send_res)


if __name__ == "__main__":
    mint_tokens()
