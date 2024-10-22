package ru.bmstu.customer;

import lombok.AllArgsConstructor;

import java.time.LocalDate;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

@AllArgsConstructor
public class CustomerService {
    private List<Customer> customers;

    public List<String> filteredEmails() {
        LocalDate now = LocalDate.now();
        LocalDate oneMonthAgo = now.minusMonths(1);
        LocalDate twoWeeksAgo = now.minusWeeks(2);

        return customers.stream()
                .filter(customer -> customer.getPurchases().stream()
                        .filter(purchase -> purchase.getDate().isAfter(oneMonthAgo))
                        .mapToDouble(purchase -> {
                            if (purchase.getCategory().equals("electronics") && purchase.getDate().isAfter(twoWeeksAgo)) {
                                return purchase.getAmount() * 1.1;
                            }
                            return purchase.getAmount();
                        }).sum() > 1000)
                .toList().stream()
                .sorted((c1, c2) -> Integer.compare(
                        c2.getPurchases().size(), c1.getPurchases().size()))
                .map(Customer::getEmail)
                .collect(Collectors.toList());
    }
}
