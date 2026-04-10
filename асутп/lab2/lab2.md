# 🔧 База (что нужно)

* tshark
* tcpdump
* `grep`, `awk`, `sed`
* `base64`, `xxd`, `strings`, `gunzip`

Проверка:

```bash
tshark -v
```

---

# **Задание 1: gzip (HTTP)**

### 1. Найти gzip-ответы

```bash
tshark -r compression_gzip.pcap -Y "http.response && http.content_encoding == gzip"
```

### 2. Вытащить тело ответа

```bash
tshark -r compression_gzip.pcap \
  -Y "http.response && http.content_encoding == gzip" \
  -T fields -e http.file_data > data.gz
```

👉 Проблема: иногда `http.file_data` пустой
Тогда:

```bash
tshark -r compression_gzip.pcap -q -z follow,http,raw,0
```

(номер стрима подбираешь)

---

### 3. Распаковать

```bash
gunzip data.gz
```

или:

```bash
zcat data.gz
```

---

### 4. Если мусор:

```bash
cat data | base64 -d
```

---

# **Задание 2: DNS tunnel**

### 1. Вытащить все DNS-запросы

```bash
tshark -r dnstunnel.pcap -T fields -e dns.qry.name
```

---

### 2. Оставить только payload

```bash
tshark -r dnstunnel.pcap -T fields -e dns.qry.name | \
sed 's/\..*//' > data.txt
```

---

### 3. Склеить

```bash
tr -d '\n' < data.txt > joined.txt
```

---

### 4. Пробовать декод:

```bash
base64 -d joined.txt
```

или:

```bash
base32 -d joined.txt
```

---

### Проблема:

* порядок может быть нарушен → сортировать по времени:

```bash
tshark -r dnstunnel.pcap -T fields -e frame.time_epoch -e dns.qry.name | sort -n
```

---

# **Задание 3: SMB**

### 1. Найти файлы

```bash
tshark -r smb_sniff.pcap -Y smb2
```

---

### 2. Попробовать extract:

```bash
tshark -r smb_sniff.pcap --export-objects smb,./out
```

👉 Если не сработает — проблема версии tshark

---

### 3. Анализ файлов:

```bash
cd out
file *
strings *
```

---

# **Задание 4: FTP**

### 1. Найти передачу файла

```bash
tshark -r ftp.pcap -Y ftp.request
```

---

### 2. Вытащить:

```bash
tshark -r ftp.pcap --export-objects ftp-data,./ftp_out
```

---

### 3. Если не работает:

```bash
tshark -r ftp.pcap -q -z follow,tcp,raw,0
```

---

# **Задание 5: MAC по IP**

### Через ARP:

```bash
tshark -r file.pcap -Y "arp" -T fields \
-e arp.src.proto_ipv4 -e arp.src.hw_mac
```

---

### Фильтр:

```bash
tshark -r file.pcap -Y "arp.src.proto_ipv4 == 192.168.0.8"
```

---

# **Задание 6: ICMP data length**

```bash
tshark -r file.pcap -Y icmp -T fields -e data.len
```

---

👉 Если пусто:

```bash
tshark -r file.pcap -V -Y icmp | grep "Data"
```

---

# **Задание 7: DNS A-запросы**

```bash
tshark -r file.pcap \
-Y "dns.qry.type == 1 && ip.dst == 208.67.220.220" \
| wc -l
```

---

# ⚠️ Основные проблемы (реально важные)

Вот где ты застрянешь:

### 1. `http.file_data` пустой

→ используй `follow,http,raw`

---

### 2. DNS туннель не декодится

→ значит:

* не тот порядок
* не та кодировка
* лишние домены не убрал

---

### 3. SMB / FTP export не работает

→ версия tshark старая

---

### 4. Бинарный мусор

→ всегда:

```bash
strings file
xxd file
file file
```

