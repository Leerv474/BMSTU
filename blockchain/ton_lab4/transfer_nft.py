import asyncio

from tonsdk.contract.token.nft import NFTItem
from tonsdk.contract import Address
from tonsdk.utils import to_nano

from TonTools import TonCenterClient, Wallet as TonToolsWallet

from wallet_data import mnemonics, wallet, wallet_address
from client_utils import get_client, get_seqno

# ---------- ВСТАВЬ СВОИ АДРЕСА ----------

# Адрес КОНКРЕТНОГО NFT ИЗ ITEMS (страница айтема в Tonscan)
NFT_ADDRESS = "kQAllrIkeaEHULkWmzL_b3NGhCYb4U-Vj8BlMCRsqANuMwJ8"

# Адрес второго кошелька (получатель)
DEST_ADDRESS = "kQC_HRoYDo6zGW8kusKmZvoBmnqrED7afncRgcQ1Z30or5K5"



# ---------- Вариант 1: через TonTools / TonCenter ----------

async def transfer_nft_tontools():
    """
    Высокоуровневый трансфер: библиотека сама сформирует все сообщения.
    """
    provider = TonCenterClient(
        base_url="https://testnet.toncenter.com/api/v2/"
        # при желании можно добавить api_key="..."
    )

    wallet_tt = TonToolsWallet(
        mnemonics=mnemonics,
        version="v3r2",
        provider=provider
    )

    await wallet_tt.transfer_nft(
        destination_address=DEST_ADDRESS,
        nft_address=NFT_ADDRESS,
        fee=0.05  # комиссия (TON)
    )

    print("Трансфер NFT через TonTools завершён.")


# ---------- Вариант 2: низкоуровневый через pytonlib ----------

async def transfer_nft_pytonlib():
    """
    Низкоуровневый вариант: мы сами собираем тело перевода и шлём
    обычное сообщение кошелька на адрес NFT.
    """
    # тело сообщения для контракта NFT: "передай владение на DEST_ADDRESS"
    body = NFTItem().create_transfer_body(
        new_owner_address=Address(DEST_ADDRESS)
    )

    client = await get_client()
    seqno = await get_seqno(client, wallet_address)
    print("seqno перед transfer_nft_pytonlib:", seqno)

    # ВАЖНО: to_addr = адрес NFT-контракта, НЕ адрес получателя!
    query = wallet.create_transfer_message(
        to_addr=NFT_ADDRESS,
        amount=to_nano(0.1, "ton"),  # немного TON на газ
        seqno=seqno,
        payload=body
    )

    await client.raw_send_message(query["message"].to_boc(False))
    print("Трансфер NFT через pytonlib завершён.")


if __name__ == "__main__":

    async def main():
        # сначала запускаем высокий уровень (TonTools):
        await transfer_nft_tontools()

        # потом (если хочешь) можешь отдельно протестировать низкий уровень:
        # await transfer_nft_pytonlib()

    asyncio.run(main())
