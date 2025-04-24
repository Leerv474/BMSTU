/*
 * main.h
 *
 * Created: 4/24/2025 3:55:02 AM
 *  Author: roman
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"
#include "adc.h"

unsigned int adc_value, adc_counter, adc_temp;



#endif /* MAIN_H_ */