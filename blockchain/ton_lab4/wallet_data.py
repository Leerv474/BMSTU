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
