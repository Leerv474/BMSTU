#!/bin/bash

# Задача 2
# Написать скрипт, который из /etc/passwd выведет домашнюю директорию 
# для пользователя заданного в параметре скрипта, пример файла /etc/passwd:

# str="key:value:another"
# IFS=':' read -r -a result <<< "$str"

if [[ ${#} -ne 1 ]]; then
    echo "Пользователь не был указан"
    exit 1
fi

USER_DATA=$(cat /etc/passwd | grep "${1}")
IFS=':' read -r -a USER_DIR <<< "$USER_DATA"
echo "Домашняя дикертория пользователя ${1}:"
echo "$(ls -a /${USER_DIR[5]})"
