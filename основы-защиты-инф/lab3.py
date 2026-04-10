def vigenere_encrypt(text, key):
    result = ""
    key = key.upper()
    text = text.upper()
    
    key_index = 0
    
    for char in text:
        if char.isalpha():
            t = ord(char) - ord('A')
            k = ord(key[key_index % len(key)]) - ord('A')
            
            c = (t + k) % 26
            result += chr(c + ord('A'))
            
            key_index += 1
        else:
            result += char
            
    return result


def vigenere_decrypt(cipher, key):
    result = ""
    key = key.upper()
    cipher = cipher.upper()
    
    key_index = 0
    
    for char in cipher:
        if char.isalpha():
            c = ord(char) - ord('A')
            k = ord(key[key_index % len(key)]) - ord('A')
            
            t = (c - k) % 26
            result += chr(t + ord('A'))
            
            key_index += 1
        else:
            result += char
            
    return result


text = "HELLO"
key = "KEY"

encrypted = vigenere_encrypt(text, key)
decrypted = vigenere_decrypt(encrypted, key)

print("Зашифровано:", encrypted)
print("Расшифровано:", decrypted)
