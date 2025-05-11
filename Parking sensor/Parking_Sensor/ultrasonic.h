/*
 * ultrasonic.h
 *
 *  Created on: Oct 15, 2024
 *      Author: YAHIA
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

#define TRIGGER_PORT	PORTD_ID
#define TRIGGER_PIN		PIN7_ID


void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
