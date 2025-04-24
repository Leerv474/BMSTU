/*
 * rtc.c
 *
 * Created: 4/22/2025 8:19:58 AM
 *  Author: roman
 */ 

#include "rtc.h"

unsigned char RTC_ConvertFromDec(unsigned char c) {
	unsigned char ch = ((c >> 4)*10 + (0b00001111 & c));
	return ch;
}

unsigned char RTC_ConvertFromBinDec(unsigned char c) {
	unsigned char ch = ((c / 10) << 4) | (c % 10);
	return ch;
}