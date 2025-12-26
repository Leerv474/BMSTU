import json
from tonsdk.contract.wallet import WalletVersionEnum, Wallets
import asyncio
import json
from pytonlib import TonlibClient
from tonsdk.utils import bytes_to_b64str, to_nano
from pathlib import Path
import requests

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

wallet, pub, priv = load_wallet_from_json("wallet1.json")
wallet_address = wallet.address.to_string(True, True, True)


from tonsdk.contract.token.ft import JettonMinter, JettonWallet
from tonsdk.utils import Address

def create_jetton_minter():
    minter = JettonMinter(
        admin_address=Address(wallet_address),
        jetton_content_uri="https://raw.githubusercontent.com/Leerv474/BMSTU/refs/heads/master/blockchain/lab5/metadata.json",
        jetton_wallet_code_hex=JettonWallet.code
    )
    return minter

def get_state_init_and_address():
    minter = create_jetton_minter()
    return minter.create_state_init, minter.address.to_string()

async def get_seqno(client: TonlibClient, address: str):
    data = await client.raw_run_method(method='seqno', stack_data=[], address=address)

    return(int(data['stack'][0][1], 16))

async def deploy_jetton(wallet, client):
    state_init, jetton_address = get_state_init_and_address()

    seqno = get_seqno(client, wallet.address.to_string())

    msg = wallet.create_transfer_message(
        to_addr=jetton_address,
        amount=to_nano(0.05, "ton"),
        seqno=seqno,
        state_init=state_init
    )

    await client.raw_send_message(msg["message"].to_boc(False))
    print("Jetton deployed:", jetton_address)


async def main():

    url = "https://ton.org/testnet-global.config.json"
    
    config = requests.get(url).json()
    keystore_dir = '/tmp/ton_keystore'
    Path(keystore_dir).mkdir(parents=True, exist_ok=True)
    client = TonlibClient(ls_index=3, config=config, keystore=keystore_dir, tonlib_timeout=60)

    await deploy_jetton(wallet, client)

if __name__ == "__main__":
    asyncio.run(main())

