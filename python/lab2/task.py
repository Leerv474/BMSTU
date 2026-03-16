from experta import Fact, Field

class SystemUnit(Fact):
    cpu_manufacturer = Field(str, mandatory=True)
    cpu_model = Field(str, mandatory=True)
    gpu_model = Field(str, mandatory=True)
    motherboard_model = Field(str, mandatory=True)
    ram_gb = Field(int, mandatory=True)
    storage_gb = Field(int)
    storage_type = Field(str)
    power_supply_w = Field(int, mandatory=True)


pc1 = SystemUnit(
    cpu_manufacturer = "Intel",
    cpu_model = "i5-9400f",
    gpu_model = "RTX 2060",
    ram_gb = 16,
    storage_gb=256,
    storage_type = "SSD",
    power_supply_w = 650
)
    
pc2 = SystemUnit(
    cpu_manufacturer = "Intel",
    cpu_model = "i5-12400f",
    gpu_model = "RTX 3060 TI",
    ram_gb = 16,
    storage_gb=256,
    storage_type = "SSD",
    power_supply_w = 650
)

pc3 = SystemUnit(
    cpu_manufacturer = "AMD",
    cpu_model = "ryzen 5 5700x",
    gpu_model = "RTX 4060 TI",
    ram_gb = 16,
    storage_gb=256,
    storage_type = "SSD",
    power_supply_w = 650
)

import json

facts = [pc1, pc2, pc3]

with open("system_units.json", "w", encoding="utf-8") as f:
    json.dump(facts, f, ensure_ascii=False, indent=4)
