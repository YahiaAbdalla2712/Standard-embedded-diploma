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




uint8 PORT_ID,RED_PIN,GREEN_PIN,BLUE_PIN;
connection_type TYPE;

/*A function to initialize the direction of the leds as outputs
 * initially turn off all leds if they are connected in positive logic*/
void LEDS_init(uint8 port_id,uint8 red_pin,uint8 green_pin,uint8 blue_pin,connection_type type){
	PORT_ID = port_id;
	RED_PIN = red_pin;
	GREEN_PIN = green_pin;
	BLUE_PIN = blue_pin;
	TYPE = type;


	/*setup the direction of the leds as outputs*/
	GPIO_setupPinDirection(PORT_ID,RED_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_ID,GREEN_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_ID,BLUE_PIN,PIN_OUTPUT);

	if(TYPE == POSITIVE){
		/*initialize their values by zero to turn the leds off if they are connected in positive logic*/
		GPIO_writePin(PORT_ID,RED_PIN,0);
		GPIO_writePin(PORT_ID,GREEN_PIN,0);
		GPIO_writePin(PORT_ID,BLUE_PIN,0);
	}
	else if(TYPE == NEGATIVE){
		/*initialize their values by ONE to turn the leds off if they are connected in negative logic*/
		GPIO_writePin(PORT_ID,RED_PIN,1);
		GPIO_writePin(PORT_ID,GREEN_PIN,1);
		GPIO_writePin(PORT_ID,BLUE_PIN,1);
	}

}




void LED_on(LED_ID id){

	if(TYPE == POSITIVE){
		/*SETUP their values by ONE to turn the leds ON if they are connected in positive logic*/
		switch(id){
		case RED:GPIO_writePin(PORT_ID,RED_PIN,1);
		break;
		case GREEN:GPIO_writePin(PORT_ID,GREEN_PIN,1);
		break;
		case BLUE:GPIO_writePin(PORT_ID,BLUE_PIN,1);
		break;
		}
	}
	else if(TYPE == NEGATIVE){
		/*SETUP their values by ZERO to turn the leds ON if they are connected in negative logic*/
		switch(id){
		case RED:GPIO_writePin(PORT_ID,RED_PIN,0);
		break;
		case GREEN:GPIO_writePin(PORT_ID,GREEN_PIN,0);
		break;
		case BLUE:GPIO_writePin(PORT_ID,BLUE_PIN,0);
		break;
		}
	}
}


void LED_off(LED_ID id){
	if(TYPE == POSITIVE){
		/*SETUP their values by zero to turn the leds OFF if they are connected in positive logic*/
		switch(id){
		case RED:GPIO_writePin(PORT_ID,RED_PIN,0);
		break;
		case GREEN:GPIO_writePin(PORT_ID,GREEN_PIN,0);
		break;
		case BLUE:GPIO_writePin(PORT_ID,BLUE_PIN,0);
		break;
		}
	}
	else if(TYPE == NEGATIVE){
		/*SETUP their values by one to turn the leds OFF if they are connected in negative logic*/
		switch(id){
		case RED:GPIO_writePin(PORT_ID,RED_PIN,1);
		break;
		case GREEN:GPIO_writePin(PORT_ID,GREEN_PIN,1);
		break;
		case BLUE:GPIO_writePin(PORT_ID,BLUE_PIN,1);
		break;
		}
	}
}


