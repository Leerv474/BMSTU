/*
 * GccApplication3.c
 *
 * Created: 4/14/2025 4:11:38 AM
 * Author : roman
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD = 0x01;
	PORTD = 0b00000000;
    /* Replace with your application code */
    while (1) 
    {
		PORTD ^= (1<<(PD0));
		_delay_ms(500);
    }
}

