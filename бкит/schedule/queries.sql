
--create table classes(
--    id integer auto_increment primary key,
--    class_name varchar(255) not null,
--    classroom varchar(255),
--    teacher varchar(255),
--    weekday integer not null,
--    class_number integer not null,
--    group_name varchar(255) not null,
--    subgroup integer not null
--);

insert into classes (class_name, classroom, teacher, weekday, class_number, group_name, subgroup)
values
    ("Социология лекц.", "УАК1_4.03", "Яловенко Я.В.", 2, 2, "ИУК5-52Б", 0),
    ("Операционные системы лекц.", "УАК1_2.10", "Алёхина Е.Д.", 2, 3, "ИУК5-52Б", 0),
    ("Операционные системы лаб.", ),
    ("Операционные системы упр."),
    ("Модели данных"),
    ("Экология лекц."),
    ("Экология упр."),
    ("Сетевые технологии в авт. СОИиУ лекц."),
    ("Сетевые технологии в авт. СОИиУ упр."),
    ("Иностранный язык"),
    ("Физическая культура"),
    ("Программирование на языке Java лекц."),
    ("Программирование на языке Java лаб."),
