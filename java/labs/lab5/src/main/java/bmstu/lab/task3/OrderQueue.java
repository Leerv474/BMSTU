package bmstu.lab.task3;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class OrderQueue {
    private final BlockingQueue<Order> queue;

    public OrderQueue(int capacity) {
        this.queue = new LinkedBlockingQueue<>(capacity);
    }

    public void addOrder(Order order) throws InterruptedException {
        queue.put(order);
        System.out.println("Order added: " + order);
    }

    public Order takeOrder() throws InterruptedException {
        Order order = queue.take();
        System.out.println("Order taken: " + order);
        return order;
    }
}
