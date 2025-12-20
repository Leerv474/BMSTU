import json
from tonsdk.contract.wallet import WalletVersionEnum, Wallets

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
