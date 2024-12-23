package bmstu.lab;

import bmstu.lab.task1.Runner;
import bmstu.lab.task2.BankSystem;
import bmstu.lab.task3.RestaurantSystem;

public class Main {
    public static void main(String[] args) {
        task3();
    }

    private static void task1() {
        Runner runner = new Runner();
        try {
            runner.start();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static void task2() {
        BankSystem system = new BankSystem(5, 1000, 3, 10);
        system.run();
    }

    private static void task3() {
        RestaurantSystem simulation = new RestaurantSystem(10, 2, 5, 3, 5);
        simulation.run();
    }
}