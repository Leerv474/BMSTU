#### shl
– shifts the bits to the left
```TASM
shl [receiver], [source]
```
receiver is register, and source is the number 
**ALSO** can be used to double the value.

**example**
```TASM
mov ax, 100b
shl ax, 1   ; now ax contains 1000b
```

#### shr
– likewise shl, shifts bit to the right
**example**
```TASM
mov ax, 100b
shr ax, 1        ; now ax contains 10b
```
**ALSO** can be used to half the value.