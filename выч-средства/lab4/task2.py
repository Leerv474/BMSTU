
import os
import re


def search_in_txt_files(directory, regex):
    try:
        
        files = [f for f in os.listdir(directory) if f.endswith('.txt')]

        if not files:
            print("В указанной папке нет текстовых файлов.")
            return

        
        for file_name in files:
            print(f"\nИщем в файле: {file_name}")
            with open(os.path.join(directory, file_name), 'r') as file:
                lines = file.readlines()
                
                
                for line in lines:
                    if re.search(regex, line):
                        print(line.strip())

    except FileNotFoundError:
        print("Указанная папка не найдена.")


directory = input("Введите путь к папке: ")
regex = input("Введите регулярное выражение для поиска: ")

search_in_txt_files(directory, regex)
