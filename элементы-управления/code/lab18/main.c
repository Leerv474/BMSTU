/*
 * GccApplication16.c
 *
 * Created: 4/23/2025 8:40:51 AM
 * Author : roman
 */ 

#include "main.h"

int main(void)
{
	unsigned int i;
	I2C_Init();//?????????????? TWI
	LCD_ini();//?????????????? ?????????? ???????
	clearlcd();//??????? ?????????? ???????
	setpos(0,0);
	str_lcd("TEST TFT ILI9341");
	TFT9341_ini();
	TFT9341_FillScreen(RED);
	_delay_ms(500);
	TFT9341_FillScreen(BLUE);
	_delay_ms(500);
	TFT9341_FillScreen(GREEN);
	_delay_ms(500);
	TFT9341_FillScreen(CYAN);
	_delay_ms(500);
	TFT9341_FillScreen(MAGENTA);
	_delay_ms(500);
	TFT9341_FillScreen(YELLOW);
	_delay_ms(500);
	TFT9341_FillScreen(WHITE);
	_delay_ms(500);
	TFT9341_FillScreen(BLACK);
	_delay_ms(500);
	for(i=0;i<8;i++)
	{
		TFT9341_FillRectangle(TFT9341_RandColor(),0,0,119,159);
		_delay_ms(100);
		TFT9341_FillRectangle(TFT9341_RandColor(),120,0,239,159);
		_delay_ms(100);
		TFT9341_FillRectangle(TFT9341_RandColor(),0,160,119,319);
		_delay_ms(100);
		TFT9341_FillRectangle(TFT9341_RandColor(),120,160,239,319);
		_delay_ms(100);
	}
	TFT9341_FillScreen(BLACK);
	for(i=0;i<15000;i++)
	{
		TFT9341_DrawPixel(rand()%240,rand()%320,TFT9341_RandColor());
	}
	TFT9341_FillScreen(BLACK);
	for(i=0;i<240;i++)
	{
		TFT9341_DrawLine(TFT9341_RandColor(),i,0,i,319);
	}
	_delay_ms(500);
	TFT9341_FillScreen(BLACK);
	for(i=0;i<1000;i++)
	{
		TFT9341_DrawLine(TFT9341_RandColor(),rand()%240,rand()%320,rand()%240,rand()%320);
	}
	_delay_ms(500);
	TFT9341_FillScreen(BLACK);
	for(i=0;i<120;i++)
	{
		TFT9341_DrawRect(TFT9341_RandColor(),i,i,239-i,319-i);
	}
	_delay_ms(500);
	TFT9341_FillScreen(BLACK);
	for(i=0;i<2000;i++)
	{
		TFT9341_DrawCircle(rand()%200+20, rand()%280+20, 20, TFT9341_RandColor());
	}
	_delay_ms(500);
	TFT9341_FillScreen(BLACK);
	TFT9341_Draw_Char(10,10,RED,GREEN,0x21,2);
	TFT9341_Draw_Char(26,10,RED,GREEN,0x22,2);
	TFT9341_Draw_Char(42,10,RED,GREEN,0x23,2);
	TFT9341_Draw_Char(58,10,RED,GREEN,0x24,2);
	TFT9341_Draw_Char(74,10,RED,GREEN,0x25,2);
	TFT9341_Draw_Char(10,26,RED,GREEN,0x21,2);
	TFT9341_Draw_Char(26,26,RED,GREEN,0x22,2);
	TFT9341_Draw_Char(42,26,RED,GREEN,0x23,2);
	TFT9341_Draw_Char(58,26,RED,GREEN,0x24,2);
	TFT9341_Draw_Char(74,26,RED,GREEN,0x25,2);
	_delay_ms(1000);
	TFT9341_FillScreen(BLACK);
	TFT9341_String(1,1,RED,GREEN,"12345ABCDE",1);
	TFT9341_String(1,9,RED,GREEN,"EDCAB54321",1);
	TFT9341_String(10,17,RED,GREEN,"ABCDEabcde",1);
	_delay_ms(1000);
	TFT9341_FillScreen(BLACK);

	while (1)
	{
		TFT9341_Draw_Char((rand()%15)*16,(rand()%20)*16,GREEN,BLACK,rand()%2+0x21,2);

	}
}

