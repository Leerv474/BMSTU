from tonsdk.contract.wallet import Wallets, WalletVersionEnum

# Мнемоника твоего основного тестнет-кошелька (тот же, что в 4-й лабе)
mnemonics = [
    'prosper', 'calm', 'column', 'silk', 'absent', 'sea', 'cause', 'library',
    'region', 'slim', 'area', 'winter', 'guitar', 'icon', 'all', 'giant',
    'spike', 'fruit', 'visit', 'dash', 'burger', 'install', 'balance', 'shoulder'
]

mn, public_key, private_key, wallet = Wallets.from_mnemonics(
    mnemonics=mnemonics,
    version=WalletVersionEnum.v3r2,
    workchain=0
)

wallet_address = wallet.address.to_string(True, True, True, True)

if __name__ == "__main__":
    print("Адрес кошелька:", wallet_address)
