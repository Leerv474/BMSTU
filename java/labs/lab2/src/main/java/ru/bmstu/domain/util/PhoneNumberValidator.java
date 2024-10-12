package ru.bmstu.domain.util;

import java.util.regex.Pattern;

public class PhoneNumberValidator {
    private final Pattern pattern = Pattern.compile("^\\+7\\s?\\(?\\d{3}\\)?[\\s.-]?\\d{3}[\\s.-]?\\d{2}[\\s.-]?\\d{2}$");

    public boolean validate(String phoneNumber) {
        return pattern.matcher(phoneNumber).matches();
    }
}
