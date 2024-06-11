CREATE OR REPLACE FUNCTION get_timestamp()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Surname: %, Name: %, Group: %, Year: %', new.student_surname, new.student_name, new.student_group, new student_year;
    RETURN NEW; 
END;
$$ LANGUAGE plpgsql;


CREATE TRIGGER update_trigger 
AFTER UPDATE on students
for each row
    execute FUNCTION get_timestamp();

CREATE TRIGGER delete_trigger 
BEFORE DELETE on students
for each row
    execute FUNCTION get_timestamp();

CREATE OR REPLACE FUNCTION instead_of_insert_trigger_function()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO students (student_surname, student_name, student_group, student_year, student_age) 
    VALUES (new.student_surname, new.student_name, new.student_group, new.student_year, new.student_age);
    raise notice 'INSERTED NEW STUDENT % %', new.student_surname, new.student_name;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE VIEW new_students as 
    SELECT student_surname, student_name, student_group FROM students;

create trigger insert_trigger
instead of update on new_students
for each row
    execute function instead_of_insert_trigger_function();
