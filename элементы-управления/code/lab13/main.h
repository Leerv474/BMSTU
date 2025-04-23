/*
 * main.h
 *
 * Created: 4/21/2025 7:41:44 PM
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
#include "pwm.h"

void port_ini(void);



#endif /* MAIN_H_ */