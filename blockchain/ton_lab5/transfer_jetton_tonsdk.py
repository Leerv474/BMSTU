import base64
import requests

from tonsdk.contract.token.ft import JettonWallet
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


# ---------- НАСТРОЙКИ ----------

# Jetton Wallet твоего ПЕРВОГО кошелька
# ЭТО ТО, ЧТО ВЫВЕЛ get_jetton_wallet_addr.py:
# Jetton Wallet address:
# kQApnzUen6qDfLGVRZIO59hFR9f4W1TjvQG9hgjS25aibfO_
MY_JETTON_WALLET = "kQApnzUen6qDfLGVRZIO59hFR9f4W1TjvQG9hgjS25aibfO_"

# Адрес ПОЛУЧАТЕЛЯ (второй твой кошелёк)
DEST_ADDRESS = "kQCWvjb966Oe-M3KiihUzBG1TOC-rbkMK8seZthT6jWmujXp"

# Сколько jetton отправляем (в «человеческих» единицах, как 15 TST)
SEND_AMOUNT = 15


def transfer_jetton():
    # 1) Собираем тело transfer для контракта JettonWallet
    body = JettonWallet().create_transfer_body(
        to_address=Address(DEST_ADDRESS),
        jetton_amount=to_nano(SEND_AMOUNT, "ton"),
        # можно ещё указать forward_ton_amount, forward_payload и т.д. при желании
    )

    # 2) Получаем текущий seqno нашего TON-кошелька
    seq_data = api_post(
        "runGetMethod",
        {
            "address": wallet_address,
            "method": "seqno",
            "stack": [],
        },
    )
    seqno = int(seq_data["stack"][0][1], 16)
    print("seqno:", seqno)

    # 3) Формируем внешнее сообщение:
    #    наш TON-кошелёк -> контракт JettonWallet
    query = wallet.create_transfer_message(
        to_addr=MY_JETTON_WALLET,        # адрес JettonWallet
        amount=to_nano(0.1, "ton"),      # немного TON на газ и выполнение кода JettonWallet
        seqno=seqno,
        payload=body,                    # сюда кладём тело transfer jetton'а
    )

    # 4) Кодируем BOC и отправляем через toncenter
    boc_bytes = query["message"].to_boc(False)
    boc_b64 = base64.b64encode(boc_bytes).decode()

    send_res = api_post("sendBoc", {"boc": boc_b64})
    print("Результат трансфера Jetton:", send_res)


if __name__ == "__main__":
    transfer_jetton()
