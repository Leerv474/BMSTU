/*
 * lcd.h
 *
 * Created: 4/21/2025 3:21:46 PM
 *  Author: roman
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "main.h"

void send_half_byte(unsigned char c);
void send_byte(unsigned char c, unsigned char mode);
void LCD_ini(void);
void send_char(unsigned char c);
void setpos(unsigned char x, unsigned char y);
void str_lcd(char str1[]);
void clear_lcd(void);


#endif /* LCD_H_ */