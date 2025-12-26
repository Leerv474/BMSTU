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


def create_jetton_minter():
    """
    Создаём объект JettonMinter c админом = наш кошелёк и ссылкой на метаданные.
    """
    admin = Address(wallet_address)

    # Временно используем учебную ссылку из методички.
    # Позже можно заменить на свою, если выложишь token_data_base64.json в GitHub.
    jetton_content_uri = (
        "https://raw.githubusercontent.com/yungwine/pyton-lessons/master/lesson-6/token_data.json"
    )

    minter = JettonMinter(
        admin_address=admin,
        jetton_content_uri=jetton_content_uri,
        jetton_wallet_code_hex=JettonWallet.code
    )

    # В devdaoteam-tonsdk нет свойства .state_init, нужно вызвать метод:
    state_init = minter.create_state_init()["state_init"]

    minter_address = minter.address.to_string(True, True, True, True)
    print("Адрес минтера (JettonMinter):", minter_address)

    return state_init, minter_address


def deploy_minter():
    """
    Отправляем транзакцию на деплой минтера через toncenter.
    """
    state_init, jetton_address = create_jetton_minter()

    # получаем текущий seqno кошелька
    seq_data = api_post("runGetMethod", {
        "address": wallet_address,
        "method": "seqno",
        "stack": []
    })
    seqno = int(seq_data["stack"][0][1], 16)
    print("Текущий seqno:", seqno)

    # формируем обычный internal transfer на адрес минтера,
    # прикрепляя state_init
    query = wallet.create_transfer_message(
        to_addr=jetton_address,
        amount=to_nano(0.05, "ton"),
        seqno=seqno,
        state_init=state_init
    )

    boc_bytes = query["message"].to_boc(False)
    boc_b64 = base64.b64encode(boc_bytes).decode()

    send_res = api_post("sendBoc", {"boc": boc_b64})
    print("Результат деплоя минтера:", send_res)


if __name__ == "__main__":
    deploy_minter()
