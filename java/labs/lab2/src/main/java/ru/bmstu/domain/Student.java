package ru.bmstu.domain;

import java.util.SortedMap;

public class Student extends Person {
    private String group;
    private int year;
    private SortedMap<String, Integer> subjects;

    public Student(String firstName, String secondName, int age, String phoneNumber, String group, int year) {
        super(firstName, secondName, age, phoneNumber);
        this.group = group;
        this.year = year;
    }

    public void setGroup(String group) {
        this.group = group;
    }

    public String getGroup() {
        return this.group;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public int getYear() {
        return this.year;
    }

    public void setSubjects(SortedMap<String, Integer> subjects) {
        this.subjects = subjects;
    }

    public SortedMap<String, Integer> getSubjects() {
        return this.subjects;
    }

    public String getFullName() {
        return String.format("%s %s", this.getFirstName(), this.getSecondName());
    }
}
