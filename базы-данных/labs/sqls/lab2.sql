CREATE procedure promote_year()
language sql 
as $$
    UPDATE students
    set student_year = students.student_year + 1 where student_year <> 4;
$$;

CREATE function average_age()
returns numeric 
as $$
declare
    result numeric;
    amount integer;
BEGIN
    select sum(student_age) into result from students;
    select count(*) into amount from students;
    return result / amount;
END;
$$ language plpgsql;

create or replace procedure promote_year()
language sql
as $$
    begin;
    update users
        set role = "guest" where course = 4;
    update users
        set course = users.course + 1 where users.course <> 4;
    select * from users;
$$
