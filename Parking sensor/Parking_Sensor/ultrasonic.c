/*
 * ultrasonic.c
 *
 *  Created on: Oct 15, 2024
 *      Author: YAHIA
 */


#include "ultrasonic.h"
#include "common_macros.h"
#include "std_types.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>


uint8 num_of_edges = 0;

uint16 highest_time = 0;

void Ultrasonic_init(void){
	/*initialize the input capture unit*/
	ICU_init();

	/*call the call back function of the ICU*/
	ICU_setCallBack(Ultrasonic_edgeProcessing);

	/*Set the direction for the trigger pin as output through
	the GPIO driver*/
	GPIO_setupPinDirection(TRIGGER_PORT,TRIGGER_PIN,1);
}


void Ultrasonic_Trigger(void){
	/*send a pulse to the trigger pin
	 * the duration of the pulse is 10 us*/
	GPIO_writePin(TRIGGER_PORT,TRIGGER_PIN,1);

	_delay_us(10);

	GPIO_writePin(TRIGGER_PORT,TRIGGER_PIN,0);
}

uint16 Ultrasonic_readDistance(void)
{
	/*declare a variable of the measured distance*/
	uint16 distance;

	/*call the trigger function to generate a pulse on the trigger*/
	Ultrasonic_Trigger();

	/*polling on pin6 portD waiting the input capture unit*/
	while(GPIO_readPin(PORTD_ID,PIN6_ID));

	/*assign the value of the variable distance*/
	distance = ((highest_time) / 117.6);


	return distance;

}

void Ultrasonic_edgeProcessing(void){
	num_of_edges++;
	if(num_of_edges == 1){
		ICU_clearTimer();

		ICU_setEdgeDetectionType(FALLING);
	}
	else if(num_of_edges == 2){
		highest_time = ICU_getInput();

		ICU_setEdgeDetectionType(RAISING);

		num_of_edges = 0;
	}
}
