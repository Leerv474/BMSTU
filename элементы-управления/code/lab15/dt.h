/*
 * dt.h
 *
 * Created: 4/23/2025 4:15:02 AM
 *  Author: roman
 */ 


#ifndef DT_H_
#define DT_H_

#include "main.h"

#define NOID 0xCC
#define T_CONVERT 0x44
#define READ_DATA 0xBE

#define PORTTEMP PORTD
#define DDRTEMP DDRD
#define PINTEMP PIND
#define BITTEMP 1


int dt_check(void);
char converttemp (unsigned int tt);



#endif /* DT_H_ */