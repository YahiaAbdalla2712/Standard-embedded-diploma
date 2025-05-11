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



void Buzzer_init(void){
	/*SETUP THE PIN DIRECTION OF THE BUZZER TO BE OUPUT PIN*/
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_NUM,PIN_OUTPUT);
}


void Buzzer_on(void){
	/*TURN THE BUZZER ON*/
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_NUM,LOGIC_HIGH);

}

void Buzzer_off(void){
	/*TURN THE BUZZER OFF*/
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_NUM,LOGIC_LOW);
}
