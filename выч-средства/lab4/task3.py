import re


def find_longest_call(file_name):
    try:
        with open(file_name, 'r') as file:
            content = file.readlines()
        
        longest_call_duration = 0
        longest_call_number = ""
        
        
        phone_pattern = r'Номер абонента:\s+(\+?\d+)'  
        duration_pattern = r'Продолжительность:\s+(\d+)\s+минут'  

        
        i = 0
        while i < len(content):
            if re.search(phone_pattern, content[i]) and re.search(duration_pattern, content[i + 1]):
                phone_number = re.search(phone_pattern, content[i]).group(1)
                duration = int(re.search(duration_pattern, content[i + 1]).group(1))
                
                
                if duration > longest_call_duration:
                    longest_call_duration = duration
                    longest_call_number = phone_number

                i += 2  
            else:
                i += 1

        if longest_call_number:
            print(f"Самый продолжительный разговор был с номером {longest_call_number}, продолжительность: {longest_call_duration} минут.")
        else:
            print("Не удалось найти данные о разговоре.")

    except FileNotFoundError:
        print("Файл не найден.")


file_name = input("Введите имя файла с переговорами: ")
find_longest_call(file_name)
