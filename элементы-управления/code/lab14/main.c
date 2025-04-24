/*
 * GccApplication12.c
 *
 * Created: 4/21/2025 7:52:57 PM
 * Author : roman
 */ 

#include "main.h"

void port_ini(void) {
	PORTD = 0x00;
	DDRD = 0xFF;
}

int main(void)
{
	uint8_t sec, min, hour, day, month, year, date;
	port_ini();
	LCD_ini();
	clear_lcd();
	
	I2C_StartCondition();
	I2C_SendByte(0b11010000);
	I2C_SendByte(0);//????????? ?? 0x00
	I2C_SendByte(RTC_ConvertFromBinDec(0)); //???????
	I2C_SendByte(RTC_ConvertFromBinDec(31)); //??????
	I2C_SendByte(RTC_ConvertFromBinDec(20)); //????
	I2C_SendByte(RTC_ConvertFromBinDec(5)); //???? ??????
	I2C_SendByte(RTC_ConvertFromBinDec(29)); //????
	I2C_SendByte(RTC_ConvertFromBinDec(1)); //?????
	I2C_SendByte(RTC_ConvertFromBinDec(16)); //???
	I2C_StopCondition();
	
    while (1) 
    {
		date = RTC_ConvertFromBinDec(date);
		setpos(0, 0);
		send_char(date/10 + 0x30);
		send_char(date%10 + 0x30);
		send_char('.');
		send_char(month/10 + 0x30);
		send_char(month%10 + 0x30);
		str_lcd(".20");
		send_char(year/10 + 0x30);
		send_char(year%10 + 0x30);
		send_char(' ');
		send_char('-');
		send_char(day/10 + 0x30);
		send_char('-');
		setpos(0, 1);
		send_char(hour/10 + 0x30);
		send_char(hour%10 + 0x30);
		send_char(':');
		send_char(min/10 + 0x30);
		send_char(min%10 + 0x30);
		send_char(':');
		send_char(sec/10 + 0x30);
		send_char(sec%10 + 0x30);
		_delay_ms(100);
		clear_lcd();
		
    }
}

