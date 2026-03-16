from experta import *
from experta.operator import *
import json


class SystemUnit(Fact):
    cpu_manufacturer = Field(str, mandatory=True)
    cpu_model = Field(str, mandatory=True)
    gpu_model = Field(str, mandatory=True)
    motherboard_model = Field(str)
    ram_gb = Field(int, mandatory=True)
    storage_gb = Field(int)
    storage_type = Field(str)
    power_supply_w = Field(int, mandatory=True)


pc1 = SystemUnit(
    cpu_manufacturer="Intel",
    cpu_model="i5-9400f",
    gpu_model="RTX 2060",
    ram_gb=16,
    storage_gb=256,
    storage_type="SSD",
    power_supply_w=650
)

pc2 = SystemUnit(
    cpu_manufacturer="Intel",
    cpu_model="i5-12400f",
    gpu_model="RTX 3060 TI",
    ram_gb=16,
    storage_gb=256,
    storage_type="SSD",
    power_supply_w=650
)

pc3 = SystemUnit(
    cpu_manufacturer="AMD",
    cpu_model="ryzen 5 5700x",
    gpu_model="RTX 4060 TI",
    ram_gb=16,
    storage_gb=256,
    storage_type="SSD",
    power_supply_w=650
)

pc4 = SystemUnit(
    cpu_manufacturer="AMD",
    cpu_model="ryzen 3 1200",
    gpu_model="Radeon 7",
    ram_gb=8,
    storage_gb=256,
    storage_type="SSD",
    power_supply_w=350
)


class PCExpertSystem(KnowledgeEngine):

    @DefFacts()
    def load_data(self):
        yield pc1
        yield pc2
        yield pc3
        yield pc4

    @Rule(
        OR(
            SystemUnit(gpu_model=P(lambda g: "3060" in g)),
            SystemUnit(gpu_model=P(lambda g: "4060" in g))
        )
    )
    def gaming_gpu(self):
        print("Обнаружена игровая видеокарта")

    @Rule(SystemUnit(cpu_manufacturer=L("AMD")))
    def amd_cpu(self):
        print("Система на базе AMD")

    @Rule(SystemUnit(cpu_manufacturer=L("Intel")))
    def intel_cpu(self):
        print("Система на базе Intel")

    @Rule(
        SystemUnit(ram_gb=MATCH.r),
        TEST(lambda r: r >= 16)
    )
    def enough_ram(self, r):
        print(f"Достаточный объем RAM: {r} ГБ")

    @Rule(
        SystemUnit(storage_gb=MATCH.s),
        TEST(lambda s: s < 512)
    )
    def small_storage(self, s):
        print(f"Недостаточный объем накопителя: {s} ГБ")

    @Rule(NOT(SystemUnit(storage_type=L("HDD"))))
    def no_hdd(self):
        print("===\nВ базе отсутствуют HDD системы\n===")

    @Rule(EXISTS(SystemUnit(power_supply_w=P(lambda w: w >= 650))))
    def strong_psu_exists(self):
        print("Существует система с мощным блоком питания")

    @Rule(
        FORALL(
            SystemUnit(MATCH.id),
            SystemUnit(ram_gb=P(lambda r: r >= 16))
        )
    )
    def all_have_16_ram(self):
        print("===\nВсе системы имеют минимум 16 ГБ RAM\n===")

    @Rule(
        SystemUnit(cpu_model=MATCH.model),
        salience=10
    )
    def show_cpu_model(self, model):
        print(f"Процессор модели: {model}")

    @Rule(SystemUnit(cpu_model=W()))
    def any_cpu(self):
        print("Обнаружена система с процессором")


if __name__ == "__main__":
    engine = PCExpertSystem()
    engine.reset()
    engine.run()
