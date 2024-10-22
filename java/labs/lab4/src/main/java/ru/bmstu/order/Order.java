package ru.bmstu.order;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDate;
import java.util.List;

@AllArgsConstructor
@Data
@NoArgsConstructor
public class Order {
    private int orderId;
    private List<Item> items;
    private LocalDate orderDate;
}
