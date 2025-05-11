/*
 * LDR_sensor.c
 *
 *  Created on: Oct 7, 2024
 *      Author: YAHIA
 */


#include "LDR_sensor.h"
#include "lm35_sensor.h"
#include "adc.h"





uint16 LDR_getLightIntensity(void){
	float light_intensity = 0;
	uint16 adc_value = 0;
	float temp_value = 0;


	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);

	/* Calculate the intensity from the ADC value*/
	temp_value = (float)(adc_value * ADC_REF_VOLT_VALUE) / ADC_MAXIMUM_VALUE;


	light_intensity = (temp_value / LDR_SENSOR_MAX_VOLT_VALUE) * LDR_SENSOR_MAX_LIGHT_INTENSITY;


	return (uint16)light_intensity;
}
