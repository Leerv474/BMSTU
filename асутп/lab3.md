# 1. Compression_gzip

```bash
tshark -r compression_gzip.pcap -Y http
```

```bash
tshark -r compression_gzip.pcap -T fields -e tcp.stream | sort -n | uniq
```

```bash
tshark -r compression_gzip.pcap -qz follow,tcp,ascii,0
```

Посмотреть выгруженные файлы:

```bash
ls http_dump
file http_dump/*
```

Если gzip:

```bash
gunzip file.gz
cat file
```

Если флаг закодирован (base64 часто):

```bash
cat file | base64 -d
```

Иногда уже есть:

```bash
strings data.gzip
zcat data.gzip
```

(у тебя уже есть `data.gz`, `data.gzip` — возможно это уже извлеченное тело)

---

# 2 DNS Tunnel

Тут флаг обычно разбит по subdomain.

## Посмотреть DNS queries

```bash
tshark -r dnstunnel.pcapng -Y dns.qry.name -T fields -e dns.qry.name
```

Часто увидишь что-то вроде:

```text
68656c6c6f.attacker.com
776f726c64.attacker.com
```

Это hex.

Собрать:

```bash
tshark -r dnstunnel.pcapng -Y dns.qry.name -T fields -e dns.qry.name \
| cut -d. -f1 > chunks.txt
```

Склеить:

```bash
tr -d '\n' < chunks.txt | xxd -r -p
```

Если base32:

```bash
tr -d '\n' < chunks.txt | base32 -d
```

Если TXT tunnel:

```bash
tshark -r dnstunnel.pcapng -Y dns.txt
```

Очень часто флаг лежит именно так.

---

# 3 smb_sniff

Нужно вытащить файл из SMB.

## Посмотреть SMB:

```bash
tshark -r smb_sniff.pcapng -Y smb
```

или:

```bash
tshark -r smb_sniff.pcapng -Y smb2
```

## Экспорт файлов:

```bash
tshark -r smb_sniff.pcapng --export-objects smb,smbfiles
```

Потом:

```bash
ls smbfiles
file smbfiles/*
strings smbfiles/*
```

Иногда флаг внутри txt/doc:

```bash
cat smbfiles/filename
```

Если export не сработал:

```bash
tshark -r smb_sniff.pcapng -qz follow,tcp,ascii,0
```

---

# 4 FTP

FTP вообще простой.

## Credentials:

```bash
tshark -r ftp.pcap -Y ftp.request
```

Ищи:

* USER
* PASS
* RETR

## Вытащить файлы:

```bash
tshark -r ftp.pcap --export-objects ftp,ftp_out
```

(у тебя папка `ftp_out` уже есть)

```bash
ls ftp_out
cat ftp_out/*
strings ftp_out/*
```

Флаг/содержимое файла там.

---

# 5 MAC адрес 192.168.0.8

Смотри ARP:

```bash
tshark -r mac.pcap -Y arp
```

Фильтр:

```bash
tshark -r mac.pcap -Y "arp.src.proto_ipv4==192.168.0.8" \
-T fields -e arp.src.hw_mac
```

или

```bash
tshark -r mac.pcap -Y "ip.addr==192.168.0.8" \
-T fields -e eth.src
```

---

# 6 длина data в ICMP

```bash
tshark -r wireshark3.pcap -Y icmp
```

Вывести поле payload length:

```bash
tshark -r wireshark3.pcap -Y icmp \
-T fields -e data.len
```

или:

```bash
tshark -r wireshark3.pcap -Y icmp -V | grep "Data ("
```

Обычно видно:

```text
Data (56 bytes)
```

Ответ — длина поля данных.

---

# 7 DNS A-запросы к 208.67.220.220

Просто посчитать:

```bash
tshark -r "Фильтры в Wireshark.pcap" \
-Y 'dns.flags.response==0 && dns.qry.type==1 && ip.dst==208.67.220.220' \
| wc -l
```

Где:

* `response==0` — запросы
* `qry.type==1` — A records

---
