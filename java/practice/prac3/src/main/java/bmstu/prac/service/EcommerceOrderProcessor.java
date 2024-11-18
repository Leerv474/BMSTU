package bmstu.prac.service;

import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

public class EcommerceOrderProcessor implements Callable<Integer> {
    private final Queue<String> orderQueue;
    private final ReentrantLock lock;
    private final AtomicInteger processedOrders;
    private final int totalOrders;

    public EcommerceOrderProcessor(Queue<String> orderQueue, ReentrantLock lock, AtomicInteger processedOrders, int totalOrders) {
        this.orderQueue = orderQueue;
        this.lock = lock;
        this.processedOrders = processedOrders;
        this.totalOrders = totalOrders;
    }

    @Override
    public Integer call() {
        int localProcessedCount = 0;
        while (processedOrders.get() < totalOrders || !orderQueue.isEmpty()) {
            lock.lock();
            try {
                String order = orderQueue.poll();
                if (order != null) {
                    processOrder(order);
                    localProcessedCount++;
                    processedOrders.incrementAndGet();
                }
            } finally {
                lock.unlock();
            }
        }
        return localProcessedCount;
    }

    private void processOrder(String order) {
        System.out.println("Processing: " + order + " by " + Thread.currentThread().getName());
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    // Non-static main logic
    public void runApplication() throws InterruptedException, ExecutionException {
        Queue<String> orderQueue = new ConcurrentLinkedQueue<>();
        ReentrantLock lock = new ReentrantLock();
        AtomicInteger processedOrders = new AtomicInteger(0);
        int totalOrders = 50;

        ExecutorService executorService = Executors.newFixedThreadPool(5);
        ExecutorService orderProducer = Executors.newSingleThreadExecutor();

        // Producer to add orders to the queue
        orderProducer.submit(() -> {
            for (int i = 1; i <= totalOrders; i++) {
                String order = "Order #" + i;
                lock.lock();
                try {
                    orderQueue.add(order);
                    System.out.println("Added: " + order);
                } finally {
                    lock.unlock();
                }
                try {
                    Thread.sleep(50);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        });

        // Start consumers
        List<Future<Integer>> futures = new ArrayList<>();
        for (int i = 0; i < 4; i++) {
            futures.add(executorService.submit(
                    new EcommerceOrderProcessor(orderQueue, lock, processedOrders, totalOrders)));
        }

        // Shutdown executors
        orderProducer.shutdown();
        executorService.shutdown();
        orderProducer.awaitTermination(10, TimeUnit.SECONDS);
        executorService.awaitTermination(10, TimeUnit.SECONDS);

        // Collect results
        int totalProcessed = 0;
        for (Future<Integer> future : futures) {
            totalProcessed += future.get();
        }

        System.out.println("All orders processed. Total processed: " + totalProcessed);
    }
}
