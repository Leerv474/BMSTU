/*
 * prac2.c
 *
 * Created: 4/14/2025 8:57:57 AM
 * Author : roman
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BLINK 300
#define VD PORTD

#define Z 300
#define K PORTB

void twoLights(void) {
	/* Replace with your application code */\
	DDRD = 0b00000011;
	while (1)
	{
		VD = 0b00000001;
		_delay_ms(BLINK);
		VD = 0b00000000;
		_delay_ms(BLINK);
		VD = 0b00000010;
		_delay_ms(BLINK);
		VD = 0b00000000;
		_delay_ms(BLINK);
	}
}

void garland(void) {
	DDRB = 0x00;
	DDRD = 0xFF;
	VD = 0x00;
	K = 0xFF;
	
	while (1) {
		if (PINB == 0b11111110) {
			VD = 0xFF;
			_delay_ms(Z);
			VD = 0x00;
			_delay_ms(Z);
		} else {
			VD = 0x00;
		}
		if (PINB == 0b11111101) {
			VD = 0b00000001;
			_delay_ms(Z);
			VD = 0b00000011;
			_delay_ms(Z);
			VD = 0b00000111;
			_delay_ms(Z);
			VD = 0b00001111;
			_delay_ms(Z);
			VD = 0b00011111;
			_delay_ms(Z);
			VD = 0b00111111;
			_delay_ms(Z);
			VD = 0b01111111;
			_delay_ms(Z);
			VD = 0b11111111;
			_delay_ms(Z);
			VD = 0b00000000;
			_delay_ms(Z);
		} else {
			VD = 0x00;
		}
	}
}

int main(void)
{
    garland();
}

