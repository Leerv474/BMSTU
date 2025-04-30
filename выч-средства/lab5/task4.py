def count_tripled_odds(file_name):
    try:
        with open(file_name, 'r') as file:
            numbers = map(int, file.read().split())
        

        tripled_odds = [num for num in numbers if num % 2 != 0 and num % 3 == 0]
        
        print(f"Количество утроенных нечетных чисел: {len(tripled_odds)}")
    
    except FileNotFoundError:
        print("Файл не найден.")

file_name = input("Введите имя файла с числами: ")
count_tripled_odds(file_name)
