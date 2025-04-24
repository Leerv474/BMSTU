/*
 * lcd.h
 *
 * Created: 4/23/2025 6:27:44 AM
 *  Author: roman
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "main.h"

#define e1 PORTD |= 0b00001000
#define e0 PORTD &= 0b11110111
#define rs1 PORTD |= 0b0000100
#define  rs0 PORTD &= 0b1111011

void sendcharlcd(unsigned char c);
void setpos(unsigned char x, unsigned y);
void LCD_ini(void);
void clearlcd(void);
void str_lcd (char str1[]);


#endif /* LCD_H_ */