/*
 * icu.h
 *
 *  Created on: Oct 14, 2024
 *      Author: YAHIA
 */

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"


typedef enum{
	RAISING,FALLING
}EdgeType;



void ICU_init(void);

void ICU_setCallBack(void(*ptr)(void));

uint16 ICU_getInput(void);

void ICU_clearTimer(void);

void ICU_setEdgeDetectionType(EdgeType type);

#endif /* ICU_H_ */
