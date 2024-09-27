package org.bmstu.dao;

public interface FileManager {
    void saveIncomeRecord(String incomeJsonString);
    void saveExpensesRecord(String expensesJsonString);
    String readIncomeRecord();
    String readExpensesRecord();
}
