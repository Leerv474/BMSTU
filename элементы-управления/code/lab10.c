/*
 * GccApplication5.c
 *
 * Created: 4/14/2025 5:29:37 AM
 * Author : roman
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char i;
void timer_ini(void) {
	TCCR1B |= (1<<WGM12);
	TIMSK |= (1<<OCIE1A);
	OCR1AH = 0b0000000;
	OCR1AL = 0b00000000;
	TCCR1B |= (1 << CS12);
}

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

ISR(TIMER1_COMPA_vect) {
	if (i > 9) i = 0;
	segchar(i);
	i++;
}

int main(void)
{
	timer_ini();
	
	DDRD = 0xFF;
	DDRB = 0x00;
	PORTD = 0b11111111;
	PORTB = 0b00000001;	
	i = 0;
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

