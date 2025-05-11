/*
 * PWM_TIMER0.c
 *
 *  Created on: Oct 7, 2024
 *      Author: YAHIA
 */


#include "PWM_TIMER0.h"
#include "std_types.h"
#include "common_macros.h"
#include "avr/io.h"


void PWM_Timer0_Start(uint8 duty_cycle){
	/*initialize timer0 to operate on fast PWM
	 * setup the prescaler to 1024
	 * non inverting mode*/
	TCCR0 = (1<<WGM01)|(1<<WGM00)|(1<<CS02)|(1<<CS00)|(1 << COM01);


	/*convert the duty cycle entered by user to an integer
	 * to initialize the OCR0 register*/
	 uint8 value = (uint8)(((uint16)duty_cycle * 255) / 100);
	 OCR0 = value;


	/*configure OC0 as an output pin*/
	SET_BIT(DDRB,PIN3);
}

void PWM_Timer0_stop(void){
	TCCR0 = 0;
}
