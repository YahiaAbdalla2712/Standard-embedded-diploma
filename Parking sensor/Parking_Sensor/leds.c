/*
 * leds.c
 *
 *  Created on: Oct 7, 2024
 *      Author: YAHIA
 */


#include "leds.h"
#include "avr/io.h"
#include "common_macros.h"
#include "std_types.h"
#include "gpio.h"





/*A function to initialize the direction of the leds as outputs
 * initially turn off all leds if they are connected in positive logic*/
void LEDS_init(void){



	/*setup the direction of the leds as outputs*/
	GPIO_setupPinDirection(LEDS_PORT_ID,RED_PIN_NUM,PIN_OUTPUT);
	GPIO_setupPinDirection(LEDS_PORT_ID,GREEN_PIN_NUM,PIN_OUTPUT);
	GPIO_setupPinDirection(LEDS_PORT_ID,BLUE_PIN_NUM,PIN_OUTPUT);

#if(CONNECTION_TYPE == POSITIVE)
	/*initialize their values by zero to turn the leds off if they are connected in positive logic*/
	GPIO_writePin(LEDS_PORT_ID,RED_PIN_NUM,0);
	GPIO_writePin(LEDS_PORT_ID,GREEN_PIN_NUM,0);
	GPIO_writePin(LEDS_PORT_ID,BLUE_PIN_NUM,0);

#elif(CONNECTION_TYPE == NEGATIVE)
	/*initialize their values by ONE to turn the leds off if they are connected in negative logic*/
	GPIO_writePin(LEDS_PORT_ID,RED_PIN_NUM,1);
	GPIO_writePin(LEDS_PORT_ID,GREEN_PIN_NUM,1);
	GPIO_writePin(LEDS_PORT_ID,BLUE_PIN_NUM,1);

#endif
}




void LED_on(LED_ID id){

#if(CONNECTION_TYPE == POSITIVE)
	/*SETUP their values by ONE to turn the leds ON if they are connected in positive logic*/
	switch(id){
	case LED_RED :
		GPIO_writePin(LEDS_PORT_ID,RED_PIN_NUM,1);
		break;
	case LED_GREEN :
		GPIO_writePin(LEDS_PORT_ID,GREEN_PIN_NUM,1);
		break;
	case LED_BLUE :
		GPIO_writePin(LEDS_PORT_ID,BLUE_PIN_NUM,1);
		break;
	}
#elif(CONNECTION_TYPE == NEGATIVE)
	/*SETUP their values by ZERO to turn the leds ON if they are connected in negative logic*/
	switch(id){
	case LED_RED:GPIO_writePin(LEDS_PORT_ID,RED_PIN_NUM,0);
	break;
	case LED_GREEN:GPIO_writePin(LEDS_PORT_ID,GREEN_PIN_NUM,0);
	break;
	case LED_BLUE:GPIO_writePin(LEDS_PORT_ID,BLUE_PIN_NUM,0);
	break;
	}

#endif
}


void LED_off(LED_ID id){
#if(CONNECTION_TYPE == POSITIVE)
	/*SETUP their values by zero to turn the leds OFF if they are connected in positive logic*/
	switch(id){
	case LED_RED :GPIO_writePin(LEDS_PORT_ID,RED_PIN_NUM,0);
	break;
	case LED_GREEN :GPIO_writePin(LEDS_PORT_ID,GREEN_PIN_NUM,0);
	break;
	case LED_BLUE :GPIO_writePin(LEDS_PORT_ID,BLUE_PIN_NUM,0);
	break;
	}
#elif(CONNECTION_TYPE == NEGATIVE)
	/*SETUP their values by one to turn the leds OFF if they are connected in negative logic*/
	switch(id){
	case LED_RED:GPIO_writePin(LEDS_PORT_ID,RED_PIN_NUM,1);
	break;
	case LED_GREEN:GPIO_writePin(LEDS_PORT_ID,GREEN_PIN_NUM,1);
	break;
	case LED_BLUE:GPIO_writePin(LEDS_PORT_ID,BLUE_PIN_NUM,1);
	break;
	}
#endif

}


