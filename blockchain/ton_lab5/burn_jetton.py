import base64
import requests

from tonsdk.contract.token.ft import JettonWallet
from tonsdk.contract import Address
from tonsdk.utils import to_nano

from wallet_data import wallet, wallet_address   # твой основной TON-кошелёк

API_URL = "https://testnet.toncenter.com/api/v2/"


def api_post(method: str, json_body: dict):
    resp = requests.post(API_URL + method, json=json_body)
    data = resp.json()
    if not data.get("ok", False):
        raise RuntimeError(f"Toncenter POST error in {method}: {data}")
    return data["result"]


# ---------- НАСТРОЙКИ ----------

# Jetton Wallet твоего кошелька (адрес, который дал get_jetton_wallet_addr.py)
MY_JETTON_WALLET = "kQApnzUen6qDfLGVRZIO59hFR9f4W1TjvQG9hgjS25aibfO_"

# Сколько токенов сжечь (можешь изменить на любое число)
BURN_AMOUNT = 500     # сжечь 500 TST


def burn_tokens():
    """
    Сжигаем указанное количество Jetton-токенов.
    """
    print(f"🔥 Сжигаем {BURN_AMOUNT} TST...")

    # 1) Формируем тело burn для JettonWallet
    body = JettonWallet().create_burn_body(
        jetton_amount=to_nano(BURN_AMOUNT, "ton"),
    )

    # 2) Получаем seqno TON-кошелька
    seq_data = api_post(
        "runGetMethod",
        {
            "address": wallet_address,
            "method": "seqno",
            "stack": []
        }
    )
    seqno = int(seq_data["stack"][0][1], 16)
    print("seqno:", seqno)

    # 3) Формируем внешнее сообщение:
    #    TON wallet → JettonWallet → burn()
    query = wallet.create_transfer_message(
        to_addr=MY_JETTON_WALLET,    # Жетон-кошелек, который будет жечь токены
        amount=to_nano(0.1, "ton"),  # TON для газа
        seqno=seqno,
        payload=body,
    )

    # 4) кодируем и отправляем
    boc_bytes = query["message"].to_boc(False)
    boc_b64 = base64.b64encode(boc_bytes).decode()

    send_res = api_post("sendBoc", {"boc": boc_b64})
    print("Результат burn:", send_res)


if __name__ == "__main__":
    burn_tokens()
