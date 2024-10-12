package ru.bmstu;

import ru.bmstu.domain.Person;
import ru.bmstu.domain.Student;
import ru.bmstu.exception.InvalidPhoneNumberException;
import ru.bmstu.service.PersonPrinter;
import ru.bmstu.service.StudentDismisser;
import ru.bmstu.service.StudentManager;

import java.util.SortedMap;
import java.util.TreeMap;

public class PersonDemo {
    private static Person person;
    private static Student student;
    public static void creationDemo() {
        try {
            person = new Person("Adam", "Met", 34, "88005555535");
            System.out.println("printDI");
            PersonPrinter.printFI(person);
            System.out.println("printInfo");
            PersonPrinter.printInfo(person);
        } catch (InvalidPhoneNumberException e) {
            e.printStackTrace();
        }

        try {
            student = new Student("Jack", "Met", 27, "855580035", "ИУК5-52Б", 3);
            System.out.println("dismiss");
            SortedMap<String, Integer> subjects = new TreeMap<>();
            subjects.put("Math", 5);
            subjects.put("English", 5);
            subjects.put("Physics", 3);
            subjects.put("History", 4);
            subjects.put("Geography", 4);
            student.setSubjects(subjects);
            StudentDismisser dismisser = new StudentDismisser();
            dismisser.dismiss(student);
        } catch (InvalidPhoneNumberException e) {
            e.printStackTrace();
        }
    }

    public static void studentManagerDemo() {
        StudentManager studentManager = new StudentManager();
        studentManager.addStudent(student);
        System.out.println("find by name");
        System.out.println(studentManager.findByName("Jack Met").getFullName());
        System.out.println("above average 4");
        studentManager.findByAverageGrade(4).forEach(s -> {
            System.out.println(s.getFullName());
        });
        System.out.println("above average 5");
        studentManager.findByAverageGrade(5).forEach(s -> {
            System.out.println(s.getFullName());
        });
        studentManager.deleteByName("Jack Met");
    }
}
