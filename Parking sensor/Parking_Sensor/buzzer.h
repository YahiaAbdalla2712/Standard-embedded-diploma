/*
 * buzzer.h
 *
 *  Created on: Oct 8, 2024
 *      Author: YAHIA
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"


#define BUZZER_PORT_ID PORTC_ID
#define BUZZER_PIN_NUM PIN5_ID

/*function to initialize the buzzer pin as output pin
 * also take from user the port_id and pin_id*/
void Buzzer_init(void);

/*function to turn on the buzzer*/
void Buzzer_on(void);

/*function to turn off the buzzer*/
void Buzzer_off(void);


#endif /* BUZZER_H_ */
