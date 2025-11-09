#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


#define DS1    PC0
#define SHCP1  PC1
#define STCP1  PC2

#define DS2    PC3
#define SHCP2  PC4
#define STCP2  PC5

#define DS3    PD0
#define SHCP3  PD1
#define STCP3  PD2

#define DS4    PD3
#define SHCP4  PD4
#define STCP4  PD5

void shiftOut(uint8_t data, uint8_t DS, uint8_t SHCP, uint8_t STCP, volatile uint8_t* DATA_PORT) {
	for (int i = 7; i >= 0; i--) {
		if (data & (1 << i))
		*DATA_PORT |= (1 << DS);
		else
		*DATA_PORT &= ~(1 << DS);

		*DATA_PORT |= (1 << SHCP);
		_delay_us(1);
		*DATA_PORT &= ~(1 << SHCP);
	}

	*DATA_PORT |= (1 << STCP);
	_delay_us(1);
	*DATA_PORT &= ~(1 << STCP);
}

void turnOffDiode(int diodeNumber, uint8_t DS, uint8_t SHCP, uint8_t STCP, volatile uint8_t* DATA_PORT, uint8_t* state) {
	*state &= ~(1 << diodeNumber); 
	shiftOut(*state, DS, SHCP, STCP, DATA_PORT);
}


void stepMotor(int step) {
	switch(step) {
		case 0: PORTB = 0b00000001; break;
		case 1: PORTB = 0b00000011; break;
		case 2: PORTB = 0b00000010; break;
		case 3: PORTB = 0b00000110; break;
		case 4: PORTB = 0b00000100; break;
		case 5: PORTB = 0b00001100; break;
		case 6: PORTB = 0b00001000; break;
		case 7: PORTB = 0b00001001; break;
	}
}

int main(void) {
	DDRC |= (1 << DS1) | (1 << SHCP1) | (1 << STCP1) | (1 << DS2) | (1 << SHCP2) | (1 << STCP2);
	DDRD |= (1 << DS3) | (1 << SHCP3) | (1 << STCP3) | (1 << DS4) | (1 << SHCP4) | (1 << STCP4);;
	DDRB = 0x0F;
	
	uint8_t diodeState1 = 0xFF;
	uint8_t diodeState2 = 0xFF;
	uint8_t diodeState3 = 0xFF;
	uint8_t diodeState4 = 0xFF;

	shiftOut(diodeState1, DS1, SHCP1, STCP1, &PORTC);
	shiftOut(diodeState2, DS2, SHCP2, STCP2, &PORTC);
	shiftOut(diodeState3, DS3, SHCP3, STCP3, &PORTD);
	shiftOut(diodeState4, DS4, SHCP4, STCP4, &PORTD);

	_delay_ms(1000);
    
	diodeState1 = 0x00;
	diodeState2 = 0x00;
	diodeState3 = 0x00;
	diodeState4 = 0x00;

	shiftOut(diodeState1, DS1, SHCP1, STCP1, &PORTC);
	shiftOut(diodeState2, DS2, SHCP2, STCP2, &PORTC);
	shiftOut(diodeState3, DS3, SHCP3, STCP3, &PORTD);
	shiftOut(diodeState4, DS4, SHCP4, STCP4, &PORTD);

	_delay_ms(1000);

	diodeState1 = 0xFF;
	diodeState2 = 0xFF;
	diodeState3 = 0xFF;
	diodeState4 = 0xFF;

	shiftOut(diodeState1, DS1, SHCP1, STCP1, &PORTC);
	shiftOut(diodeState2, DS2, SHCP2, STCP2, &PORTC);
	shiftOut(diodeState3, DS3, SHCP3, STCP3, &PORTD);
	shiftOut(diodeState4, DS4, SHCP4, STCP4, &PORTD);
	
	int step = 0;
	int totalSteps = 0;
	int diodesLit = 32;
	int moduleDioteCount = 0;
	
	while (1) {
		stepMotor(step);
		step = (step + 1) % 8;
		totalSteps ++;
		if (totalSteps % 400 == 0) {
			if (diodesLit > 24) {
				turnOffDiode(moduleDioteCount, DS1, SHCP1, STCP1, &PORTC, &diodeState1);
			} else if (diodesLit > 16) {
				if (diodesLit == 24)
					moduleDioteCount = 0;
				turnOffDiode(moduleDioteCount, DS2, SHCP2, STCP2, &PORTC, &diodeState2);
			} else if (diodesLit > 8) {
				if (diodesLit == 16)
					moduleDioteCount = 0;
					turnOffDiode(moduleDioteCount, DS3, SHCP3, STCP3, &PORTD, &diodeState3);
			} else {
				if (diodesLit == 8)
					moduleDioteCount = 0;
				turnOffDiode(moduleDioteCount, DS4, SHCP4, STCP4, &PORTD, &diodeState4);
			}
			moduleDioteCount++;
			diodesLit--;
		}
		_delay_ms(5);
		
		if (totalSteps == 12000) {
			diodeState1 = 0xFF;
			diodeState2 = 0xFF;
			diodeState3 = 0xFF;
			diodeState4 = 0xFF;

			shiftOut(diodeState1, DS1, SHCP1, STCP1, &PORTC);
			shiftOut(diodeState2, DS2, SHCP2, STCP2, &PORTC);
			shiftOut(diodeState3, DS3, SHCP3, STCP3, &PORTD);
			shiftOut(diodeState4, DS4, SHCP4, STCP4, &PORTD);
			
			step = 0;
			totalSteps = 0;
			diodesLit = 32;
			moduleDioteCount = 0;
			_delay_ms(5000);
		}
	}
}
