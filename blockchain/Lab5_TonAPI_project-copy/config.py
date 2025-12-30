from tonsdk.contract.wallet import WalletVersionEnum

# ТВОЙ тестовый кошелёк (НЕ основной!)
MNEMONICS = [
    "loop", "galaxy", "memory", "ahead", "merge", "nose",
    "arrange", "close", "alone", "solid", "sunny", "tiny",
    "essay", "wolf", "false", "master", "used", "ordinary",
    "shallow", "isolate", "coast", "minute", "umbrella", "grocery"
]

WALLET_VERSION = WalletVersionEnum.v3r2

TONAPI_BASE_URL = "https://testnet.tonapi.io"  # Testnet TonAPI

TONAPI_API_KEY: str | None = None  # если получишь — впишем

JETTON_CONTENT_URI = (
    "https://raw.githubusercontent.com/JSwhiz/ton-jetton-lab5-assets/main/jetton_meta.json"
)

# сохраняем после deploy
MINTER_ADDRESS_FILE = "minter_address.txt"

