/*
 * GccApplication5.c
 *
 * Created: 4/14/2025 5:29:37 AM
 * Author : roman
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

void segchar(unsigned char seg) {
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

	PORTD = ~(values[seg]);
}

int main(void)
{
	DDRD = 0xFF;
	DDRB = 0x00;
	
	PORTD = 0b00000000;
	PORTB = 0b00000001;
	_delay_ms(300);
	
	
	int i;
	unsigned butcount = 0, butstate = 0;
    /* Replace with your application code */
    while (1) 
    {
		for (i = 0; i < 10; i++) {
			while (butstate == 0) {
				if (!(PINB&0b00000001)) {
					if (butcount < 5) {
						butcount++;
					} else {
						i = 0;
						butstate = 1;
					}
				} else {
					if (butcount > 0) {
						butcount--;
					} else {
						butstate = 1;
					}
				}
			} 
		
			segchar(i);
			_delay_ms(100);
			butstate = 0;
		}
    }
}

