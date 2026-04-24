import hashlib

class User:
    def __init__(self, login, passwords):
        self.login = login
        self.passwords = [self.hash(p) for p in passwords]
        self.index = 0

    def hash(self, text):
        return hashlib.sha256(text.encode()).hexdigest()

    def authenticate(self, password_input):
        if self.index >= len(self.passwords):
            print("Пароли закончились")
            return False

        if self.hash(password_input) == self.passwords[self.index]:
            print("Доступ разрешён")
            self.index += 1
            return True
        else:
            print("Доступ запрещён")
            return False


user = User("admin", ["AXY", "ZZQ", "13J"])

user.authenticate("AXY")  
user.authenticate("AXY") 
user.authenticate("ZZQ")
user.authenticate("ZZQ")
