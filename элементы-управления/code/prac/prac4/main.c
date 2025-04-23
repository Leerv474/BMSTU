/*
 * prac4.c
 *
 * Created: 4/15/2025 7:26:22 PM
 * Author : roman
 */ 
#include <avr/io.h>
#include "./main.h"

int main(void)
{
	unsigned int i = 0;
	DDRB |= ((1<<PORTB2) | (1<<PORTB3) | (1<<PORTB5));
	PORTB &= ~((1<<PORTB2) | (1<<PORTB3) | (1<<PORTB5));
	
	SPCR = ((1<<SPE) | (1<<MSTR));
	SPDR = 0x00;

    while (!(SPSR & (1<<SPIF))); 
	PORTB |= (1<<PORTB2);
	_delay_us(10);
	PORTB &= ~(1<<PORTB2);
	_delay_ms(200);
	SPDR = 0xFF;
	while (!(SPSR & (1<<SPIF))); 
	PORTB |= (1<<PORTB2);
	_delay_us(10);
	PORTB &= ~(1<<PORTB2);
	_delay_ms(200);
	
	while (1) {
		for (i = 0; i < 256; i++) {
			SPDR = i;
			while (!(SPSR&(1<<SPIF)));
			PORTB |= (1<<PORTB2);
			PORTB &= ~(1<<PORTB2);
			_delay_ms(50);
		}
		i = 0;
	}
}

