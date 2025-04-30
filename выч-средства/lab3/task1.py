input_str = input("Введите строку: ")

lowercase_count = 0
digit_count = 0

for char in input_str:
    if char.islower(): 
        lowercase_count += 1
    elif char.isdigit():
        digit_count += 1

print("Количество букв нижнего регистра:", lowercase_count)
print("Количество цифр:", digit_count)
