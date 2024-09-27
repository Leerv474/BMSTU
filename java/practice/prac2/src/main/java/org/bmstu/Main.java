package org.bmstu;

import org.bmstu.api.OptionMenu;

import java.util.Scanner;

public class Main {
    private static final Scanner scanner = new Scanner(System.in);
    public static void main(String[] args) {
        OptionMenu.print(scanner);
    }
}