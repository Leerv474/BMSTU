#!/bin/sh

# изменять имена файлов с верхнего на нижний и наоборот
directory=${1:-$(pwd)}

for file in "$directory"/*; do
    file_name=$(basename "$file")

    if [[ $(stat --format=%s $file) -eq 0 ]]; then
        if [[ "$file_name" =~ [A-Z] ]]; then
            new_name=$(echo "$file_name" | tr 'A-Z' 'a-z')
        fi
        if [[ "$file_name" =~ [a-z] ]]; then
            new_name=$(echo "$file_name" | tr 'a-z' 'A-Z')
        fi

        mv "$file" "$directory/$new_name"
    fi

done

echo "Имена файлов в каталоге '$directory' изменены."

