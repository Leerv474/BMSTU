from tonsdk.contract.wallet import WalletVersionEnum

# ТВОЙ тестовый кошелёк (НЕ основной!)
MNEMONICS = [
        "field",
        "man",
        "zero",
        "typical",
        "winter",
        "vague",
        "fatigue",
        "crane",
        "zero",
        "actor",
        "trouble",
        "there",
        "industry",
        "push",
        "crater",
        "spray",
        "tide",
        "include",
        "shoulder",
        "build",
        "cabbage",
        "middle",
        "oxygen",
        "exhaust"
]

WALLET_VERSION = WalletVersionEnum.v3r2

TONAPI_BASE_URL = "https://testnet.tonapi.io"  # Testnet TonAPI

TONAPI_API_KEY: str | None = None  # если получишь — впишем

JETTON_CONTENT_URI = (
    "https://raw.githubusercontent.com/JSwhiz/ton-jetton-lab5-assets/main/jetton_meta.json"
)

# сохраняем после deploy
MINTER_ADDRESS_FILE = "minter_address.txt"

