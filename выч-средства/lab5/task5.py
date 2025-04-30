def sort_numbers_descending(file_name):
    try:
        with open(file_name, 'r') as file:
            numbers = list(map(int, file.read().split()))

        numbers.sort(reverse=True)
        
        print("Числа по убыванию:")
        print(numbers)
    
    except FileNotFoundError:
        print("Файл не найден.")

file_name = input("Введите имя файла с числами: ")
sort_numbers_descending(file_name)
