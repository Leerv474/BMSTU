import os


def find_large_files_and_folders(root_directory, size_limit_mb=100):
    size_limit_bytes = size_limit_mb * 1024 * 1024  

    for root, dirs, files in os.walk(root_directory):
        
        for file in files:
            file_path = os.path.join(root, file)
            file_size = os.path.getsize(file_path)
            if file_size > size_limit_bytes:
                print(f"Файл: {file_path} - Размер: {file_size / (1024 * 1024):.2f} МБ")

        
        for dir_name in dirs:
            dir_path = os.path.join(root, dir_name)
            dir_size = 0
            for dir_root, _, dir_files in os.walk(dir_path):
                for dir_file in dir_files:
                    dir_size += os.path.getsize(os.path.join(dir_root, dir_file))
            if dir_size > size_limit_bytes:
                print(f"Папка: {dir_path} - Размер: {dir_size / (1024 * 1024):.2f} МБ")


root_directory = input("Введите путь к папке для поиска: ")
find_large_files_and_folders(root_directory)
