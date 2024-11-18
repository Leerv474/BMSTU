package bmstu.prac;

import bmstu.prac.service.EcommerceOrderProcessor;
import bmstu.prac.service.FileReader;
import bmstu.prac.service.Order;
import bmstu.prac.service.RestaurantOrderProcessing;

import java.nio.file.Paths;
import java.util.*;
import java.util.concurrent.ExecutionException;

public class Main {
    public static void main(String[] args) {
        task1();
    }

    public static void task1() {
        Map<String, AbstractMap.SimpleEntry<Double, Integer>> results = new HashMap<>();
        List<FileReader> readers = new ArrayList<>();
        List<Thread> threads = new ArrayList<>();

        try {
            String[] paths = {"data/file1.txt", "data/file2.txt", "data/file3.txt"};

            for (String path : paths) {
                FileReader fileReader = new FileReader(Paths.get(path));
                Thread thread = new Thread(fileReader);
                readers.add(fileReader);
                threads.add(thread);
                thread.start();
            }

            for (Thread thread : threads) {
                thread.join();
            }

            for (FileReader reader : readers) {
                results.put(reader.getFilePath().toString(), reader.getPair());
            }

            for (Map.Entry<String, AbstractMap.SimpleEntry<Double, Integer>> result : results.entrySet()) {
                System.out.println("File: " + result.getKey() + " Total Salary: " + result.getValue().getKey() +
                        ", Employees Count: " + result.getValue().getValue());
            }
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public static void task2() {

        Order order1 = new Order("Burger", 300, 2000);
        Order order2 = new Order("Pizza", 700, 1500);
        Order order3 = new Order("Pasta", 400, 500);

        RestaurantOrderProcessing restaurantOrderProcessing = new RestaurantOrderProcessing();
        restaurantOrderProcessing.processOrder(order1);
        restaurantOrderProcessing.processOrder(order2);
        restaurantOrderProcessing.processOrder(order3);
    }

    public static void task3() {
        EcommerceOrderProcessor app = new EcommerceOrderProcessor(null, null, null, 0);
        try {
            app.runApplication();
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
    }
}
