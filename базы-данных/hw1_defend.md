## Online query
Tables:
- Users
- Polls 
- Questions
- Options
- Responses


#### User table:
- id
- login
- password
- email

#### Polls table:
- id
- title
- release\_date

#### Questions table:
- id
- question_text
- question_type
- poll_id FOREIGN KEY

#### Table options table:
- id
- question_id
- option_text

#### response table:
- id
- user_id
- question_id
- option_id


# Вопросы
Базы данных - организованная в соотвествии с опредленными правилами, совокупность данных, характеризующая актуальное состояние некоторой предметной области и используемая для взаимодействия с пользователем информационной системы.

Информационная система - это совокупность содержащейся в базах данных информации и обеспечивающих ее обработку информационными технологий и технических средств.

Предметная область - часть реального мира, которая должна быть адекватно в полном информационном объеме представлена в Базе данных.

