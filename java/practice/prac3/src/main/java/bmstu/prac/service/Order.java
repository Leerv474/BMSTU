package bmstu.prac.service;

public class Order {
    private final String dishName;
    private final int preparationTime; // в миллисекундах
    private final double price;
    private double finalPrice;

    public Order(String dishName, int preparationTime, double price) {
        this.dishName = dishName;
        this.preparationTime = preparationTime;
        this.price = price;
    }

    public String getDishName() {
        return dishName;
    }

    public int getPreparationTime() {
        return preparationTime;
    }

    public double getPrice() {
        return price;
    }

    public double getFinalPrice() {
        return finalPrice;
    }

    public void setFinalPrice(double finalPrice) {
        this.finalPrice = finalPrice;
    }
}
