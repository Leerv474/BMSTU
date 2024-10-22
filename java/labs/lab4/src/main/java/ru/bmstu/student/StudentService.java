package ru.bmstu.student;

import lombok.AllArgsConstructor;

import java.util.Comparator;
import java.util.List;

@AllArgsConstructor
public class StudentService {
    private List<Student> students;

    public List<Student> listSortedStudents(int age, String subject, int gradeScore) {
        return students.stream().filter(student ->
                student.getAge() > age && student.getSubjects().get(subject) == gradeScore
        ).toList().stream().sorted(Comparator.comparing(Student::getName)).toList();
    }
}
