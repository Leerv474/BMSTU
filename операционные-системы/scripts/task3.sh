#!/bin/bash
echo "Топ 5 процессов по нагрузке на процессор:"
echo "$(ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head -6)"

echo ""

echo "Топ 5 процессов по занимаемой памяти:"
echo "$(ps -eo pid,comm,%cpu,%mem --sort=-%mem | head -6)"
