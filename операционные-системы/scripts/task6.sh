#!/bin/sh

# Задача 6
# Написать скрипт, которые выведет на экран все файлы,
# размер которых больше 50 Мб в директории /var/log

DIR="/var/log"


for file in "$DIR"/*; do
    if [[ $(stat --format="%s" ${file}) -ge 51200 ]]; then
        echo $file
    fi
done
