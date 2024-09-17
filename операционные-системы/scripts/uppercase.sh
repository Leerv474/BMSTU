#!/bin/sh

directory=${1:-$(pwd)}

for file in "$directory"/*; do
    file_name=$(basename "$file")
    
    if [[ "$file_name" =~ [A-Z] ]]; then
        new_name=$(echo "$file_name" | tr 'A-Z' 'a-z')
    else
        new_name=$(echo "$file_name" | tr 'a-z' 'A-Z')
    fi
    
    mv "$file" "$directory/$new_name"
done

echo "Имена файлов в каталоге '$directory' изменены."

