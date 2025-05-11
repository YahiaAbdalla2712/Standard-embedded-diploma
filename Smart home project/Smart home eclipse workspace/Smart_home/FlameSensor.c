/*
 * FlameSensor.c
 *
 *  Created on: Oct 7, 2024
 *      Author: YAHIA
 */


#include "FlameSensor.h"
#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"

uint8 port_id,pin_id;


void FlameSensor_init(uint8 PORT_ID, uint8 PIN_ID){
	/*initialize the pin direction of the flame sensor*/
	port_id = PORT_ID;
	pin_id = PIN_ID;
	GPIO_setupPinDirection(PORT_ID,PIN_ID,PIN_INPUT);
}




uint8 FlameSensor_getValue(void){
	uint8 reading;
	reading = GPIO_readPin(port_id,pin_id);
	return reading;
}
