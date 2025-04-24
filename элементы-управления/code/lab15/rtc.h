/*
 * rtc.h
 *
 * Created: 4/22/2025 8:19:49 AM
 *  Author: roman
 */ 


#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>

unsigned char RTC_ConvertFromDec(unsigned char c);
unsigned char RTC_ConvertFromBinDec(unsigned char c);



#endif /* RTC_H_ */