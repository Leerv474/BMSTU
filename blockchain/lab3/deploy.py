import json
from tonsdk.contract.wallet import Wallets, WalletVersionEnum
from pytonlib import TonlibClient
from tonsdk.utils import bytes_to_b64str, to_nano
from pathlib import Path
import requests
import asyncio


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

mnemonics, wallet, pub, priv = load_wallet_from_json("wallet1.json")

from walletNew import newWallet

async def get_seqno(client: TonlibClient, address: str):
    data = await client.raw_run_method(method='seqno', stack_data=[], address=address)
    return(int(data['stack'][0][1], 16))

async def main():
    url = "https://ton.org/testnet-global.config.json"
    
    config = requests.get(url).json()

    keystore_dir = '/tmp/ton_keystore'
    Path(keystore_dir).mkdir(parents=True, exist_ok=True)

    client = TonlibClient(ls_index=3, config=config, keystore=keystore_dir, tonlib_timeout=60)
    wallet_address = wallet.address.to_string(True, True, True, True)
    new_wallet_address = newWallet.address.to_string(True, True, True, True)
    print(f"Адрес кошелька: {wallet_address}")
    print(f"Адрес нового кошелька: {new_wallet_address}")


    # query = newWallet.create_init_external_message()
    # boc_base64 = bytes_to_b64str(query["message"].to_boc(False))
    #
    # resp = requests.post(
    #     "https://testnet.toncenter.com/api/v2/sendBoc",
    #     json={"boc": boc_base64}  # No API key needed for testnet, rate-limited
    # )
    # print(resp.json())
    #
    #
    # import time
    #
    # while True:
    #     r = requests.get(
    #         "https://testnet.toncenter.com/api/v2/getWalletInformation",
    #         params={"address": newWallet.address.to_string(True, True, True)}
    #     )
    #     info = r.json()
    #     if info["ok"] and info["result"]["account_state"] == "active":
    #         print("Wallet deployed!")
    #         break
    #     time.sleep(2)

    await client.init()

    import asyncio

    async def get_seqno_safe(client, wallet_address, retries=20, delay=5):
        for i in range(retries):
            try:
                return await get_seqno(client, wallet_address)
            except Exception as e:
                print(f"Retry {i+1}/{retries} due to: {e}")
                await asyncio.sleep(delay)
        raise Exception("Failed to get seqno after retries")
    seqno = await get_seqno_safe(client, wallet_address)

    state_init = newWallet.create_state_init()['state_init']

    
    transfer_query = wallet.create_transfer_message(
        to_addr=new_wallet_address,  
        amount=to_nano(0.05, 'ton'), 
        seqno=seqno, 
        state_init=state_init  
    )
 
    transfer_message = transfer_query['message'].to_boc(False)
    await client.raw_send_message(transfer_message)

if __name__ == '__main__':
    asyncio.run(main())
