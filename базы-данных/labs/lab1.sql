CREATE TABLE student (
    student_id denerated by default as identity primary key,
    student_surname varchar(80) not null,
    student_name varchar(80) not null,
    student_age integer not null,
    student_group varchar(10) not null
);
