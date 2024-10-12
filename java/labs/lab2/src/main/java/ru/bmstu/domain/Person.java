package ru.bmstu.domain;

import ru.bmstu.domain.util.PhoneNumberValidator;
import ru.bmstu.exception.InvalidPhoneNumberException;

public class Person {
    private String firstName;
    private String secondName;
    private int age;
    private String phoneNumber;
    private final PhoneNumberValidator phoneNumberValidator = new PhoneNumberValidator();

    public Person(String firstName, String secondName, int age) {
        this.firstName = firstName;
        this.secondName = secondName;
        this.age = age;
    }

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
        if (!phoneNumberValidator.validate(phoneNumber)) {
            throw new InvalidPhoneNumberException();
        }
        this.phoneNumber = phoneNumber;
    }
}