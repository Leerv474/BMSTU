package bmstu.lab.task3;

import java.util.Random;

public class Waiter implements Runnable {
    private final OrderQueue orderQueue;
    private final int maxOrders;
    private final Random random = new Random();

    public Waiter(OrderQueue orderQueue, int maxOrders) {
        this.orderQueue = orderQueue;
        this.maxOrders = maxOrders;
    }

    @Override
    public void run() {
        for (int i = 1; i <= maxOrders; i++) {
            try {
                Thread.sleep(random.nextInt(500)); // Имитация времени принятия заказа
                Order order = new Order(i);
                orderQueue.addOrder(order);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println("Waiter interrupted.");
            }
        }
    }
}
