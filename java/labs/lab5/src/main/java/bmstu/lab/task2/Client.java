package bmstu.lab.task2;

import java.util.Random;

public class Client implements Runnable {
    private final BankAccount[] accounts;
    private final int maxTransactions;
    private final int clientId;
    private int transactionCount = 0;
    private final Random random = new Random();

    public Client(BankAccount[] accounts, int maxTransactions, int clientId) {
        this.accounts = accounts;
        this.maxTransactions = maxTransactions;
        this.clientId = clientId;
    }

    @Override
    public void run() {
        while (transactionCount < maxTransactions) {
            int fromIndex = random.nextInt(accounts.length);
            int toIndex = random.nextInt(accounts.length);
            int amount = random.nextInt(100) + 1;

            if (fromIndex != toIndex) {
                BankAccount fromAccount = accounts[fromIndex];
                BankAccount toAccount = accounts[toIndex];

                if (fromAccount.withdraw(amount)) {
                    toAccount.deposit(amount);
                    System.out.printf("Client %d: Transferred %d from Account %d to Account %d%n",
                            clientId, amount, fromIndex, toIndex);
                } else {
                    System.out.printf("Client %d: Insufficient funds in Account %d for transfer of %d%n",
                            clientId, fromIndex, amount);
                }
                transactionCount++;
            }
        }
        System.out.printf("Client %d: Finished after %d transactions.%n", clientId, transactionCount);
    }
}
