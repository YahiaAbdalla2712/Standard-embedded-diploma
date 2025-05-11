/*
 * leds.h
 *
 *  Created on: Oct 7, 2024
 *      Author: YAHIA
 */

#ifndef LEDS_H_
#define LEDS_H_
#include "std_types.h"

#define LEDS_PORT_ID PORTC_ID
#define RED_PIN_NUM	PIN0_ID
#define GREEN_PIN_NUM PIN1_ID
#define BLUE_PIN_NUM PIN2_ID
#define CONNECTION_TYPE POSITIVE


/*Enum for every led color*/
typedef enum {
	LED_RED,LED_GREEN,LED_BLUE
}LED_ID;

/*ENUM to determine the type of connection of the leds*/
typedef enum{
	POSITIVE,NEGATIVE
}connection_type;



/*A function to setup the leds as outputs and initialize their values to turn all of them off
 * also to let the user enter the type of the connection of the leds
 * user must use this function if he want to use any other function in this file*/
void LEDS_init(void);

/*A function to turn a specific led with its id on*/
void LED_on(LED_ID id);

/*A function to turn a specific led with its id off*/
void LED_off(LED_ID id);


#endif /* LEDS_H_ */
