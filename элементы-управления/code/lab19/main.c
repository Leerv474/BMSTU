/*
 * GccApplication17.c
 *
 * Created: 4/24/2025 3:49:25 AM
 * Author : roman
 */ 

#include "main.h"

void port_ini(void) {
	PORTD = 0x00;
	DDRD = 0xFF;
}

int main(void)
{
	port_ini();
	LCD_ini();
	ADC_Init();
	sei();
	clearlcd();
	setpos(0,0);
	str_lcd("Button Test");
    while (1) 
    {
		setpos(0, 1);
		if      (adc_value < 25)  str_lcd("RIGHT KEY   ");
		else if (adc_value < 65)  str_lcd("UP KEY      ");
		else if (adc_value < 115) str_lcd("DOWN KEY    ");
		else if (adc_value < 180) str_lcd("LEFT KEY    ");
		else if (adc_value < 230) str_lcd("SELECT KEY  ");
		_delay_ms(200);
    }
}

