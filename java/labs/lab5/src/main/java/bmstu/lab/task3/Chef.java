package bmstu.lab.task3;

import java.util.Random;

public class Chef implements Runnable {
    private final OrderQueue orderQueue;
    private final int chefId;
    private final int maxConcurrentDishes;
    private final Random random = new Random();

    public Chef(OrderQueue orderQueue, int chefId, int maxConcurrentDishes) {
        this.orderQueue = orderQueue;
        this.chefId = chefId;
        this.maxConcurrentDishes = maxConcurrentDishes;
    }

    @Override
    public void run() {
        for (int i = 0; i < maxConcurrentDishes; i++) {
            try {
                Order order = orderQueue.takeOrder();
                System.out.println("Chef " + chefId + " is preparing " + order);
                Thread.sleep(random.nextInt(1000)); // Имитация приготовления блюда
                Dish dish = new Dish(order.getId());
                System.out.println("Chef " + chefId + " finished " + dish);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println("Chef " + chefId + " interrupted.");
            }
        }
    }
}
