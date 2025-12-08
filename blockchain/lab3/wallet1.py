import json
from tonsdk.contract.wallet import Wallets, WalletVersionEnum
from pytonlib import TonlibClient

wallet_version = WalletVersionEnum.v3r2
wallet_workchain = 0

def load_wallet_from_json(filename):
    with open(filename) as f:
        data = json.load(f)
    mnemonics = data["mnemonics"]
    _mn, pub, priv, wallet = Wallets.from_mnemonics(
        mnemonics, wallet_version, wallet_workchain
    )
    return mnemonics, wallet, pub, priv

mnemonics, wallet1, pub1, priv1 = load_wallet_from_json("wallet1.json")


mnemonics, public_key, private_key, wallet = Wallets.from_mnemonics(mnemonics=mnemonics, version=WalletVersionEnum.v3r2, workchain=0)

if __name__ == "__main__":
    print(mnemonics)
    print(wallet.address.to_string(True, True, True, True))
