/*
 * GccApplication5.c
 *
 * Created: 4/14/2025 5:29:37 AM
 * Author : roman
 */ 

#include <avr/io.h>

int main(void)
{
	DDRD = 0xFF;
	DDRB = 0x00;
	
	PORTD = 0b00000001;
	PORTB = 0b00000001;
	
	unsigned char butcount = 0;
    /* Replace with your application code */
    while (1) 
    {
		if (!(PINB&0b00000001)) {
			if (butcount < 5) {
				butcount++;
			} else {
				PORTD = 0b00000001;
			}
		} else {
			if (butcount > 0) {
				butcount--;
			} else {
				PORTD = 0b00000000;
			}
		}
    }
}

