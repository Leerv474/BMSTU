/*
 * GccApplication2.c
 *
 * Created: 4/14/2025 12:54:45 PM
 * Author : roman
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0b00000001;
    /* Replace with your application code */
    while (1) 
    {
    }
}

