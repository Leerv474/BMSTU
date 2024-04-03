## Turbo assembler x8086
16-bit or 32-bit architecture for developing in DOS and early Windows environments.

### Program body
```TASM
.model small
.stack                                 ;  STACK SEGMENT
.data
	variable_name [directive] [data]   ;  DATA SEGMENT
.code
start:
                                       ;  CODE SEGMENT
end start
end
```
### Memory Segments
- **Data segment** − It is represented by **.data** section and the **.bss**. The .data section is used to declare the memory region, where data elements are stored for the program. This section cannot be expanded after the data elements are declared, and it remains static throughout the program.
    The .bss section is also a static memory section that contains buffers for data to be declared later in the program. This buffer memory is zero-filled.

- **Code segment** − It is represented by **.text** section. This defines an area in memory that stores the instruction codes. This is also a fixed area.

- **Stack** − This segment contains data values passed to functions and procedures within the program.

to address to those segments in code **ds**, **cs**, **ss** need to be used

### Compiling with DOSbox
```console
tasm program_name    # compiles .asm and creates .obj
tlink program_name   # creates .exe with .obj
program_name         # starts the program
```

### .386
– directive instructs TASM to generate code for 32-bit protected mode, which is a feature of the 80386 and later x86 processors.
if setup at the very start of the code it enables 32-bit registers