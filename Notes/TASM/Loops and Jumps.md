#### Loop
– literally loops the labelled code part
```TASM
mov cx, [число] ; число повторейний цикла
loop [label]
```

*Example*
```TASM
	mov cx, 3
label_1:
	mov ah, 9
	mov dx, offset my_string
	int 21h
	loop label_1
```

#### Команды LOOPE/LOOPZ и LOOPNE/LOOPNZ

Эти команды похожи на команду LOOP, но позволяют также организовать и досрочный выход из цикла. ^9800cc

`LOOPE <метка> ; Команды являются синонимами LOOPZ <метка>`

Действие этой команды можно описать следующим образом: `ECX = ECX - 1; if (ECX != 0 && ZF == 1) goto <метка>;`

До начала цикла в регистр ECX необходимо записать число повторений цикла. Команда LOOPE/LOOPZ, как и команда LOOP ставится в конце цикла, а перед ней помещается команда, которая меняет флаг ZF (обычно это команда сравнения CMP). Команда LOOPE/LOOPZ заставляет цикл повторяться ECX раз, но только если предыдущая команда фиксирует равенство сравниваемых величин (вырабатывает нулевой результат, т.е. ZF = 1).

По какой именно причине произошёл выход из цикла надо проверять после цикла. Причём надо проверять флаг ZF, а не регистр ECX, т.к. условие ZF = 0 может появиться как раз на последнем шаге цикла, когда и регистр ECX стал нулевым.

Команда LOOPNE/LOOPNZ аналогична команде LOOPE/LOOPZ, но досрочный выход из цикла осуществляется, если ZF = 1.

Рассмотрим пример: пусть в регистре ESI находится адрес начала некоторого массива двойных слов, а в переменной n – количество элементов массива, требуется проверить наличие в массиве элементов, кратных заданному числу x, и занести в переменную f значение 1, если такие элементы есть, и 0 в противном случае.

```TASM
	mov ebx, x 
	mov ecx, n 
	mov f, 1 
L1: 
	mov eax, [esi] 
	add esi, 4 
	cdq 
	idiv ebx 
	cmp edx, 0 
	loopne L1 
	je L2 
	mov f, 0 
L2:
```
#### Unconditional jump
```TASM
jmp [label]
```
– jumps to the label, without any restrictions. Literally skips the segment of code.

#### Conditional jump
```TASM
cmp [destination], [source]
[conditional jump] [label]
```

^424332

cmp - compares two numeric data fields

| destination | source   |
| ----------- | -------- |
| register    | constant |
| memory      | data     |
|             | register |
|             | memory   |

**signed data conditional jumps:** ^f7e0e6

| Instruction | Description                         | Flags tested |
| ----------- | ----------------------------------- | ------------ |
| JE/JZ       | Jump Equal or Jump Zero             | ZF           |
| JNE/JNZ     | Jump not Equal or Jump Not Zero     | ZF           |
| JG/JNLE     | Jump Greater or Jump Not Less/Equal | OF, SF, ZF   |
| JGE/JNL     | Jump Greater/Equal or Jump Not Less | OF, SF       |
| JL/JNGE     | Jump Less or Jump Not Greater/Equal | OF, SF       |
| JLE/JNG     | Jump Less/Equal or Jump Not Greater | OF, SF, ZF   |

^d87010

**unsigned data conditional jumps:** ^4c3873

| Instruction | Description                        | Flags tested |
| ----------- | ---------------------------------- | ------------ |
| JE/JZ       | Jump Equal or Jump Zero            | ZF           |
| JNE/JNZ     | Jump not Equal or Jump Not Zero    | ZF           |
| JA/JNBE     | Jump Above or Jump Not Below/Equal | CF, ZF       |
| JAE/JNB     | Jump Above/Equal or Jump Not Below | CF           |
| JB/JNAE     | Jump Below or Jump Not Above/Equal | CF           |
| JBE/JNA     | Jump Below/Equal or Jump Not Above | AF, CF       |

^364ec5

**special conditional jumps:** ^5fec12

| Instruction | Description                       | Flags tested |
| ----------- | --------------------------------- | ------------ |
| JC          | Jump If Carry                     | CF           |
| JNC         | Jump If No Carry                  | CF           |
| JO          | Jump If Overflow                  | OF           |
| JNO         | Jump If No Overflow               | OF           |
| JP/JPE      | Jump Parity or Jump Parity Even   | PF           |
| JNP/JPO     | Jump No Parity or Jump Parity Odd | PF           |
| JS          | Jump Sign (negative value)        | SF           |
| JNS         | Jump No Sign (positive value)     | SF           |

^ee4881

#### far ptr and near ptr
> these are available with [[Basics#.386|.386]]

**Near Pointer (near ptr):**
- A near pointer uses only an offset value to address memory. It does not involve segment registers.
- It is used within the same segment of memory and is suitable for addressing data and code within the same segment. It's efficient for small programs and is often used in real mode.
```TASM
jmp near ptr label
```

**Far Pointer (far ptr):**
- A far pointer includes both a segment and an offset value to address memory. It typically requires the use of segment registers, such as `CS` (code segment), `DS` (data segment), `ES` (extra segment), and `SS` (stack segment).
- It is used to access data and code in different segments of memory, such as when calling functions or accessing data in other segments.
```TASM
jmp far ptr label
```
