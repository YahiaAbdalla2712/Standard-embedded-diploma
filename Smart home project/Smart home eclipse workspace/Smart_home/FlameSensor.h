/*
 * FlameSensor.h
 *
 *  Created on: Oct 7, 2024
 *      Author: YAHIA
 */

#ifndef FLAMESENSOR_H_
#define FLAMESENSOR_H_

#include "std_types.h"

/*function to initialize the flame sensor pin as input pin
 * also take the port_id and pin_num from the user*/
void FlameSensor_init(uint8 PORT_ID, uint8 PIN_ID);


/*function to read the value on the pin of the sensor*/
uint8 FlameSensor_getValue(void);


#endif /* FLAMESENSOR_H_ */
