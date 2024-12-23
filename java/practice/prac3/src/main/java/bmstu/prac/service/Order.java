package bmstu.prac.service;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class Order {
    private final String dishName;
    private final int preparationTime;
    private final double price;
    private double finalPrice;

    public Order(String dishName, int preparationTime, double price) {
        this.dishName = dishName;
        this.preparationTime = preparationTime;
        this.price = price;
    }

}
