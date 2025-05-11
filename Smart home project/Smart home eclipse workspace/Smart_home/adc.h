/*
 * adc.h
 *
 *  Created on: Oct 7, 2024
 *      Author: YAHIA
 */

#ifndef ADC_H_
#define ADC_H_


#include "std_types.h"


#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56


/*function to initialize the ADC*/
void ADC_init(void);


/*function to start conversion on a specific channel*/
uint16 ADC_readChannel(uint8 num);


#endif /* ADC_H_ */
