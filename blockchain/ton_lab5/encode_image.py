import base64

# читаем картинку
with open("image.webp", "rb") as f:
    data = f.read()

# сырые байты → base64-строка
b64 = base64.b64encode(data).decode("ascii")

# пишем «двоичное представление» в файл (сырой base64 как будто двоичные данные)
with open("image.raw", "wb") as out:
    out.write(base64.b64encode(data))  # как в методичке

print("Base64 строка (укороченная):")
print(b64[:120] + "...")

# Полная строка пригодится для JSON
with open("image_base64.txt", "w") as txt:
    txt.write(b64)

print("Полная base64-строка сохранена в image_base64.txt")
