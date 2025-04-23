/*
 * pwm.c
 *
 * Created: 4/21/2025 7:42:13 PM
 *  Author: roman
 */ 

#include "pwm.h"

void init_pwm_timer(void) {
	ASSR = 0x00;
	TCCR2 = 0b01101110;
	TCNT2 = 0x00;
	OCR2 = 0x00;
	TIMSK |= 0x00;
}