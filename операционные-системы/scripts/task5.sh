#!/bin/sh

# Задача 5
# Написать скрипт, который для всех файлов во временной директории, которые были созданы за текущий месяц,
# и не изменялись в течение недели при нахождении в них строки test поменяет ее на tset.

# Определяем временную директорию
TEMP_DIR="/home/roman/"

CURRENT_MONTH=$(date +"%Y-%m")
ONE_WEEK_AGO=$(date -d '7 days ago' +%s)

find "$TEMP_DIR" -type f -newermt "$CURRENT_MONTH-01" ! -newermt "$CURRENT_MONTH-31" | while read -r file; do
    last_modified=$(stat -c %Y "$file")
    
    if [[ $last_modified -le $ONE_WEEK_AGO ]]; then
        if grep -q "test" "$file"; then
            sed -i 's/test/tset/g' "$file"
            echo "Modified: $file"
        fi
    fi
done

