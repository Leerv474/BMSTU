import json, random, requests
from tonsdk.contract.wallet import WalletVersionEnum, Wallets
from tonsdk.utils import to_nano, bytes_to_b64str

wallet_version = WalletVersionEnum.v3r2
wallet_workchain = 0

def load_wallet_from_json(filename):
    with open(filename) as f:
        data = json.load(f)
    mnemonics = data["mnemonics"]
    _mn, pub, priv, wallet = Wallets.from_mnemonics(
        mnemonics, wallet_version, wallet_workchain
    )
    return wallet, pub, priv

wallet1, pub1, priv1 = load_wallet_from_json("wallet1.json")
wallet2, pub2, priv2 = load_wallet_from_json("wallet2.json")

print("Loaded wallet1:", wallet1.address.to_string(True, True, True))
print("Loaded wallet2:", wallet2.address.to_string(True, True, True))

from tonsdk.utils import bytes_to_b64str

query = wallet1.create_init_external_message()
boc_base64 = bytes_to_b64str(query["message"].to_boc(False))

import requests
resp = requests.post(
    "https://testnet.toncenter.com/api/v2/sendBoc",
    data={"boc": boc_base64}  # No API key needed for testnet, rate-limited
)
print(resp.json())


import time

while True:
    r = requests.get(
        "https://testnet.toncenter.com/api/v2/getWalletInformation",
        params={"address": wallet1.address.to_string(True, True, True)}
    )
    info = r.json()
    if info["ok"] and info["result"]["account_state"] == "active":
        print("Wallet deployed!")
        break
    time.sleep(2)


query = wallet2.create_init_external_message()
boc_base64 = bytes_to_b64str(query["message"].to_boc(False))

resp = requests.post(
    "https://testnet.toncenter.com/api/v2/sendBoc",
    data={"boc": boc_base64}  # No API key needed for testnet, rate-limited
)
print(resp.json())


import time

while True:
    r = requests.get(
        "https://testnet.toncenter.com/api/v2/getWalletInformation",
        params={"address": wallet2.address.to_string(True, True, True)}
    )
    info = r.json()
    if info["ok"] and info["result"]["account_state"] == "active":
        print("Wallet deployed!")
        break
    time.sleep(2)
