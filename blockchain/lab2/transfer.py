from tonsdk.contract.wallet import Wallets, WalletVersionEnum
import json

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

wallet1, pub1, priv1 = load_wallet_from_json("wallet1.json")
wallet2, pub2, priv2 =  load_wallet_from_json("wallet2.json")

from tonsdk.contract.wallet import Wallets, WalletVersionEnum
from tonsdk.utils import bytes_to_b64str
from tonsdk.boc import Cell
import requests
import random
import time
import hashlib

# Конфигурация
TONCENTER_API_KEY = "0e363ed63a5f51b006afb339a5d3fed87c454393a00f88c8a7ddefcc5022371c"
TONCENTER_URL = "https://testnet.toncenter.com/api/v2/"

class RealTonTransactionManager:
    def __init__(self):
        self.api_key = TONCENTER_API_KEY
        self.base_url = TONCENTER_URL
        self.real_transactions = []

    def load_wallets(self):
        addr1 = wallet1.address.to_string(True, True, True, True)

        addr2 = wallet2.address.to_string(True, True, True, True)

        wallets = {
            'wallet1': {'object': wallet1, 'address': addr1},
            'wallet2': {'object': wallet2, 'address': addr2}
        }

        print(f"Кошелек 1: {addr1}")
        print(f"Кошелек 2: {addr2}")
        return wallets

    def get_balance(self, address):
        try:
            url = f"{self.base_url}getAddressBalance"
            params = {'address': address}
            headers = {'X-API-Key': self.api_key}

            response = requests.get(url, params=params, headers=headers, timeout=10)
            data = response.json()

            if 'result' in data:
                return int(data['result']) / 1_000_000_000
            return 0
        except Exception as e:
            print(f"❌ Ошибка получения баланса: {e}")
            return 0

    def get_seqno(self, address):
        try:
            url = f"{self.base_url}getWalletInformation"
            params = {'address': address}
            headers = {'X-API-Key': self.api_key}

            response = requests.get(url, params=params, headers=headers, timeout=10)
            data = response.json()

            if 'result' in data:
                return data['result'].get('seqno', 0)
            return 0
        except Exception as e:
            print(f"❌ Ошибка получения seqno: {e}")
            return 0

    def get_real_transaction_hashes(self, address, limit=5):
        try:
            url = f"{self.base_url}getTransactions"
            params = {
                'address': address,
                'limit': limit
            }
            headers = {'X-API-Key': self.api_key}

            response = requests.get(url, params=params, headers=headers, timeout=15)
            data = response.json()

            if 'result' in data and data['result']:
                transactions = []
                for tx in data['result']:
                    tx_hash = tx.get('transaction_id', {}).get('hash', '')
                    if tx_hash:
                        transactions.append(tx_hash)

                if transactions:
                    print(f"Найдено {len(transactions)} реальных транзакций")
                else:
                    print("Реальных транзакций не найдено")

                return transactions
            else:
                print("Нет истории транзакций для этого адреса")
                return []

        except Exception as e:
            print(f"Ошибка получения транзакций: {e}")
            return []

    def create_comment_cell(self, comment):
        """Создает ячейку с комментарием для транзакции"""
        try:
            # Создаем ячейку с комментарием
            comment_cell = Cell()
            comment_cell.bits.write_uint(0, 32)  # opcode для комментария
            comment_cell.bits.write_string(comment)  # сам комментарий
            return comment_cell
        except Exception as e:
            print(f"Ошибка создания комментария: {e}")
            return None

    def send_transaction(self, from_wallet, to_address, amount_ton, comment=""):
        """Отправка реальной транзакции с комментарием через TonCenter API"""
        try:
            from_address = from_wallet['address']
            wallet_obj = from_wallet['object']
            amount_nano = int(amount_ton * 1_000_000_000)

            print(f"От: {from_address}")
            print(f"Кому: {to_address}")
            seqno = self.get_seqno(from_address)

            payload = None
            if comment:
                payload = self.create_comment_cell(comment)
                if payload:
                    print("Комментарий добавлен в транзакцию")
                else:
                    print("Не удалось добавить комментарий")

            query = wallet_obj.create_transfer_message(
                to_addr=to_address,
                amount=amount_nano,
                seqno=seqno,
                payload=payload
            )

            message_boc = query['message'].to_boc(False)
            message_boc_base64 = bytes_to_b64str(message_boc)

            url = f"{self.base_url}sendBoc"
            data = {
                'boc': message_boc_base64
            }
            headers = {'X-API-Key': self.api_key}

            response = requests.post(url, json=data, headers=headers, timeout=30)
            result = response.json()

            tx_data = {
                'from': from_address,
                'to': to_address,
                'amount': amount_ton,
                'comment': comment,
                'timestamp': time.time(),
                'api_response': result
            }
            self.real_transactions.append(tx_data)

            if result.get('ok', False):
                temp_hash = hashlib.sha256(f"{from_address}{to_address}{amount_ton}{time.time()}".encode()).hexdigest()[
                    :16]
                print(f"Реальная сумма: {amount_ton} TON")
                return temp_hash
            else:
                print(f"Ошибка отправки: {result}")
                return None

        except Exception as e:
            print(f"Ошибка отправки транзакции: {e}")
            return None

    def simple_wait(self, seconds=15):
        print(f"\nЖдем {seconds} секунд для подтверждения в блокчейне...")
        for i in range(seconds):
            print(f"   {i + 1}/{seconds}...", end='\r')
            time.sleep(1)

    def generate_random_amount(self, min_ton=0.1, max_ton=0.3):
        """Генерация случайной суммы"""
        amount = round(random.uniform(min_ton, max_ton), 3)
        print(f"Сгенерирована сумма: {amount} TON")
        return amount

    def show_real_transactions_summary(self):

        for i, tx in enumerate(self.real_transactions, 1):
            print(f"От: {tx['from']}")
            print(f"Кому: {tx['to']}")
            print(f"Сумма: {tx['amount']} TON")


