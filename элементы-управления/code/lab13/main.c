/*
 * GccApplication11.c
 *
 * Created: 4/21/2025 7:39:27 PM
 * Author : roman
 */ 

#include "main.h"

void port_ini(void) {
	DDRB |= (1<<PB3);
}

int main(void)
{
	init_pwm_timer();
	OCR2 = 0;
	unsigned char pwm_state = 0;
	port_ini();
    while (1) 
    {
		if (pwm_state==0) {
			OCR2++;
			if (OCR2 > 254) {
				pwm_state = 1;
			}
		}
		if (pwm_state == 1) {
			OCR2--;
			if (OCR2<1) {
				pwm_state = 0;
			}
		}
		_delay_ms(3);
    }
}

