/*
 * lcd.c
 *
 * Created: 4/21/2025 3:24:24 PM
 *  Author: roman
 */ 
#include "lcd.h"


void send_half_byte(unsigned char c) {
	c<<=4;
	PORTD &= 0b00001111;
	PORTD |= c;
	e1;
	_delay_us(1);
	e0;
	_delay_us(50);
}

void send_byte(unsigned char c, unsigned char mode) {
	if (mode == 0) rs0; else rs1;
	unsigned char hc = 0;
	hc=c>>4;
	send_half_byte(hc);
	send_half_byte(c & 0x0F);
}


void LCD_ini(void) {
	_delay_ms(15);
	
	rs0;
	send_half_byte(0x03);
	_delay_ms(5);
	send_half_byte(0x03);
	_delay_us(150);
	send_half_byte(0x03);
	send_half_byte(0x02);
	
	send_byte(0x28, 0);
	send_byte(0x0C,0 );
	send_byte(0x06, 0);
	send_byte(0x01, 0);
	_delay_ms(2);
	
}

void send_char(unsigned char c) {
	send_byte(c, 1);
}

void setpos(unsigned char x, unsigned char y) {
	char address;
	address = (0x40*y + x) | 0b10000000;
	send_byte(address, 0);
}

void str_led(char str1[]) {
	unsigned char n;
	for(n = 0; str1[n] != '\0'; n++) {
		send_char(str1[n]);
	}
}