from tonsdk.contract import Contract
from tonsdk.utils import Address, to_nano
import base64
import requests

from tonsdk.contract.wallet import Wallets, WalletVersionEnum
import json

def load_wallet_from_json(filename):
    with open(filename) as f:
        data = json.load(f)
    mnemonics = data["mnemonics"]
    _, _, _, wallet = Wallets.from_mnemonics(
        mnemonics, WalletVersionEnum.v3r2, 0
    )
    return wallet, mnemonics

wallet, mnemonics = load_wallet_from_json("wallet.json")
wallet_address = wallet.address.to_string(True, True, True)


if __name__ == "__main__":
    print("Адрес кошелька:", wallet_address)
API_URL = "https://testnet.toncenter.com/api/v2/"

def api_post(method: str, json_body: dict):
    resp = requests.post(API_URL + method, json=json_body)
    data = resp.json()
    if not data.get("ok", False):
        raise RuntimeError(f"Toncenter POST error in {method}: {data}")
    return data["result"]


from tonsdk.boc import Cell
from tonsdk.contract import Contract


with open("contract.boc", "rb") as f:
    code_bytes = f.read()


code_cell = Cell.one_from_boc(code_bytes)


contract = Contract()
contract.options['code'] = code_cell  


state_init = contract.create_state_init()


seq_data = api_post("runGetMethod", {"address": wallet_address, "method": "seqno", "stack": []})
seqno = int(seq_data["stack"][0][1], 16)


query = wallet.create_transfer_message(
    to_addr=contract.address.to_string(True, True, True, True),
    amount=to_nano(0.16, "ton"),  
    seqno=seqno,
    state_init=state_init["state_init"]
)


boc_b64 = base64.b64encode(query["message"].to_boc(False)).decode()
send_res = api_post("sendBoc", {"boc": boc_b64})
print("Deploy result:", send_res)
print("Contract address:", contract.address.to_string(True, True, True, True))

