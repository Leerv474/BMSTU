package ru.bmstu;

import ru.bmstu.customer.Customer;
import ru.bmstu.customer.CustomerService;
import ru.bmstu.customer.Purchase;
import ru.bmstu.employee.Employee;
import ru.bmstu.employee.EmployeeService;
import ru.bmstu.order.Item;
import ru.bmstu.order.Order;
import ru.bmstu.order.OrderService;
import ru.bmstu.product.Product;
import ru.bmstu.product.ProductService;
import ru.bmstu.student.Student;
import ru.bmstu.student.StudentService;

import java.time.LocalDate;
import java.util.List;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
//        studentTest();
//        employeeTest();
//        orderTest();
//        productTest();
        customerTest();
    }

    private static void studentTest() {
        Student studentA = Student.builder()
                .name("Artyom")
                .age(22)
                .subjects(Map.of("math", 80, "physics", 50, "cs", 70))
                .build();

        Student studentB = Student.builder()
                .name("Ilya")
                .age(20)
                .subjects(Map.of("math", 85, "physics", 34, "cs", 69))
                .build();

        Student studentC = Student.builder()
                .name("Egor")
                .age(20)
                .subjects(Map.of("math", 98, "physics", 92, "cs", 100))
                .build();

        StudentService studentService = new StudentService(List.of(studentA, studentB, studentC));
        studentService.listSortedStudents(20, "math", 80).forEach(student -> System.out.println(student.toString()));
    }

    private static void employeeTest() {
        Employee employee1 = Employee.builder()
                .name("egor")
                .age(20)
                .salary(69000)
                .department("IT")
                .build();

        Employee employee2 = Employee.builder()
                .name("ilya")
                .age(20)
                .salary(39000)
                .department("IT")
                .build();

        Employee employee3 = Employee.builder()
                .name("nizami")
                .age(20)
                .salary(120000)
                .department("IT")
                .build();

        Employee employee4 = Employee.builder()
                .name("artyom")
                .age(22)
                .salary(100000)
                .department("IT")
                .build();

        EmployeeService employeeService = new EmployeeService(List.of(employee1, employee2, employee3, employee4));
        employeeService.employeeFilter(50000, "IT").forEach(employee -> System.out.println(employee.toString()));
    }

    private static void orderTest() {
        Item item1 = new Item("Electronics", 250.0);
        Item item2 = new Item("Clothing", 50.0);
        Item item3 = new Item("Electronics", 150.0);
        Item item4 = new Item("Books", 30.0);

        Order order1 = new Order(1, List.of(item1, item2), LocalDate.now().minusDays(10));
        Order order2 = new Order(2, List.of(item3), LocalDate.now().minusDays(5));
        Order order3 = new Order(3, List.of(item4), LocalDate.now().minusMonths(2));

        OrderService orderService = new OrderService(List.of(order1, order2, order3));

        double total = orderService.filterOrders("Clothing");
        System.out.println("Total price for Electronics in last month: " + total);
    }

    private static void productTest() {
        Product product1 = new Product("Laptop", 1200.0, 5);
        Product product2 = new Product("Phone", 800.0, 10);
        Product product3 = new Product("Headphones", 150.0, 0); // Out of stock
        Product product4 = new Product("Monitor", 300.0, 3);

        ProductService productService = new ProductService(List.of(product1, product2, product3, product4));

        productService.filterProducts(50.0);
    }

    private static void customerTest() {
        Purchase purchase1 = new Purchase("electronics", 800.0, LocalDate.now().minusDays(10));
        Purchase purchase2 = new Purchase("groceries", 150.0, LocalDate.now().minusDays(15));
        Purchase purchase3 = new Purchase("electronics", 500.0, LocalDate.now().minusDays(20));
        Purchase purchase4 = new Purchase("furniture", 300.0, LocalDate.now().minusDays(5));

        Customer customer1 = new Customer("customer1@example.com", List.of(purchase1, purchase2));
        Customer customer2 = new Customer("customer2@example.com", List.of(purchase3));
        Customer customer3 = new Customer("customer3@example.com", List.of(purchase4, purchase2, purchase1));

        CustomerService customerService = new CustomerService(List.of(customer1, customer2, customer3));

        List<String> filteredEmails = customerService.filteredEmails();
        filteredEmails.forEach(System.out::println);
    }
}

