package ru.bmstu.customer;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDate;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Purchase {
    private String category;
    private double amount;
    private LocalDate date;
}
