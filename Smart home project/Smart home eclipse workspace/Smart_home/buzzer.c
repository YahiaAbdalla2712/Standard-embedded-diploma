/*
 * buzzer.c
 *
 *  Created on: Oct 8, 2024
 *      Author: YAHIA
 */

#include "buzzer.h"
#include "common_macros.h"
#include "std_types.h"
#include "gpio.h"

uint8 port_id,pin_id;

void Buzzer_init(uint8 PORT_ID,uint8 PIN_ID){
	port_id = PORT_ID;
	pin_id = PIN_ID;

	/*SETUP THE PIN DIRECTION OF THE BUZZER TO BE OUPUT PIN*/
	GPIO_setupPinDirection(port_id,pin_id,PIN_OUTPUT);
}


void Buzzer_on(void){
	/*TURN THE BUZZER ON*/
	GPIO_writePin(port_id,pin_id,1);
}

void Buzzer_off(void){
	/*TURN THE BUZZER OFF*/
	GPIO_writePin(port_id,pin_id,0);
}
