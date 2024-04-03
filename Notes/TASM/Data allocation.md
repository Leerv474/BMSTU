```TASM
.data        ; DATA SEGMENT
	variable_name directive data
```
#### Allocating data space
| directive | purpose           | storage space |
| --------- | ----------------- | ------------- |
| db        | define byte       | 1 byte        |
| dw        | define word       | 2 bytes       |
| dd        | define doubleword | 4 bytes       |
| dq        | define quadword   | 8 bytes       |
| dt        | define ten bytes  | 10 bytes      |

#### Allocating Storage Space for Uninitialized Data
```TASM
variable_name directive ?
```
но в используя такую запись в переменной будет храниться мусор.

Если нужно, чтобы в переменной хранился ноль, то нужно соответственно списать ноль.
```TASM
variable_name directive 0
```
#### Numbers in TASM
| number | binary | hexa |
| ------ | ------ | ---- |
| 0      | 0b     | 0h   |
| 5      | 101b   | 5h   |
| 15     | 1111b  | fh   |

to display numbers to the console this [[Programs#Вывод числа в консоль |program]] is used
#### Arrays
```TASM
array_name [directive] [elements separated by comma]
```

- The name of and array is treated like pointer to the first element of array.
- Ways to access individual elements via indexing 
	`[array + si]` or `array[si]`
- Incrementing array shifts the start of an array to the next element
##### dup()
```TASM
variable_name [directive] [number of elements] dup ([element])
```
creates \[number of elements] amount of \[element] in the brackets
typically used for predefining the length of arrays

**Нюанс!**
Переменные хранятся в `ds` в обратном порядке.
Значение переменной `0102h` будет записана в двух байтах как `02 01`. Таким образом младший разряд находится слева, старший - справа.

##### equ
– creates constant value, which can be reused multiple times in code and **cannot** be changed.
```TASM
constant_name equ number
```

##### $-
– gets the length of an array
```TASM
size_variable equ $-variable_name
```

#### define string
– to define string, a normal variable has to be defined and the value of string has to be placed in apostrophes 
```TASM
my_string db 'this is my string', '$'
```
at the end of the string `$` has to be place in order to tell the end of the string
- string work just as the array
- In order to define an empty string `dup(0)` has to be used, which fills string with NULL values

to display string interruption `int 21h` by number `09h` is used:
![[Прерывания#^1b7bae]]
