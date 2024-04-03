#### and
```TASM
and operand1, operand2
```
– bitwise AND
>sets the resultant bit to 1 if both compared bits contain 1, otherwise sets to 0

| operand                | data |
| ---------------------- | ---- |
| Operand1:              | 0101 |
| Operand2:              | 0011 |
| ---------------------- | ---- |
| After AND  → Operand1: | 0001 |
#### or
```TASM
or operand1, operand2
```
– bitwise OR
> sets the resultant bit to 1 if at least one of two compared bits contain 1, otherwise sets to 0

| operand                | data |
| ---------------------- | ---- |
| Operand1:              | 0101 |
| Operand2:              | 0011 |
| ---------------------- | ---- |
| After OR  → Operand1:  | 0111 |

#### xor
```TASM
xor operand1, operand2
```
– bitwise XOR (исключающее или)
> sets the resultant bit to 1 only if two compared bits are different, otherwise sets to 0

| operand                | data |
| ---------------------- | ---- |
| Operand1:              | 0101 |
| Operand2:              | 0011 |
| ---------------------- | ---- |
| After XOR  → Operand1: | 0110 |

**to set registers to 0** it's faster to XOR them to themselves
```TASM
mov ax, 0  ; ax = 0000

xor ax, ax ; ax = 0000
```
results are the same but the speed with XORing is higher
#### test
```TASM
test operand1, operand2
```
– bitwise AND, but it **does not** change any values of operands 
#### not
```TASM
not operand1
```
– bitwise NOT, which reverses the bits of in and operand
> The operand can be either in a register or in the memory

| operand                | data |
| ---------------------- | ---- |
| Operand:               | 0101 |
| ---------------------- | ---- |
| After XOR  → Operand1: | 1010 |
