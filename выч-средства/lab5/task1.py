import os
import shutil


def copy_files_with_extension(src_directory, dst_directory, extension):
    if not os.path.exists(dst_directory):
        os.makedirs(dst_directory)  

    
    for root, dirs, files in os.walk(src_directory):
        for file in files:
            if file.endswith(extension):  
                src_file = os.path.join(root, file)
                dst_file = os.path.join(dst_directory, file)

                if os.path.abspath(src_file) != os.path.abspath(dst_file):
                    shutil.copy(src_file, dst_file)
                    print(f"Файл {file} скопирован в {dst_directory}")


src_directory = input("Введите путь исходной папки: ")
dst_directory = input("Введите путь целевой папки: ")
extension = input("Введите расширение файла (например, .pdf): ")

copy_files_with_extension(src_directory, dst_directory, extension)

