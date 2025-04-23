/*
 * prac1.c
 *
 * Created: 4/14/2025 8:21:34 AM
 * Author : roman
 */ 
#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD = 0b11111111;
    /* Replace with your application code */
    while (1) 
    {
		PORTD = 0b00111111;
		_delay_ms(300);
		PORTD = 0b00000110;
		_delay_ms(300);	
		PORTD = 0b01011011;
		_delay_ms(300);
		PORTD = 0b01001111;
		_delay_ms(300);
		PORTD = 0b01100110;
		_delay_ms(300);
		PORTD = 0b01101101;
		_delay_ms(300);
		PORTD = 0b01111101;
		_delay_ms(300);
		PORTD = 0b00000111;
		_delay_ms(300);
		PORTD = 0b01111111;
		_delay_ms(300);
		PORTD = 0b01101111;
		_delay_ms(300);
    }
}

