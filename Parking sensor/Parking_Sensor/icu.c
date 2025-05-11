/*
 * icu.c
 *
 *  Created on: Oct 14, 2024
 *      Author: YAHIA
 */


#include "icu.h"
#include "std_types.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>



volatile void (*call_back_ptr)(void) = NULL_PTR;


/*initialize timer 1 registers
 * set the required clock and edge detection*/
void ICU_init(void){

	/*setup the direction of the pin of input capture unit as input*/
	DDRD &= ~(1<<PD6);

	/*setup compare mode for channel A and channel B*/
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);

	/*setup the required clock
	 * CLK/8
	 * input capture on rising edge*/
	TCCR1B = (1<<CS11) | (1<<ICES1);

	/*initial value for timer1*/
	TCNT1 = 0;

	/*initial value for input capture register*/
	ICR1 = 0;

	/*enable the input capture enable*/
	TIMSK |= (1<<TICIE1);

	/*enable global interrupts*/
	SREG |= (1<<7);

}



/*ISR for input capture interrupt*/
ISR(TIMER1_CAPT_vect){

	if(call_back_ptr != NULL_PTR){

		(*call_back_ptr)();

	}
}



void ICU_setCallBack(void(*ptr)(void)){
	call_back_ptr = ptr;
}



uint16 ICU_getInput(void){
	return ICR1;
}


void ICU_clearTimer(void){
	TCNT1 = 0;
}

/*to choose the type of the edge detection*/
void ICU_setEdgeDetectionType(EdgeType type){
	if(type == RAISING){
		TCCR1B |= (1<<ICES1);
	}
	else if(type == FALLING){
		TCCR1B &= ~(1<<ICES1);
	}
}
