#### Hello world
``` TASM
.model small
.stack 100h                           ; stack storage allocation
.data                                 ; data segment
helloSTR db 'Hello world!$'           ; helloSTR variable allocation
.code                                 ; code segment
start:                                ; initializing start of the program
	mov ax, @data                     ; linking contains of DATA segment to AX register
	mov ds, ax                        ; moves contains of AX register to ds .note#1 to make space
	mov ah, 09h                       ; sends a string to AH which is in AX
	mov dx, offset helloSTR           ; puts string into the space sreated earlier 
	int 21h                           ; implements actions above

	mov ax, 4c00h                     ; function to terminate the program
	int 21h                           ; implemets function
end start                             ; ends initialized code segment
```
#### Input from console
```TASM
;----
string db 100, 100 dup('$')
;----
mov ah, 0ah
lea dx, string
int 21h

mov string+1, 0ah ; +1 cause we dont need the first element of an array
```
thus we have a **string** variable we can work with

#### Convert to numbers from console
```TASM
numberInput MACRO var:req
    local exit, convert, greater, break, isDigit, skip
    push ax
    push bx
    push dx
    push cx
    push si

    mov ah, 0ah
    mov dx, offset input_buffer
    int 21h

    xor ax, ax

    mov si, 2
    cmp input_buffer[2], '-'
    jne convert

    inc si
    convert:
        mov al, input_buffer[si]
        cmp ax, '0'
        jge greater
        jmp break
        greater:
            cmp ax, '9'
            jle isDigit
            jmp break

        isDigit:
            and ax, 0fh
            push ax
            mov ax, result_buffer
            mov bl, 10
            mul bl
            mov result_buffer, ax
            pop ax
            add result_buffer, ax
        inc si
    jmp convert

    break:
        cmp ax, 0dh
        jne far ptr input_error1L
        
    skip:
        mov ax, result_buffer
        mov var, ax

        cmp input_buffer[2], '-'
        jne exit
        neg var

    exit:
        mov result_buffer, 0
        clearInput
  
        pop si
        pop cx
        pop dx
        pop bx
        pop ax
ENDM
```

#### Прокрутка экрана (отчистка экрана)
```TASM
mov ax, 0600H
mov bh, 07h   ; цвет
mov cx, 0000  ; сдвиг вправо вверх
mov dx, 184FH
int 10h
```

параметры bh:

| источник | цвет                |
| -------- | ------------------- |
| 0        | all black           |
| 01       | black and blue      |
| 02       | black and green     |
| 07       | black and white     |
| 3fh      | turquoise and white |

#### Установка курсора
```TASM
mov ah, 2  ; set the cursor
mov dh, 8  ; row number
mov dl, 28 ; column number
mov bh, 0  ; page number
int 10h
```

**In DosBOX:**
- 24 is the max visible row
- 79 is the max visible column
#### Считать символ с консоли
```TASM
mov ah, 01h
int 21h
```
– data gets put into **al**

#### Вывод числа в консоль
```TASM
numberOutput MACRO num:req
    local exit, skip, pushing, outputLoop
    push ax
    push bx
    push dx
    push cx
  
    mov ax, num
    cmp ax, 0
    jnl skip
    printSymbol '-'
    neg ax

    skip:
    mov bx, 10
    xor cx, cx

    pushing:
        xor dx, dx
        div bx
        push dx
        inc cx
    test ax, ax
    jnz pushing

    mov ah, 02h
    outputLoop:
        pop dx
        add dx, '0'
        int 21h
    loop outputLoop

    exit:
    pop cx
    pop dx
    pop bx
    pop ax
ENDM
```

#### Cut the char from string at the index
```TASM
strpopc MACRO str:req, index:req
    local exit, bufLoop, skip, loadLoop, exitBuf, skipError
    push ax
    push bx
    push dx
    push cx
    push di
    push si

    xor ax, ax
    xor si, si
    xor di, di
    xor cx, cx
    bufLoop:
        cmp si, index
        je skip
        
        mov al, str[si]
        mov buffer[di], al
        inc di
        inc cx
        
        skip:
        
        inc si
        cmp al, '$'
        je exitBuf
    jmp bufLoop
    exitBuf:
        cmp cx, index
        jne skipError
        mov ah, 09h
        mov dx, offset strpopc_error
        int 21h
        jmp exit

    skipError:
    xor si, si
    loadLoop:
        mov al, buffer[si]
        mov str[si], al
        inc si
    cmp cx, si
    jne loadLoop

    exit:
    pop si
    pop di
    pop cx
    pop dx
    pop bx
    pop ax
ENDM
```