
import os
from tonsdk.contract.wallet import Wallets
from tonsdk.utils import Address
from config import MNEMONICS, WALLET_VERSION

WALLET_WORKCHAIN = 0

try:
    from config_local import MNEMONICS_ADMIN
except Exception:
    MNEMONICS_ADMIN = None

profile = os.getenv("WALLET_PROFILE", "main").lower()

if profile == "main":
    used_mnemonics = MNEMONICS
elif profile == "admin":
    if not MNEMONICS_ADMIN:
        raise RuntimeError("WALLET_PROFILE=admin, но нет config_local.py или MNEMONICS_ADMIN.")
    used_mnemonics = MNEMONICS_ADMIN
else:
    raise RuntimeError(f"Неизвестный WALLET_PROFILE={profile}. Используй main или admin.")

_mn, PUBLIC_KEY, PRIVATE_KEY, wallet = Wallets.from_mnemonics(
    used_mnemonics, WALLET_VERSION, WALLET_WORKCHAIN
)

wallet_address = wallet.address.to_string(True, True, True)

def get_wallet_address() -> str:
    return wallet_address
