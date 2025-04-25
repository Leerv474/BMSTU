#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define D0_OFF PORTC |= (1<<PC0);
#define D0_ON PORTC &= ~(1<<PC0);
#define D1_OFF PORTC |= (1<<PC1);
#define D1_ON PORTC &= ~(1<<PC1);

unsigned char i = 97;

ISR(INT4_vect) {
	if (i < 99) {
		i++;
	}
}

ISR(INT5_vect) {
	if (i > 0) {
		i--;
	}
}

void setupInputPins(void) {
	DDRE &= ~((1 << DDE4) | (1 << DDE5));
	DDRB = 0xFF;
	DDRC |= (1<<PC0) | (1<<PC1);
}

void setupInterrupts(void) {
	EICRA |= (1<< ISC41) | (1<<ISC51);
	EICRA &= ~((1 << ISC40) | (1 << ISC50));
	
	EIMSK |= (1 << INT4) | (1 << INT5);
	
	
	TCCR1B |= (1<<WGM12);
	TIMSK |= (1<<OCIE1A);
	OCR1AH = 0b00001111;
	OCR1AL = 0b01000010;
	TCCR1B |= (1<<CS11);
	sei();
}

void pollButtons(void) {
	if (PINE & (1 << PINE4)) {
		_delay_ms(50);
		if (!(PINE & (1 << PINE4)) && (i < 99)) {
			i++;
		}
	}
	if (PINE & (1 << PINE5)) {
		_delay_ms(50);
		if (!(PINE & (1 << PINE5)) && (i > 0)) {
			i--;
		}
	}
}




unsigned char counter = 0;
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

	PORTB = ~(values[seg]);
}
ISR(TIMER1_COMPA_vect) {
	digit0 = i / 10;
	digit1 = i % 10;
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
	setupInputPins();
	setupInterrupts();
	
	while (1) {
		//pollButtons();
	}
}

