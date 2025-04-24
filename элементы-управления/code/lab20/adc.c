/*
 * adc.c
 *
 * Created: 4/24/2025 3:57:27 AM
 *  Author: roman
 */ 

#include "adc.h"

extern unsigned int adc_value, adc_counter, adc_temp;

char high_adc  = 0, low_adc = 0;

ISR(ADC_vect) {
	low_adc = ADCL;
	high_adc = ADCH;
	if (adc_counter < 20) {
		adc_temp += high_adc; 
		adc_counter++;
	} else {
		adc_value = adc_temp/20;
		adc_counter = 0;
		adc_temp = 0;
	}
}

void ADC_Init(void) {
	ADCSRA |= (1<<ADEN) |(1<<ADSC) | (1<<ADFR) | (1<<ADPS2) | (1<<ADPS1) |(1<<ADPS0) | (1<<ADIE);
	ADMUX |= (1<<ADLAR) |(0<<REFS1) |(1<<REFS0);
}