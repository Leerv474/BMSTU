package bmstu.lab.task2;

import java.util.ArrayList;
import java.util.List;

public class BankSystem {
    private final BankAccount[] accounts;
    private final List<Thread> clients = new ArrayList<>();
    private final int maxTransactions;

    public BankSystem(int numAccounts, int initialBalance, int numClients, int maxTransactions) {
        this.accounts = new BankAccount[numAccounts];
        for (int i = 0; i < numAccounts; i++) {
            accounts[i] = new BankAccount(initialBalance);
        }
        this.maxTransactions = maxTransactions;

        for (int i = 0; i < numClients; i++) {
            clients.add(new Thread(new Client(accounts, maxTransactions, i + 1)));
        }
    }

    public void run() {
        for (Thread client : clients) {
            client.start();
        }

        for (Thread client : clients) {
            try {
                client.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println("Simulation interrupted.");
            }
        }

        printBalances();
    }

    private void printBalances() {
        System.out.println("Final account balances:");
        for (int i = 0; i < accounts.length; i++) {
            System.out.printf("Account %d: %d%n", i, accounts[i].getBalance());
        }
    }
}
