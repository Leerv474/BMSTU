#include "main.h"
#include "lcd.h"

void port_ini(void) {
	PORTD = 0x00;
	DDRD = 0xFF;
}

int main(void)
{
	port_ini();
	LCD_ini();
	setpos(0,0);
	
	str_led("Hello world!");
	setpos(2, 1);
	str_led("String 2");
    while (1) 
    {
    }
}

