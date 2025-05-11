/*
 * APP.c
 *
 *  Created on: Oct 11, 2024
 *      Author: YAHIA
 */


#include "common_macros.h"
#include "std_types.h"
#include "lcd.h"
#include "leds.h"
#include "buzzer.h"
#include "ultrasonic.h"
#include <util/delay.h>



void led_flash(void);

void display_distance(uint16 distance){
	LCD_displayStringRowColumn(0,0,"Distance=    cm");
	LCD_moveCursor(0,9);
	LCD_intgerToString(distance);
}

int main(void){

	/*declare a variable for the distance measured from the sensor*/
	uint16 measured_distance;

	/*initialize the ultra sonic sensor and the ICU*/
	Ultrasonic_init();

	/*initialize the leds*/
	LEDS_init();

	/*initialize the lcd*/
	LCD_init();

	/*initialize the buzzer*/
	Buzzer_init();

	while(1){
		measured_distance = Ultrasonic_readDistance()+1;
		display_distance(measured_distance);

		if(measured_distance <= 5){
			LCD_clearScreen();
			while(measured_distance<=5){
				LCD_displayStringRowColumn(0,7,"Stop");
				measured_distance = Ultrasonic_readDistance()+1;
				Buzzer_on();
				led_flash();
			}
		}
		else if((measured_distance>=6) && (measured_distance <= 10)){
			Buzzer_off();
			LED_on(LED_RED);
			LED_on(LED_GREEN);
			LED_on(LED_BLUE);
		}
		else if((measured_distance>=11) && (measured_distance<=15)){
			Buzzer_off();
			LED_off(LED_BLUE);
			LED_on(LED_RED);
			LED_on(LED_GREEN);
		}
		else if((measured_distance>=16) && (measured_distance <=20)){
			Buzzer_off();
		    LED_off(LED_BLUE);
		    LED_off(LED_GREEN);
		    LED_on(LED_RED);
		}
		else {
			Buzzer_off();
			LED_off(LED_RED);
			LED_off(LED_GREEN);
			LED_off(LED_BLUE);
		}
	}


	return 0;
}


/*function responsible for flashing the leds*/
void led_flash(void){
	LED_on(LED_RED);
	LED_on(LED_GREEN);
	LED_on(LED_BLUE);
	_delay_ms(500);
	LED_off(LED_RED);
	LED_off(LED_GREEN);
	LED_off(LED_BLUE);
	_delay_ms(500);
}
