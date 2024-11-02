#!/bin/bash

if [[ $(whoami) == "fadeyjo" || $(whoami) == "root" ]]; then
    echo "ТЫ ДУРАК?!?!??!?!?"
    exit 1
fi

USER_HOME="/home/$(whoami)"

if [[ $2 == "*" && $3 == "-" ]]; then
    if [[ $# -lt 4 ]]; then
        echo "Не указаны исключённые файлы."
        exit 1
    fi
    excluded_files=("${@:4}")
    excluded_files+=("${1}")
    for excluded_file in "${excluded_files[@]}"; do
        if [[ ! -f "${USER_HOME}/${excluded_file}" ]]; then
            echo "Файл ${excluded_file} не существует."
            exit 1
        fi
    done
    echo "Удаление всех файлов в ${USER_HOME} кроме ${excluded_files[@]}."
    for file in "${USER_HOME}"/*; do
        if ! [[ -f $file ]]; then
            continue
        fi

        is_excluded="false"
        for excluded_file in "${excluded_files[@]}"; do
            if [[ ${excluded_file} == $(basename ${file}) ]]; then
                is_excluded="true"
                continue
            fi
        done
        if ! $is_excluded; then
            rm -f "${file}"
        fi
    done
    echo "Все файлы удалены."
elif [[ "${#}" -eq 2 && -f $2 ]]; then
    if [[ "${1}" != "${2}" ]]; then
        echo "Удаление файла ${2}..."
        rm -f "${2}"
        echo "Файл ${2} удалён."
    else
        echo "Файл не удалён".
    fi
else
    echo "Неправильный формат команды."
fi
