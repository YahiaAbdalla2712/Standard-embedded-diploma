/*
 * DC_motor.c
 *
 *  Created on: Oct 7, 2024
 *      Author: YAHIA
 */


#include "DC_motor.h"
#include "common_macros.h"
#include "std_types.h"
#include <avr/io.h>
#include "gpio.h"
#include "PWM_TIMER0.h"

void DcMotor_Init(void){
	/*Setup the direction of the pins of the H-bridge as outputs*/
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);


	/*Initialize the motor to stop rotating*/
	GPIO_writePin(PORTB_ID,PIN0_ID,0);
	GPIO_writePin(PORTB_ID,PIN1_ID,0);

	/*enable the motor to rotate*/
	GPIO_writePin(PORTB_ID,PIN3_ID,1);
}



void DcMotor_Rotate(DcMotor_State state, uint8 speed){
	switch (state){
	case STOP:
		GPIO_writePin(PORTB_ID,PIN0_ID,0);
		GPIO_writePin(PORTB_ID,PIN1_ID,0);
		PWM_Timer0_stop();
		break;
	case CLOCKWISE:
		GPIO_writePin(PORTB_ID,PIN0_ID,0);
		GPIO_writePin(PORTB_ID,PIN1_ID,1);
		PWM_Timer0_Start(speed);
		break;
	case ANTI_CLOCKWISE:
		GPIO_writePin(PORTB_ID,PIN0_ID,1);
		GPIO_writePin(PORTB_ID,PIN1_ID,0);
		PWM_Timer0_Start(speed);
		break;
	}
}
