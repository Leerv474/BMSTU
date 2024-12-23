package bmstu.prac.service;

import java.util.Map;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ConcurrentHashMap;

public class RestaurantOrderProcessing {
    private static final Map<String, Integer> ingredientStock = new ConcurrentHashMap<>();

    static {
        ingredientStock.put("Burger", 10);
        ingredientStock.put("Pizza", 5);
        ingredientStock.put("Pasta", 8);
    }


    public void processOrder(Order order) {
        CompletableFuture.supplyAsync(() -> checkIngredients(order))
                .thenCompose(isAvailable -> {
                    if (isAvailable) {
                        return prepareDish(order);
                    } else {
                        System.out.println("Order for " + order.getDishName() + " canceled due to insufficient ingredients.");
                        return CompletableFuture.completedFuture(null);
                    }
                })
                .thenApply(preparedOrder -> {
                    if (preparedOrder != null) {
                        return calculatePrice(preparedOrder);
                    }
                    return null;
                })
                .thenAccept(finalOrder -> {
                    if (finalOrder != null) {
                        notifyReady(finalOrder);
                    }
                });
    }

    private boolean checkIngredients(Order order) {
        int required = 1;
        String dish = order.getDishName();
        if (ingredientStock.getOrDefault(dish, 0) >= required) {
            ingredientStock.computeIfPresent(dish, (key, value) -> value - required);
            System.out.println("Ingredients available for " + dish);
            return true;
        }
        return false;
    }

    private CompletableFuture<Order> prepareDish(Order order) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                System.out.println("Preparing " + order.getDishName());
                Thread.sleep(order.getPreparationTime());
                System.out.println(order.getDishName() + " is ready!");
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            return order;
        });
    }

    private Order calculatePrice(Order order) {
        double finalPrice = order.getPrice();
        if (finalPrice > 500) {
            finalPrice *= 0.9;
        }
        order.setFinalPrice(finalPrice);
        System.out.println("Final price for " + order.getDishName() + ": " + finalPrice);
        return order;
    }

    private void notifyReady(Order order) {
        System.out.println("Notification: " + order.getDishName() + " is ready! Total price: " + order.getFinalPrice());
    }
}

