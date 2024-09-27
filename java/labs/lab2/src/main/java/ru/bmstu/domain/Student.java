package ru.bmstu.domain;

public class Student extends Person {
    private String group;
    private int year;

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
}
