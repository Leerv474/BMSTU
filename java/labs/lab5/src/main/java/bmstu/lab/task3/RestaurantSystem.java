package bmstu.lab.task3;

import java.util.ArrayList;
import java.util.List;

public class RestaurantSystem {
    private final List<Thread> waiters = new ArrayList<>();
    private final List<Thread> chefs = new ArrayList<>();

    public RestaurantSystem(int queueCapacity, int numWaiters, int maxOrdersPerWaiter, int numChefs, int maxConcurrentDishes) {
        OrderQueue orderQueue = new OrderQueue(queueCapacity);

        for (int i = 0; i < numWaiters; i++) {
            waiters.add(new Thread(new Waiter(orderQueue, maxOrdersPerWaiter), "Waiter-" + (i + 1)));
        }

        for (int i = 0; i < numChefs; i++) {
            chefs.add(new Thread(new Chef(orderQueue, i + 1, maxConcurrentDishes), "Chef-" + (i + 1)));
        }
    }

    public void run() {
        waiters.forEach(Thread::start);
        chefs.forEach(Thread::start);

        waiters.forEach(waiter -> {
            try {
                waiter.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        chefs.forEach(chef -> {
            try {
                chef.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        System.out.println("Simulation complete.");
    }
}
