import time

while True:
    txs = requests.get(f"https://testnet.toncenter.com/api/v2/getTransactions?address={wallet1.address.to_string(True, True, True)}").json()
    if "result" in txs and txs["result"]:
        print("Latest tx:", txs["result"][0]["utime_string"])
        break
    time.sleep(2)
