/*
 * i2c.h
 *
 * Created: 4/21/2025 10:31:26 AM
 *  Author: roman
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

void I2C_ini(void);
void I2C_StartCondition(void);
void I2C_StopCondition(void);
void I2C_SendByte(uint8_t data);
uint8_t I2C_ReadByteACK(void);

uint8_t I2C_ReadByteNACK(void);

uint8_t RTC_ConvertFromBinDec(uint8_t value);

uint8_t RTC_ConvertFromBinDec(uint8_t value);
void RTC_GetTime(uint8_t *sec, uint8_t* min, uint8_t* hour, uint8_t* day, uint8_t* month, uint8_t* year, uint8_t* date);


#endif /* I2C_H_ */