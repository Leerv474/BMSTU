package ru.bmstu.employee;

import lombok.AllArgsConstructor;

import java.util.Comparator;
import java.util.List;

@AllArgsConstructor
public class EmployeeService {
    private List<Employee> employees;

    public List<Employee> employeeFilter(double salary, String department) {
        var filteredEmployees = employees.stream()
                .filter(employee -> employee.getSalary() > salary && employee.getDepartment().equals(department))
                .toList().stream().sorted(Comparator.comparing(Employee::getAge)).limit(3).toList();
        filteredEmployees.forEach(employee -> System.out.println(employee.getName() + " " + employee.getAge()));
        return filteredEmployees;
    }
}
