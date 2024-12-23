package bmstu.lab.task3;

public class Dish {
    private final int id;

    public Dish(int id) {
        this.id = id;
    }

    @Override
    public String toString() {
        return "Dish{" + "id=" + id + '}';
    }
}
