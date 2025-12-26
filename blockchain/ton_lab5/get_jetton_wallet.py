from tonsdk.contract.token.ft import JettonMinter, JettonWallet
from tonsdk.contract import Address

#  МИНТЕР (Jetton Master)
JETTON_MASTER = "kQCIkj9ZxCUUNA-P-jx6bHdr39wOZeRx5zYcM0gLz23KbN_4"  

#  TON-адрес (владелец Jetton Wallet)
OWNER = "0QC_HRoYDo6zGW8kusKmZvoBmnqrED7afncRgcQ1Z30or898"  # из wallet_data

# Создаём объект Minter
minter = JettonMinter(
    admin_address=Address(OWNER),
    jetton_content_uri="",
    jetton_wallet_code_hex=JettonWallet.code
)

# Вычисляем адрес Jetton Wallet
wallet_address = minter.get_wallet_address(Address(OWNER))

print("Jetton Wallet address:")
print(wallet_address.to_string(True, True, True, True))
