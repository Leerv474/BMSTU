CREATE OR REPLACE FUNCTION great_grades(
    OUT subject VARCHAR(80)
)
RETURNS SETOF VARCHAR(80) AS
$$
DECLARE
    great_grades_list CURSOR FOR SELECT journal.subject FROM journal WHERE grade = 5;
    grades_list RECORD;
BEGIN
    OPEN great_grades_list;
    LOOP
        FETCH NEXT FROM great_grades_list INTO grades_list;
        EXIT WHEN NOT FOUND;
        subject := grades_list.subject;
        RETURN NEXT;
    END LOOP;
    CLOSE great_grades_list;
END;
$$ LANGUAGE plpgsql;

CREATE INDEX good_grade on journal (grade) where grade = 4;

SELECT * FROM journal WHERE grade = 4;
