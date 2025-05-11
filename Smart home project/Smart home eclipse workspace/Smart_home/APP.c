/*
 * APP.c
 *
 *  Created on: Oct 7, 2024
 *      Author: YAHIA
 */

#include "common_macros.h"
#include "std_types.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "DC_motor.h"
#include "FlameSensor.h"
#include "leds.h"
#include "buzzer.h"
#include "adc.h"



/*definitions*/
#define LEDS_PORT_ID 		1
#define RED_LED_PIN			5
#define GREEN_LED_PIN		6
#define BLUE_LED_PIN		7

#define FLAME_SENSOR_PORT_ID 3
#define FLAME_SENSOR_PIN_NUM 2

#define BUZZER_PORT_ID		3
#define BUZZER_PIN_NUM		3




int main(void){

	/*declare a variable for the light intensity*/
	uint16 light_intensity;

	/*declare a variable for the temperature reading*/
	uint8 temperature;

	/*declare a variable for the flame sensor reading*/
	uint8 flame;

	/*initialize the leds as they are all turned off
	 * also chose the type of connection as positive logic*/
	LEDS_init(LEDS_PORT_ID,RED_LED_PIN,GREEN_LED_PIN,BLUE_LED_PIN,POSITIVE);

	/*initialize the adc */
	ADC_init();

	/*initialize the lcd in 8 bit mode*/
	LCD_init();

	/*Initially the fan is turned off*/
	LCD_displayStringRowColumn(0,0,"FAN IS OFF");

	/*Initialize the DC_motor*/
	DcMotor_Init();

	/*Initialize the flame sensor port_id and pin_num*/
	FlameSensor_init(FLAME_SENSOR_PORT_ID,FLAME_SENSOR_PIN_NUM);

	/*Initialize the buzzer*/
	Buzzer_init(BUZZER_PORT_ID,BUZZER_PIN_NUM);

	while(1){
		/*get the flame sensor reading*/
		flame = FlameSensor_getValue();

		/*check if there is fire or not*/
		if (flame) {
			while(flame){
				flame = FlameSensor_getValue();
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "Fire alert!");
				Buzzer_on();
			}
		} else {
		    Buzzer_off();
		}
		/*stop the buzzer if it was working*/
		Buzzer_off();

		/*get light intensity percentage reading from the sensor*/
		light_intensity = LDR_getLightIntensity();

		/*get temperature reading from the lm35_sensor*/
		temperature = LM35_getTemperature();


		/*keep printing the temperature and LDR reading on lcd*/
		LCD_displayStringRowColumn(1,0,"Temp=");
		LCD_moveCursor(1,5);
		LCD_intgerToString(temperature);
		LCD_moveCursor(1,7);
		LCD_displayCharacter('C');
		LCD_displayStringRowColumn(1,9,"LDR=");
		LCD_moveCursor(1,13);
		LCD_intgerToString(light_intensity);
		LCD_moveCursor(1,15);
		LCD_displayCharacter('%');

		/*if light intensity is less than 15% all 3 leds should be turned on*/
		if(light_intensity<15){
			LED_on(RED);
			LED_on(GREEN);
			LED_on(BLUE);
		}
		/*if light intensity is between 16% and 50% red and green leds only should be turned on*/
		else if((light_intensity>=16)&&(light_intensity<=50)){
			LED_off(RED);
			LED_off(GREEN);
			LED_off(BLUE);
			LED_on(RED);
			LED_on(GREEN);
		}
		/*If the light intensity is between 51% and 70% only the red led should be turned on*/
		else if((light_intensity>=51)&&(light_intensity<=70)){
			LED_off(RED);
			LED_off(GREEN);
			LED_off(BLUE);
			LED_on(RED);
		}
		/*if the light intensity is greater than 70% then all leds should be off*/
		else{
			LED_off(RED);
			LED_off(GREEN);
			LED_off(BLUE);
		}


		/*if temperature is above 40C then the fan should be turned on
		 * additionally the motor should rotate at full speed
		 * print on lcd that the fan is on and the speed of the motor
		 */
		if(temperature >= 40){
			LCD_displayStringRowColumn(0,0,"FAN IS ON ");
			DcMotor_Rotate(CLOCKWISE,100);
		}
		/*if the temperature is between 35C and 40C then the fan should be turned on
		 * the motor should rotate at 75% of its full speed
		 * then print on the lcd that the fan is turned on*/
		else if((temperature>=35)&&(temperature<40)){
			LCD_displayStringRowColumn(0,0,"FAN IS ON ");
			DcMotor_Rotate(CLOCKWISE,75);
		}
		/*if the temperature is between 30C and 35C then the fan should be turned on
		 * the motor should rotate at 50% of its full speed
		 * then print on the lcd that the fan is turned on*/
		else if((temperature>=30)&&(temperature<35)){
			LCD_displayStringRowColumn(0,0,"FAN IS ON ");
			DcMotor_Rotate(CLOCKWISE,50);
		}
		/*if the temperature is between 25C and 30C then the fan should be turned on
		 * the motor should rotate at 25% of its full speed
		 * then print on the lcd that the fan is turned on*/
		else if((temperature>=25)&&(temperature<30)){
			LCD_displayStringRowColumn(0,0,"FAN IS ON ");
			DcMotor_Rotate(CLOCKWISE,25);
		}
		/*if the temperature is less than 25C then the fan should be turned off
		 * the lcd print that is the fan is off*/
		else{
			LCD_displayStringRowColumn(0,0,"FAN IS OFF");
			DcMotor_Rotate(STOP,0);
		}

	}




	return 0;
}
