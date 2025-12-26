import base64
import requests

from tonsdk.boc import begin_cell, Cell
from tonsdk.contract import Address

API_URL = "https://testnet.toncenter.com/api/v2/"

# Адрес минтера (Jetton Master) ТВОЕГО токена TST
JETTON_MASTER = "kQCIkj9ZxCUUNA-P-jx6bHdr39wOZeRx5zYcM0gLz23KbN_4"  # <- проверь, что он точный

# Твой основной TON-кошелёк (holder)
OWNER = "0QC_HRoYDo6zGW8kusKmZvoBmnqrED7afncRgcQ1Z30or898"


def api_post(method: str, json_body: dict):
    resp = requests.post(API_URL + method, json=json_body)
    data = resp.json()
    if not data.get("ok", False):
        raise RuntimeError(f"Toncenter error in {method}: {data}")
    return data["result"]


def main():
    owner_addr = Address(OWNER)

    # Собираем ячейку с адресом владельца
    cell = begin_cell().store_address(owner_addr).end_cell()
    boc = cell.to_boc(False)
    boc_b64 = base64.b64encode(boc).decode()

    # runGetMethod get_wallet_address(JettonMaster, slice(owner_address))
    result = api_post(
        "runGetMethod",
        {
            "address": JETTON_MASTER,
            "method": "get_wallet_address",
            "stack": [["tvm.Slice", boc_b64]],
        },
    )

    # Ожидаем, что в стеке вернётся cell/slice с адресом кошелька
    stack_item = result["stack"][0]  # первый элемент стека
    raw_val = stack_item[1]

    # Toncenter может вернуть либо строку, либо dict с полем "bytes"
    if isinstance(raw_val, str):
        slice_b64 = raw_val
    elif isinstance(raw_val, dict) and "bytes" in raw_val:
        slice_b64 = raw_val["bytes"]
    else:
        raise TypeError(f"Неподдерживаемый формат stack[0][1]: {raw_val}")

    # Декодируем BOC в ячейку и читаем адрес
    slice_boc = base64.b64decode(slice_b64)
    cell_wallet = Cell.one_from_boc(slice_boc)
    sl = cell_wallet.begin_parse()
    wallet_addr = sl.read_msg_addr()


    print("Jetton Wallet address:")
    print(wallet_addr.to_string(True, True, True, True))


if __name__ == "__main__":
    main()
