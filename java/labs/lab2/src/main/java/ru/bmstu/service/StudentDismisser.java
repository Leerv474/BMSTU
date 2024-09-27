package ru.bmstu.service;

import ru.bmstu.domain.Student;

public class StudentDismisser implements Dismissable{

    @Override
    public void dismiss(Student student) {
        System.out.println("First Name: " + student.getFirstName());
        System.out.println("Second Name: " + student.getSecondName());
        System.out.println("Age: " + student.getAge());
        System.out.println("Phone number: " + student.getPhoneNumber());
        System.out.println("Group: " + student.getGroup());
        System.out.println("Year: " + student.getYear());
    }
}
