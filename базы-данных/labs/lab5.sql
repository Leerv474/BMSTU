create or replace function great_grades(
    out subject varchar(80)
)
returns setof record as
&&
declare
great_grades_list cursor for select subject from journal
where grade = 5;
grades_list record;
begin
    open great_grades_list;
    loop
        fetch next from great_grades_list into grades_list;
        exit when not found;
        subject = grades_list.subject;
        return next;
    end loop;
    close great_grades_list;
end;
&& language plpgsql;

