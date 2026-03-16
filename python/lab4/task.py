from experta import *
from experta.operator import *

class CPU(Fact):
    manufacturer = Field(str, mandatory=True)
    model = Field(str, mandatory=True)
    socket = Field(str, mandatory=True)
    tdp = Field(int, mandatory=True)

class Motherboard(Fact):
    model = Field(str, mandatory=True)
    socket = Field(str, mandatory=True)
    chipset = Field(str)

class GPU(Fact):
    model = Field(str, mandatory=True)
    power_draw = Field(int, mandatory=True)

class RAM(Fact):
    size_gb = Field(int, mandatory=True)

class PowerSupply(Fact):
    power_w = Field(int, mandatory=True)


class PCBuilder(KnowledgeEngine):
    @Rule(
            RAM(size_gb=MATCH.size_gb),
            TEST(lambda size_gb: size_gb < 16)
    )
    def not_enough_ram(self):
        print("Недостаточный объем оперативной памяти")

    @Rule(
            CPU(socket=MATCH.socket),
            Motherboard(socket=MATCH.socket)
    )
    def socket_ok(self):
        print("Сокеты совместимы")

    @Rule(CPU(socket=MATCH.socket),
          NOT(Motherboard(socket=MATCH.socket)))
    def suggest_motherboard(self, socket):
        print(f"Сокеты не совпадают, нужно выбрать материнскую плату с сокетом {socket}")

    @Rule(
        CPU(tdp=MATCH.cpu_tdp),
        GPU(power_draw=MATCH.gpu_power),
        PowerSupply(power_w=MATCH.psu_power),
        TEST(lambda cpu_tdp, gpu_power, psu_power:
             psu_power < (cpu_tdp + gpu_power) * 1.3)
    )
    def not_enough_power(self):
        print("Недостаточная мощность блока питания!")

    @Rule(
        CPU(tdp=MATCH.cpu_tdp),
        GPU(power_draw=MATCH.gpu_power),
        TEST(lambda cpu_tdp, gpu_power: gpu_power > cpu_tdp * 3)
    )
    def gpu_too_powerful(self):
        print("Видеокарта слишком мощная для данного процессора (возможен bottleneck).")


def declare_cpu():
    print("Укажите Процессор")
    manufacturer = input("производитель: ")
    model = input("модель: ")
    socket = input("сокет: ")
    tdp = int(input("tdp: "))
    return CPU(
            manufacturer = manufacturer,
            model = model, 
            socket = socket,
            tdp = tdp
            )

def declare_motherboard():
    print("Укажите материнскую плату")
    model = input("модель: ")
    socket = input("сокет: ")
    chipset = input("чипсет: ")
    return Motherboard(
                model = model,
                socket = socket,
                chipset = chipset
            )

def declare_gpu():
    print("Укажите видеокарту")
    model = input("модель: ")
    power_draw = int(input("энергопотребление: "))
    return GPU(
            model = model,
            power_draw = power_draw
            )

def declare_ram():
    size_gb = int(input("Укажите кол-во ОЗУ: "))
    return RAM(size_gb = size_gb)

def declare_powersupply():
    power_w = int(input("Укажите мощность блока питания: "))
    return PowerSupply(power_w = power_w)

if __name__ == "__main__":
    engine = PCBuilder()
    step = 0
    while True:
        if step == 0:
            com = input("Начать подбор (y/n): ")
            if com == "y":
                step += 1
            engine.reset()
            continue
        
        if step == 1:
            cpu = declare_cpu()
            engine.declare(cpu)
            step += 1
            continue
        if step == 2:
            mb = declare_motherboard()
            engine.declare(mb)
            step += 1
            continue
        if step == 3:
            gpu = declare_gpu()
            engine.declare(gpu)
            step += 1
            continue
        if step == 4:
            ram = declare_ram()
            engine.declare(ram)
            step += 1
            continue
        if step == 5:
            psu = declare_powersupply()
            engine.declare(psu)
            break


    engine.run()
