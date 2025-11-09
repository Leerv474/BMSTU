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

# --- Fetch seqno (without API key) ---
r = requests.get(
    "https://testnet.toncenter.com/api/v2/getWalletInformation",
    params={"address": wallet1.address.to_string(True, True, True)}
)
info = r.json()
print(info)

if not info.get("ok"):
    raise Exception(f"Wallet1 not initialized or invalid: {info}")

seqno = info["result"]["seqno"]

# --- Prepare transfer ---
amount = random.uniform(0.1, 0.3)
value = to_nano(amount, "ton")

transfer = wallet1.create_transfer_message(
    to_addr=wallet2.address.to_string(True, True, True),
    amount=value,
    seqno=seqno,
    payload=f"Sending {amount:.3f} TONs from wallet1".encode("utf-8")
)

boc_base64 = bytes_to_b64str(transfer["message"].to_boc(False))

# --- Send BOC (without API key) ---
resp = requests.post(
    "https://testnet.toncenter.com/api/v2/sendBoc",
    data={"boc": boc_base64}
)
print(resp.json())

print(f"✅ Sent {amount:.3f} TONs from wallet1 to wallet2")

