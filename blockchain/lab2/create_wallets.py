import json
from tonsdk.contract.wallet import WalletVersionEnum, Wallets
from tonsdk.utils import bytes_to_b64str
from tonsdk.crypto import mnemonic_new

wallet_workchain = 0
wallet_version = WalletVersionEnum.v3r2

def create_wallet_json(filename):
    mnemonics = mnemonic_new()
    _mn, pub, priv, wallet = Wallets.from_mnemonics(
        mnemonics, wallet_version, wallet_workchain
    )
    query = wallet.create_init_external_message()
    base64_boc = bytes_to_b64str(query["message"].to_boc(False))

    data = {
        "mnemonics": mnemonics,
        "public_key": pub.hex(),
        "private_key": priv.hex(),
        "raw_address": wallet.address.to_string(),
        "user_friendly_address": wallet.address.to_string(True, True, True),
        "base64_boc": base64_boc
    }

    with open(filename, "w") as f:
        json.dump(data, f, indent=4)

    print(f"✅ Wallet saved to {filename}")
    return data

wallet1_data = create_wallet_json("wallet1.json")
wallet2_data = create_wallet_json("wallet2.json")

