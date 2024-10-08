package org.bmstu.api;

import org.bmstu.dao.JsonParser;
import org.bmstu.model.TransactionModel;

import java.util.Comparator;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

public class OptionMenu {
    public static void print(Scanner scanner) {
        int option;
        while (true) {
            System.out.println("Добро пожаловать в финансовый помощник.");
            System.out.println("0. Выход\n1. Запись доходов\n2. Запись расходов\n3. Календарь платежей");
            System.out.print("Выберите опцию: ");
            option = scanner.nextInt();

            switch (option) {
                case 0:
                    System.out.println("Выход из системы...");
                    return;
                case 1:
                    incomeRecord(scanner);
                    break;
                case 2:
                    expensesRecord(scanner);
                    break;
                case 3:
                    paymentHistory();
                    break;
                default:
                    System.out.println("Неверный ввод, попробуйте снова");
                    break;
            }
        }
    }

    private static void incomeRecord(Scanner scanner) {
        double income = -1;
        System.out.println("---Запись доходы---");
        while (income < 0) {
            System.out.print("Введите доходы: ");
            scanner.nextLine();
            try {
                income = scanner.nextDouble();
                if (income < 0) {
                    System.out.println("Неверный ввод, повторите снова...");
                }
            } catch (InputMismatchException e) {
                System.out.println("Неверный ввод, повторите снова...");
            }


            JsonParser.updateIncomeData(income);
        }
    }

    private static void expensesRecord(Scanner scanner) {
        double expenses = -1;
        System.out.println("---Запись расходов---");
        while (expenses < 0) {
            System.out.print("Введите расходы: ");
            scanner.nextLine();
            try {
                expenses = scanner.nextDouble();
                if (expenses < 0) {
                    System.out.println("Неверный ввод, повторите снова...");
                }
            } catch (InputMismatchException e) {
                System.out.println("Неверный ввод, повторите снова...");
            }

            JsonParser.updateExpensesData(expenses);
        }
    }

    private static void paymentHistory() {
        System.out.println("---История расходов---");

        List<TransactionModel> transactionList = JsonParser.getTransactionHistory();
        if (transactionList == null) {
            System.out.println("Записи отсутствуют");
            return;
        }
        transactionList.sort(Comparator.comparing(TransactionModel::getRecordDate));
        transactionList.forEach(item -> System.out.printf("- %s %s: %f\n", item.getTransactionType(), item.getRecordDate(), item.getTransactionSum()));
        System.out.println();
    }
}