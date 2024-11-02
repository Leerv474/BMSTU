#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Количество аргументов должно быть больше 1."
    exit 1
fi

SERVER="$1"
shift


COMMAND_LIST=""
for COMMAND in "$@"; do
    COMMAND_LIST+="${COMMAND}; "
done

echo "Выполнение команды на сервере: $SERVER"
ssh "$SERVER" "$COMMAND_LIST"
