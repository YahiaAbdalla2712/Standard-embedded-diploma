/*
 * DC_motor.h
 *
 *  Created on: Oct 7, 2024
 *      Author: YAHIA
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*ENUM to determine the states of the motor*/
typedef enum{
	STOP, CLOCKWISE, ANTI_CLOCKWISE
}DcMotor_State;



void DcMotor_Init(void);


void DcMotor_Rotate(DcMotor_State state, uint8 speed);


#endif /* DC_MOTOR_H_ */
