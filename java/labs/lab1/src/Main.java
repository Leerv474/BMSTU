import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        task1();
        task2();
        task3();
        task4();
    }

    public static void task1() {
        int a = 10;
        int b = 20;
        int c = 30;
        int d = 40;

        if (a > 5 && b < 25) {
            System.out.println("a > 5 && b < 25");
        } else if (a > 15 || b == 20) {
            System.out.println("a > 15 || b == 20");
        } else {
            System.out.println("false");
        }

        if (a > 5 && b < 25 && c == 30) {
            System.out.println("true");
        } else {
            System.out.println("false");
        }

        if ((a > 5 && b < 25) || (c == 30 && d > 35)) {
            System.out.println("true");
        } else {
            System.out.println("false");
        }

        int day = 3;

        switch (day) {
            case 1:
                System.out.println("Понедельник");
                break;
            case 2:
                System.out.println("Вторник");
                break;
            case 3:
                System.out.println("Среда");
                break;
            case 4:
                System.out.println("Четверг");
                break;
            case 5:
                System.out.println("Пятница");
                break;
            default:
                System.out.println("Выходной");
                break;
        }

        String result = (a > b) ? "a > b" : "a <= b";
        System.out.println(result);
    }

    public static void task2() {
        for (int i = 0; i < 10; i++) {
            System.out.print(i + " ");
        }

        int happiness = 30;
        while (happiness > 0) {
            if (happiness == 1) {
                System.out.println("I wanna eat");
                continue;
            }
            happiness--;
        }
        Scanner scanner = new Scanner(System.in);
        String line;
        do {
            line = scanner.nextLine();
            if (line.equals("quit")) {
                break;
            }
        } while (line.isEmpty());

        int[][] matrix = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
        };

        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void task3() {
        int intValue = 10;
        Integer integerValue = intValue;
        int newIntValue = integerValue;

        boolean boolValue = true;
        Boolean booleanValue = boolValue;
        boolean newBoolValue = booleanValue;

        long longValue = 100L;
        Long longObjectValue = longValue;
        long newLongValue = longObjectValue;

        Integer nullInteger = null;
        try {
            int intFromNull = nullInteger;
        } catch (NullPointerException e) {
            e.printStackTrace();
        }
    }

    public static void task4() {
        String str = "Жизнь прекрасна";

        String replacedStr = str.replace("Жизнь", "Любовь");
        System.out.println("После замены: " + replacedStr);

        String trimmedStr = str.trim();
        System.out.println("trim: " + trimmedStr);

        String[] parts = str.trim().split(" ");
        System.out.println("split: ");
        for (String part : parts) {
            System.out.println(part);
        }

        String str1 = "Hello";
        String str2 = "Hello";
        String str3 = new String("Hello");

        System.out.println("str1 == str2: " + (str1 == str2));
        System.out.println("str1 == str3: " + (str1 == str3));

        System.out.println("str1.equals(str3): " + str1.equals(str3));

        String str4 = "hello";
        System.out.println("str1.equalsIgnoreCase(str4): " + str1.equalsIgnoreCase(str4));

        StringBuilder sb = new StringBuilder();

        sb.append("Hello");
        sb.append(" ");
        sb.append("World");
        System.out.println("append" + sb.toString());

        sb.delete(5, sb.length());
        System.out.println("delete:" + sb.toString());
    }
}