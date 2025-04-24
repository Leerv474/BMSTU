/*
 * ili8341.h
 *
 * Created: 4/23/2025 8:54:45 AM
 *  Author: roman
 */ 


#ifndef ILI8341_H_
#define ILI8341_H_



#include <stdlib.h>
#include "main.h"
#include "twi.h"
#include "lcdtwi.h"

#define swap(a,b) {int16_t t=a;a=b;b=t;}
#define  DATA_DDR DDRD
#define  DATA_PORT PORTD
#define  DATA_PIN PIND
#define  COMMAND_DDR DDRB
#define  COMMAND_PORT PORTB
#define  LCD_CS 2//Chip Select
#define  LCD_CD 1//Command/Data
#define  LCD_WR 3//LCD Write
#define  LCD_RD 4//LCD Read
#define  LCD_RESET 0//LCD Reset
#define  RESET_IDLE COMMAND_PORT|=(1<<LCD_RESET)
#define  CS_IDLE COMMAND_PORT|=(1<<LCD_CS)
#define  WR_IDLE COMMAND_PORT|=(1<<LCD_WR)
#define  RD_IDLE COMMAND_PORT|=(1<<LCD_RD)
#define  RESET_ACTIVE COMMAND_PORT&=~(1<<LCD_RESET)
#define  CS_ACTIVE COMMAND_PORT&=~(1<<LCD_CS)
#define  WR_ACTIVE COMMAND_PORT&=~(1<<LCD_WR)
#define  RD_ACTIVE COMMAND_PORT&=~(1<<LCD_RD)
#define  CD_COMMAND COMMAND_PORT&=~(1<<LCD_CD)
#define  CD_DATA COMMAND_PORT|=(1<<LCD_CD)

#define  BLACK 0x0000
#define  BLUE 0x001F
#define  RED 0x0F800
#define  GREEN 0x07E0
#define  CYAN 0x07FF
#define  MAGENTA 0xF81F
#define  YELLOW 0xFFE0
#define  WHITE 0xFFFF

#define   setReadDir() DATA_DDR=0x00
#define   setWriteDir() DATA_DDR=0xFF

#define  WR_STROBE {WR_ACTIVE;WR_IDLE;}

void TFT9341_ini(void);
void TFT9341_FillScreen(unsigned int color);
void TFT9341_FillRectangle(unsigned int color,unsigned int x1, unsigned int y1,
unsigned int x2, unsigned int y2);
unsigned int TFT9341_RandColor(void);
void TFT9341_DrawPixel(int x, int y, unsigned int color);
void TFT9341_DrawLine(unsigned int color,unsigned int x1, unsigned int y1,
unsigned int x2, unsigned int y2);
void TFT9341_DrawRect(unsigned int color,unsigned int x1, unsigned int y1,
unsigned int x2, unsigned int y2);
void TFT9341_DrawCircle(unsigned int x0, unsigned int y0, int r, unsigned int color);
void TFT9341_Draw_Char(int x, int y, unsigned int color, unsigned int phone,
unsigned char charcode, unsigned char size);
void TFT9341_String(unsigned int x, unsigned int y, unsigned int color, unsigned int phone,
char *str, unsigned char size);


#endif /* ILI8341_H_ */