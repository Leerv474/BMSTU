/*
 * IncFile1.h
 *
 * Created: 4/21/2025 3:17:58 PM
 *  Author: roman
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "i2c.h"
#include "rtc.h"

#define e1 PORTD |= 0b00001000
#define e0 PORTD &= 0b11110111
#define rs1 PORTD |= 0b00000100
#define rs0 PORTD &= 0b11111011

void port_ini(void);

#endif /* MAIN_H_ */