package ru.bmstu.service;

import ru.bmstu.domain.Student;

import java.util.SortedMap;

public class StudentDismisser implements Dismissable{

    @Override
    public void dismiss(Student student) {
        System.out.println("First Name: " + student.getFirstName());
        System.out.println("Second Name: " + student.getSecondName());
        System.out.println("Age: " + student.getAge());
        System.out.println("Phone number: " + student.getPhoneNumber());
        System.out.println("Group: " + student.getGroup());
        System.out.println("Year: " + student.getYear());
        System.out.println("The list of subjects:");
        SortedMap<String, Integer> subjects = student.getSubjects();
        subjects.forEach((key, value) -> System.out.println(key + ": " + value));
    }
}
