package org.bmstu.financeManagement;

import java.time.LocalDate;

public class TransactionManager {
    private LocalDate recordDate;
    private double transactionSum;
    private String transactionType;

    public TransactionManager(double transactionSum, String recordDate, String transactionType) {
        this.transactionSum = transactionSum;
        this.recordDate = LocalDate.parse(recordDate);
        this.transactionType = transactionType;
    }
    public TransactionManager(double transactionSum, String recordDate) {
        this.transactionSum = transactionSum;
        this.recordDate = LocalDate.parse(recordDate);
    }
    public TransactionManager(double transactionSum) {
        this.transactionSum = transactionSum;
        this.recordDate = LocalDate.now();
    }

    public String getTransactionType(){
        return transactionType;
    }

    public String getRecordDate() {
        return String.valueOf(recordDate);
    }

    public double getTransactionSum() {
        return transactionSum;
    }
}
