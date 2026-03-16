class Calc:
    def add(self, x, y):
        return x + y

    def sub(self, x, y):
        return x - y

    def mult(self, x, y):
        return x * y

    def div(self, x, y):
        return x / y

calc = Calc()

print(calc.add(1, 2))
print(calc.sub(1, 2))
print(calc.mult(1, 2))
print(calc.div(1, 2))
