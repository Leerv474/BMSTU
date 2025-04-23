/*
 * GccApplication9.c
 *
 * Created: 4/20/2025 6:00:31 AM
 * Author : roman
 */ 
#define F_CPU 8000000UL
#define D0_OFF PORTB |= (1<<PB0);
#define D0_ON PORTB &= ~(1<<PB0);
#define D1_OFF PORTB |= (1<<PB1);
#define D1_ON PORTB &= ~(1<<PB1);

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void timer_ini(void) {
	TCCR1B |= (1<<WGM12);
 	TIMSK |= (1<<OCIE1A);
 	OCR1AH = 0b00001111;
 	OCR1AL = 0b01000010;
	TCCR1B |= (1<<CS11);
}

unsigned char counter = 0;
int number = 10;
int digit1 = 0;
int digit0 = 0;


void segchar(unsigned char seg) {
	uint8_t values[] = {
		0b00111111,
		0b00000110,
		0b01011011,
		0b01001111,
		0b01100110,
		0b01101101,
		0b01101101,
		0b00000111,
		0b01111111,
		0b01101111,
	};

	PORTD = ~(values[seg]);
}
ISR(TIMER1_COMPA_vect) {
	if (!(PINB&0b00100000)) {
		number = 0;
	}
	digit0 = number / 10;
	digit1 = number % 10;
	if (counter == 0) {
		D0_ON;
		D1_OFF;
		segchar(digit0);
		counter = 1;
	} else if (counter == 1) {
		D1_ON;
		D0_OFF;
		segchar(digit1);
		counter = 0;
	}
}

int main(void)
{
	DDRD = 0xFF;
	DDRB |= (1<<PB0) | (1<<PB1) | ~(1<<PB5);
	timer_ini();
	sei();
	number = 97;
    while (1) {
		for (number = 0; number < 100; number++) {
			_delay_ms(100);
		}
    }
}

