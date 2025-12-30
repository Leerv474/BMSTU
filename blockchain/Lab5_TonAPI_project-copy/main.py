import sys
import asyncio
from wallet import get_wallet_address
from net import get_balance
from jetton_minter import deploy_minter, mint_to_self, transfer_jetton, burn_jetton, change_admin, claim_admin


def usage():
    print("""
Usage:
  python main.py deploy_minter
  python main.py mint_self <amount>
  python main.py transfer_jetton <jetton_wallet_addr> <to_address> <amount>
  python main.py burn_jetton <jetton_wallet_addr> <amount>
  python main.py info
""")


async def main():
    if len(sys.argv) < 2:
        return usage()

    cmd = sys.argv[1]

    if cmd == "deploy_minter":
        deploy_minter()

    elif cmd == "mint_self":
        if len(sys.argv) < 3:
            print("Specify amount! Example: python main.py mint_self 100")
            return
        mint_to_self(int(sys.argv[2]))

    elif cmd == "transfer_jetton":
        if len(sys.argv) < 5:
            print("Specify jetton wallet address, destination address, and amount! Example: python main.py transfer_jetton <jetton_wallet> <to_address> 100")
            return
        transfer_jetton(sys.argv[2], sys.argv[3], int(sys.argv[4]))

    elif cmd == "burn_jetton":
        if len(sys.argv) < 4:
            print("Specify jetton wallet address and amount! Example: python main.py burn_jetton <jetton_wallet> 100")
            return
        # Добавление await для асинхронной функции
        burn_jetton(sys.argv[2], int(sys.argv[3]))

    elif cmd == "info":
        addr = get_wallet_address()
        bal = get_balance(addr)
        print("Wallet:", addr)
        print(f"Balance: {bal / 1e9:.3f} TON")

    elif cmd == "change_admin":
        change_admin(sys.argv[2])

    elif cmd == "claim_admin":
        await claim_admin()


    else:
        usage()


if __name__ == "__main__":
    asyncio.run(main())
