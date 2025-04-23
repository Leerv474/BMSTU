/*
 * GccApplication5.c
 *
 * Created: 4/14/2025 5:29:37 AM
 * Author : roman
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int i = 0;
	DDRD = 0xFF;
	DDRB = 0x00;
	
	PORTD = 0b00000000;
	PORTB = 0b00000001;
	_delay_ms(300);
	
	uint8_t values[] = {
		0b00000110,
		0b01011011,
		0b01001111,
		0b01100110,
		0b01101101,
		0b01111101,
		0b00000111,
		0b01111111,
		0b01101111,
		0b00111111 
	};
	
    /* Replace with your application code */
    while (1) 
    {
		PORTD = ~(values[i]);
		_delay_ms(100);
		i++;
		if (i > sizeof(values)/sizeof(uint8_t) - 1) {
			i = 0;
		}
    }
}

