/*
 * GccApplication4.c
 *
 * Created: 4/14/2025 5:16:18 AM
 * Author : roman
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	unsigned char i;
	DDRD = 0xFF;
	PORTD = 0b00000001;
    /* Replace with your application code */
    while (1) 
    {
		for (i = 0; i < 7; i++) {
			PORTD = (1<<i);
			_delay_ms(100);
		}
    }
}

