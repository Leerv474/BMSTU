#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

// Stepper motor on PB0..PB3
void stepMotor(uint8_t step) {
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
    DDRB = 0x0F;       // PB0..PB3 outputs
    uint8_t step = 0;

    while (1) {
        stepMotor(step);
        step = (step + 1) % 8;   // advance step
        _delay_ms(10);           // adjust for speed
    }
}

