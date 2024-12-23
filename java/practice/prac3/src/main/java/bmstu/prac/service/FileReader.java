package bmstu.prac.service;

import lombok.Data;
import lombok.RequiredArgsConstructor;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.AbstractMap.SimpleEntry;
import java.util.List;

@RequiredArgsConstructor
@Data
public class FileReader implements Runnable {
    private final Path filePath;
    private SimpleEntry<Double, Integer> pair;

    @Override
    public void run() {
        this.pair = totalSalaryAndEmployees(filePath);
    }

    private SimpleEntry<Double, Integer> totalSalaryAndEmployees(Path filePath) {
        double totalSalary = 0.0;
        try {
            List<String> contents = Files.readAllLines(filePath);
            for (String line : contents) {
                String[] words = line.split(" ");
                totalSalary += Double.parseDouble(words[2]);
            }
            return new SimpleEntry<>(totalSalary, contents.size());
        } catch (IOException e) {
            e.printStackTrace();
        }
        return new SimpleEntry<>(0.0, 0);
    }
}
