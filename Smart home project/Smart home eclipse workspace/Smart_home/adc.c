/*
 * adc.c
 *
 *  Created on: Oct 7, 2024
 *      Author: YAHIA
 */

#include "adc.h"
#include "common_macros.h"
#include "std_types.h"
#include "avr/io.h"


void ADC_init(void){
	/*Setup ADMUX register voltage reference to internal reference = 2.56V*/
	ADMUX = (1<<REFS1)|(1<<REFS0);

	/*To enable ADC
	 *choose the prescaler of 128*/
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<ADPS0);
}


uint16 ADC_readChannel(uint8 num){
	/*insert the number of channel in ADMUX register to choose the channel number*/
	ADMUX = (ADMUX&~0x0F) | (num&0x0F);

	/*to start conversion*/
	ADCSRA |= (1<<ADSC);

	/*To wait for the conversion to end*/
	while(BIT_IS_CLEAR(ADCSRA,ADIF));

	/*clear ADIF bit by setting this bit to 1*/
	SET_BIT(ADCSRA,ADIF);

	/*return digital data*/
	return ADC;
}
