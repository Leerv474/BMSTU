import re


def replace_placeholders_in_file(file_name):
    try:
        
        with open(file_name, 'r') as file:
            content = file.read()
        
        
        print("Исходный текст:")
        print(content)
        
        
        adjective = input("Введите имя прилагательное: ")
        noun_1 = input("Введите имя существительное: ")
        verb = input("Введите глагол: ")
        noun_2 = input("Введите имя существительное: ")

        
        content = content.replace("ADJECTIVE", adjective)
        content = content.replace("NOUN", noun_1, 1)  
        content = content.replace("VERB", verb)
        content = content.replace("NOUN", noun_2, 1)  

        
        print("\nРезультат замены:")
        print(content)

        
        with open('modified_file.txt', 'w') as file:
            file.write(content)
        
        print("\nИзмененный текст сохранен в файле 'modified_file.txt'.")

    except FileNotFoundError:
        print("Файл не найден. Пожалуйста, убедитесь, что файл существует.")


file_name = input("Введите имя текстового файла: ")
replace_placeholders_in_file(file_name)
