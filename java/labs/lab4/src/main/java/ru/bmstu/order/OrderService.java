package ru.bmstu.order;

import lombok.AllArgsConstructor;

import java.time.LocalDate;
import java.util.List;

@AllArgsConstructor
public class OrderService {
    private List<Order> orders;

    public double filterOrders(String itemCategory) {
        return orders.stream()
                .filter(order -> order.getOrderDate().isAfter(LocalDate.now().minusMonths(1))
                        && order.getItems().stream().anyMatch(item -> item.getCategory().equals(itemCategory)))
                .flatMap(order -> order.getItems().stream())
                .mapToDouble(Item::getPrice).sum();
    }
}
