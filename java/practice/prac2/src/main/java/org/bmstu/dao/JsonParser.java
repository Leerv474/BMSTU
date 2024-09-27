package org.bmstu.dao;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.bmstu.financeManagement.TransactionManager;

import java.util.ArrayList;
import java.util.List;

public class JsonParser {

    private static final ObjectMapper MAPPER = new ObjectMapper();
    private static final FileMangerImpl FILE_MANGER = new FileMangerImpl();

    public static void updateExpensesData(double expenses) {
        try {
            List<TransactionManager> expensesList = new ArrayList<>();
            String oldExpensesData = FILE_MANGER.readExpensesRecord();
            JsonNode arrayNode = MAPPER.readTree(String.valueOf(oldExpensesData));
            if (arrayNode.isArray()) {
                for (JsonNode node : arrayNode) {
                    expensesList.add(new TransactionManager(node.get("transactionSum").asDouble(), node.get("recordDate").asText(), "Расход"));
                }
            }
            expensesList.add(new TransactionManager(expenses));

            String newExpensesData = MAPPER.writerWithDefaultPrettyPrinter().writeValueAsString(expensesList);
            FILE_MANGER.saveExpensesRecord(newExpensesData);

        } catch (JsonProcessingException e) {
            e.printStackTrace();
        }
    }

    public static void updateIncomeData(double income) {
        try {
            List<TransactionManager> incomeList = new ArrayList<>();
            String oldIncomeData = FILE_MANGER.readIncomeRecord();
            JsonNode arrayNode = MAPPER.readTree(String.valueOf(oldIncomeData));
            if (arrayNode.isArray()) {
                for (JsonNode node : arrayNode) {
                    incomeList.add(new TransactionManager(node.get("transactionSum").asDouble(), node.get("recordDate").asText(), "Доход"));
                }
            }
            incomeList.add(new TransactionManager(income));

            FILE_MANGER.saveIncomeRecord(MAPPER.writerWithDefaultPrettyPrinter().writeValueAsString(incomeList));

        } catch (JsonProcessingException e) {
            e.printStackTrace();
        }
    }

    public static List<TransactionManager> getTransactionHistory() {
        try {
            List<TransactionManager> transactionList = new ArrayList<>();
            String incomeData = FILE_MANGER.readIncomeRecord();
            JsonNode arrayNode = MAPPER.readTree(String.valueOf(incomeData));
            if (arrayNode.isArray()) {
                for (JsonNode node : arrayNode) {
                    transactionList.add(new TransactionManager(node.get("transactionSum").asDouble(), node.get("recordDate").asText(), "Доход"));
                }
            }

            String expensesData = FILE_MANGER.readExpensesRecord();
            arrayNode = MAPPER.readTree(String.valueOf(expensesData));
            if (arrayNode.isArray()) {
                for (JsonNode node : arrayNode) {
                    transactionList.add(new TransactionManager(node.get("transactionSum").asDouble(), node.get("recordDate").asText(), "Расход"));
                }
            }
            return transactionList;

        } catch (JsonProcessingException e) {
            e.printStackTrace();
        }
        return null;
    }
}
