def merge_files_reverse_order(file1, file2, output_file):
    try:
        with open(file1, 'r') as f1, open(file2, 'r') as f2:
            content1 = f1.read()
            content2 = f2.read()[::-1]  

        with open(output_file, 'w') as out:
            out.write(content1 + content2)

        print(f"Файлы {file1} и {file2} успешно объединены в {output_file}.")
    
    except FileNotFoundError:
        print("Один или оба файла не найдены.")


file1 = input("Введите имя первого файла: ")
file2 = input("Введите имя второго файла: ")
output_file = input("Введите имя третьего файла для записи: ")

merge_files_reverse_order(file1, file2, output_file)
