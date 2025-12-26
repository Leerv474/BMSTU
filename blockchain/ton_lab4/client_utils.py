import requests
from pathlib import Path
from pytonlib import TonlibClient

CONFIG_URL = "https://ton.org/testnet-global.config.json"
KEYSTORE_DIR = "/tmp/ton_keystore"   # под виндой тоже норм

async def get_client():
    """
    Инициализируем TonlibClient для тестнета.
    """
    config = requests.get(CONFIG_URL).json()
    Path(KEYSTORE_DIR).mkdir(parents=True, exist_ok=True)

    client = TonlibClient(
        ls_index=2,
        config=config,
        keystore=KEYSTORE_DIR,
        tonlib_timeout=10
    )
    await client.init()
    return client

async def get_seqno(client: TonlibClient, address: str) -> int:
    """
    Получаем seqno кошелька через raw_run_method('seqno').
    """
    data = await client.raw_run_method(
        method="seqno",
        stack_data=[],
        address=address
    )
    return int(data["stack"][0][1], 16)
