/*
 * prac3.c
 *
 * Created: 4/14/2025 9:41:31 AM
 * Author : roman
 */ 
#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define NUMBER PORTD
#define PLACE PORTB

unsigned int place1 = 0, place2 = 0, place3 = 0, place4 = 0;
unsigned char bc547 = 1;
unsigned int z = 28;
unsigned int numbers[10] = {
	0x3f ,0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f
};

ISR(TIMER0_OVF_vect) {
	PLACE = 0;
	if (bc547 == 1) {
		PLACE = 0b00000001;
		NUMBER = numbers[place1];
	}
	if (bc547 == 2) {
		PLACE = 0b00000010;
		NUMBER = numbers[place2];
	}
	if (bc547 == 3) {
		PLACE = 0b00000100;
		NUMBER = numbers[place3];
	}
	if (bc547 == 4) {
		PLACE = 0b00001000;
		NUMBER = numbers[place4];
	}

	bc547++;
	if (bc547 > 4) bc547 = 1;
}

void number_breakdown(unsigned int number_placement) {
	place1 = number_placement/1000;
	place2 = number_placement%1000/100;
	place3 = number_placement%100/10;
	place4 = number_placement%10;
}

int main(void)
{
	DDRB = 0b00001111;
	DDRD = 0b11111111;
	PLACE = 0b00000001;
	NUMBER = 0x3f;

	TCCR0 |= (1<<1);
	TCCR0 &= ~((1<<0) | (1<<2));
	TCNT0 = 0;
	TIMSK |= (1<<0);
	sei();

	DDRC &= ~((1<<4) | (1<<5));
	PORTC |= (1<<4) | (1<<5);
    while (1) {
		number_breakdown(z);
    }
}