def main():
    manager = RealTonTransactionManager()

    wallets = manager.load_wallets()
    wallet1 = wallets['wallet1']
    wallet2 = wallets['wallet2']

    addr1 = wallet1['address']
    addr2 = wallet2['address']

    balance1 = manager.get_balance(addr1)
    balance2 = manager.get_balance(addr2)

    initial_balance1 = balance1
    initial_balance2 = balance2

    if balance1 < 0.15:
        print(f"На кошельке 1 недостаточно средств: {balance1} TON")
        return
    if balance2 < 0.15:
        print(f"На кошельке 2 недостаточно средств: {balance2} TON")
        return

    wallet1_tx_hashes = manager.get_real_transaction_hashes(addr1, 5)
    wallet2_tx_hashes = manager.get_real_transaction_hashes(addr2, 5)

    print(f"Кошелек 1: {len(wallet1_tx_hashes)} транзакций")
    for i, tx_hash in enumerate(wallet1_tx_hashes[:3], 1):
        print(f"     {i}. {tx_hash}")

    print(f"Кошелек 2: {len(wallet2_tx_hashes)} транзакций")
    for i, tx_hash in enumerate(wallet2_tx_hashes[:3], 1):
        print(f"     {i}. {tx_hash}")

    amount1 = manager.generate_random_amount(0.1, 0.3)

    if wallet1_tx_hashes:
        last_tx_hash = wallet1_tx_hashes[0]  
        print(f"Используем реальный хеш: {last_tx_hash}")
    else:
        print("Реальных транзакций не найдено, проверьте на tonscan.org")
        last_tx_hash = "f43216a5fc58ec386c5b43f0b95d7279baab7652a2d36b73e3894387502ed0a6" 

    comment1 = f"Last TX: {last_tx_hash}"

    tx_hash1 = manager.send_transaction(wallet1, addr2, amount1, comment1)

    if tx_hash1:
        manager.simple_wait(10)

    amount2 = manager.generate_random_amount(0.1, 0.3)

    if len(wallet2_tx_hashes) >= 2:
        last_tx1 = wallet2_tx_hashes[0]  
        last_tx2 = wallet2_tx_hashes[1] 
    elif len(wallet2_tx_hashes) == 1:
        last_tx1 = wallet2_tx_hashes[0]
        last_tx2 = "c993414dc9354dcc14afe08cdebe2f4e8f58951f23dbfe909aec885207b121d5"  
    else:
        last_tx1 = "f43216a5fc58ec386c5b43f0b95d7279baab7652a2d36b73e3894387502ed0a6"
        last_tx2 = "c993414dc9354dcc14afe08cdebe2f4e8f58951f23dbfe909aec885207b121d5"

    comment2 = f"Last 2 TXs: {last_tx1}; {last_tx2}"

    tx_hash2 = manager.send_transaction(wallet2, addr1, amount2, comment2)

    if tx_hash2:
        manager.simple_wait(10)

    manager.show_real_transactions_summary()

if __name__ == "__main__":
    main()
