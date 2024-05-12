CREATE OR REPLACE FUNCTION get_timestamp()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Surname: %, Name: %, Group: %, Year: %', new.student_surname, new.student_name, new.student_group, new student_year;
    RETURN NEW; 
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER insert_trigger 
BEFORE INSERT on students
for each row
    execute FUNCTION get_timestamp();


CREATE TRIGGER update_trigger 
BEFORE UPDATE on students
for each row
    execute FUNCTION get_timestamp();

CREATE TRIGGER delete_trigger 
BEFORE DELETE on students
for each row
    execute FUNCTION get_timestamp();
