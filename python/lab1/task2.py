class String:
    def __init__(self, content):
        self.s = content

    def uncap(self):
        return self.s.lower()

    @staticmethod
    def compare(str1, str2):
        if str1.uncap() == str2.uncap():
            return True
        return False

str1 = String("hello")
str2 = String("HeLLo")
str3 = String("world")

print("hello to HeLLo: ", String.compare(str1, str2))
print("hello to world: ", String.compare(str1, str3))



