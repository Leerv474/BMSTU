package org.bmstu.dao;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileMangerImpl implements FileManager {
    private final String incomePath = "financeData/income.json";
    private final String expensesPath = "financeData/expenses.json";

    FileMangerImpl() {
        Path incomeFilePath = Paths.get(incomePath);
        Path expensesFilePath = Paths.get(expensesPath);
        try {
            if (!Files.exists(incomeFilePath.getParent())) {
                Files.createDirectories(incomeFilePath.getParent());
            }

            if (!Files.exists(incomeFilePath)) {
                Files.createFile(incomeFilePath);
            }

            if (!Files.exists(expensesFilePath)) {
                Files.createFile(expensesFilePath);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void saveIncomeRecord(String incomeJsonString) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(incomePath))) {
            writer.write(incomeJsonString);
            writer.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void saveExpensesRecord(String expensesJsonString) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(expensesPath))) {
            writer.write(expensesJsonString);
            writer.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public String readIncomeRecord() {
        StringBuilder incomeRecord = new StringBuilder();
        String line;
        try (BufferedReader reader = new BufferedReader(new FileReader(incomePath))) {
            while ((line = reader.readLine()) != null) {
                incomeRecord.append(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return String.valueOf(incomeRecord);
    }

    @Override
    public String readExpensesRecord() {
        StringBuilder expensesRecord = new StringBuilder();
        String line;
        try (BufferedReader reader = new BufferedReader(new FileReader(expensesPath))) {
            while ((line = reader.readLine()) != null) {
                expensesRecord.append(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return String.valueOf(expensesRecord);
    }
}