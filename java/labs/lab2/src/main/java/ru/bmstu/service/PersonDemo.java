package ru.bmstu.service;

import ru.bmstu.domain.Person;
import ru.bmstu.domain.Student;

public class PersonDemo {
    public static void main(String[] args) {
        Person person  = new Person("Adam", "Met", 34, "88005555535");
        System.out.println("printDI");
        PersonPrinter.printFI(person);
        System.out.println("printInfo");
        PersonPrinter.printInfo(person);

        Student student = new Student("Jack", "Met", 27, "855580035", "ИУК5-52Б", 3);
        System.out.println("dismiss");
        StudentDismisser dismisser = new StudentDismisser();
        dismisser.dismiss(student);
    }
}
