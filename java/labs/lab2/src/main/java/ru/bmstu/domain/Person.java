package ru.bmstu.domain;

public class Person {
    private String firstName;
    private String secondName;
    private int age;
    private String phoneNumber;

    public Person(String firstName, String secondName, int age, String phoneNumber) {
        this.firstName = firstName;
        this.secondName = secondName;
        this.age = age;
        this.phoneNumber = phoneNumber;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getSecondName() {
        return secondName;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }
}