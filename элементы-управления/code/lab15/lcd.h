/*
 * lcd.h
 *
 * Created: 4/21/2025 3:21:46 PM
 *  Author: roman
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "main.h"

#define e1 PORTD |= 0b00001000
#define e0 PORTD &= 0b11110111
#define rs1 PORTD |= 0b00000100
#define rs0 PORTD &= 0b11111011
#include "lcd.h"


void sendcharlcd(unsigned char c);
void setpos(unsigned char x, unsigned y);
void LCD_ini(void);
void clearlcd(void);
void str_lcd (char str1[]);

#endif /* LCD_H_ */