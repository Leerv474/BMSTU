/*
 * GccApplication1.c
 *
 * Created: 4/13/2025 9:46:28 PM
 * Author : roman
 */ 

#include <avr/io.h>

#define PORT7 7
#define PORT6 6
#define PORT5 5
#define PORT4 4
#define PORT3 3
#define PORT2 2
#define PORT1 1
#define PORT0 0

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0b00000001;
    /* Replace with your application code */
    while (1) 
    {
    }
}

