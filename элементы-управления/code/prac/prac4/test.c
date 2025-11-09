#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LATCH PB2
#define DATA  PB3
#define CLOCK PB4

void shiftOut(uint8_t data) {
	for (int i = 7; i >= 0; i--) {
		if (data & (1 << i))
			PORTB |= (1 << DATA);
		else
			PORTB &= ~(1 << DATA);

		PORTB |= (1 << CLOCK);
		_delay_us(1000);
		PORTB &= ~(1 << CLOCK);
	}
}

int main(void) {
	DDRB |= (1 << LATCH) | (1 << DATA) | (1 << CLOCK);

	while (1) {
		// Turn all outputs ON
		PORTB &= ~(1 << LATCH);
		shiftOut(0xFF);      // all bits high
		PORTB |= (1 << LATCH);

		_delay_ms(1000);

		// Turn all outputs OFF
		PORTB &= ~(1 << LATCH);
		shiftOut(0x00);      // all bits low
		PORTB |= (1 << LATCH);

		_delay_ms(1000);
	}
}
