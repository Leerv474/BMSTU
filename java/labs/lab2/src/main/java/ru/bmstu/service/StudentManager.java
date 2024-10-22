package ru.bmstu.service;

import ru.bmstu.domain.Student;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.SortedMap;
import java.util.stream.Collectors;

public class StudentManager {
    private List<Student> students = new ArrayList<>();

    public void addStudent(Student student) {
        students.add(student);
    }

    public Student findByName(String name) {
        return students.stream()
                .filter(student ->
                        student.getFullName().equals(name)
                ).collect(Collectors.toList()).get(0);
    }

    public List<Student> findByAverageGrade(double minAverage) {
        double avg = 0;
        List<Student> result = new ArrayList<>();
        for (Student student : this.students) {
            SortedMap<String, Integer> subjects = student.getSubjects();
            avg = subjects.values().stream().mapToDouble(Integer::doubleValue).average().orElse(0.0);
            if (avg > minAverage) {
                result.add(student);
            }
        }
        return result;
    }

    public void deleteByName(String name) {
        students.remove(
                findByName(name)
        );
    }

}
