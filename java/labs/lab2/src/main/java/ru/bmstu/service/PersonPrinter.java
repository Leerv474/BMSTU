package ru.bmstu.service;

import ru.bmstu.domain.Person;

public class PersonPrinter {
    public static void printFI(Person p) {
        System.out.println("First Name: " + p.getFirstName());
        System.out.println("Second Name: " + p.getSecondName());
    }

    public static void printInfo(Person p) {
        System.out.println("First Name: " + p.getFirstName());
        System.out.println("Second Name: " + p.getSecondName());
        System.out.println("Age: " + p.getAge());
        System.out.println("Phone number: " + p.getPhoneNumber());
    }
}