from tonsdk.contract.wallet import Wallets, WalletVersionEnum


mnemonics_new, public_key, private_key, newWallet = Wallets.create(version=WalletVersionEnum.v3r2, workchain=0)


if __name__ == "__main__":
    print("Адрес :", newWallet.address.to_string(True, True, True))


