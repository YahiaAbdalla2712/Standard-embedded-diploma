#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


/*To light up the 7 segment*/
void lightup(int i);

/* initialize Timer 1 compare a*/
void TIMER1_INIT(void);

/*A tick variable to count seconds*/
unsigned char tick_1= 0;
unsigned char tick_2= 0;
unsigned char tick_3= 0;
unsigned char tick_4= 0;
unsigned char tick_5= 0;
unsigned char tick_6= 0;

int count_mode = 0; /*0 for counting_up and 1 for counting_down*/
int adjusting_time_mode = 0; /*variable to indicate adjusting time*/

/*initialize interrupt zero*/
void INT0_INIT(void);

/*initialize interrupt two*/
void INT2_INIT(void);

/*initialize interrupt one*/
void INIT1_INIT(void);

/*function to display time*/
void display_time(void);


/*Main*/
int main(void){
	DDRC |= (1<<0)|(1<<1)|(1<<2)|(1<<3); /*direction of the decoder as an output*/
	PORTC &= ~(0x0F);

	DDRA |= (1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);/*direction of the enable of the seven segment as an output*/
	PORTA |= (1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);

	TIMER1_INIT();

	DDRD |= (1<<4)|(1<<5);/*direction of LEDs as outputs*/
	PORTD |= (1<<4);/*Initially the count up mode is active*/

	INT0_INIT();

	DDRD &= ~(1<<2);/*direction of reset button as input*/
	PORTD |= (1<<2);/*configure internal pull up resistor*/

	INT2_INIT();
	DDRB &= ~(1<<2);/*direction of resume button as input*/
	PORTB |= (1<<2);/*configure internal pull up resistor*/

	INIT1_INIT();
	DDRD &= ~(1<<3);/*direction of pause button as input*/

	DDRB &= ~(0xFB);/*direction of increment and decrement buttons as inputs*/
	PORTB |= (0xFF);/*configure all with internal pull up resistors*/

	DDRD |= (1<<0);/*direction of buzzer as output*/
	PORTD &= ~(1<<0);/*initially buzzer is off*/

	while(1){
		display_time();
		if(!(PINB & (1<<7))){
			TIMSK &= ~(1<<OCIE1A);
			PORTD ^= (1<<4);
			PORTD ^= (1<<5);
			count_mode = ~ count_mode;
			adjusting_time_mode = 1;
			}


		if(!(PINB & (1<<1)) && adjusting_time_mode){
				if(tick_5 == 9){
					tick_5 = 0;
					tick_6 ++;
					}
					else{
						tick_5++;
					}
				while(!(PINB & (1<<1))){
					display_time();
				}
			}
		if(!(PINB & (1<<0)) && adjusting_time_mode){
			tick_5--;
			if(tick_5 == 0){
				tick_5 = 0;
				}
			while(!(PINB & (1<<0))){
				display_time();
			}
		}
		if(!(PINB & (1<<4)) && adjusting_time_mode){
			if(tick_3 == 9){
				tick_4 ++;
				tick_3 = 0;
				}
			else{
				tick_3++;
				}
			while(!(PINB & (1<<4))){
				display_time();
			}
		}
		if(!(PINB & (1<<3)) && adjusting_time_mode){
			tick_3--;
			if(tick_3 == 0){
				tick_3 = 0;
				}
			while(!(PINB & (1<<3))){
				display_time();
			}
		}
		if(!(PINB & (1<<6)) && adjusting_time_mode){
			if(tick_1 == 9){
				tick_1 = 0;
				tick_2 ++;
				}
			else{
				tick_1++;
				}
			while(!(PINB & (1<<6))){
			display_time();
			}
		}
		if(!(PINB & (1<<5)) && adjusting_time_mode){
				tick_1--;
				if(tick_1==0){
					tick_1=0;
					}
				while(!(PINB & (1<<5))){
					display_time();
				}
			}
			if(!(PINB & (1<<2))){
					adjusting_time_mode = 0;
				}
		}
	return 0;
}










void lightup(int i){

	switch(i){
	case 0:
		PORTC &= ~(0x0F);
		break;
	case 1:
		PORTC |= (1<<0);
		PORTC &= ~(0x0E);
		break;
	case 2:
		PORTC |= (1<<1);
		PORTC &= ~(0x0D);
		break;
	case 3:
		PORTC |= (1<<1)|(1<<0);
		PORTC &= ~(0x0C);
		break;
	case 4:
		PORTC |= (1<<2);
		PORTC &= ~(0x0B);
		break;
	case 5:
		PORTC |= (1<<2)|(1<<0);
		PORTC &= ~(0x0A);
		break;
	case 6:
		PORTC |= (1<<2)|(1<<1);
		PORTC &= ~(0x09);
		break;
	case 7:
		PORTC |= (1<<2)|(1<<1)|(1<<0);
		PORTC &= ~(0x08);
		break;
	case 8:
		PORTC |= (1<<3);
		PORTC &= ~(0x07);
		break;
	case 9:
		PORTC |= (1<<3)|(1<<0);
		PORTC &= ~(0x06);
		break;
	}
}



void TIMER1_INIT(void){
	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<WGM12)|(1<<CS12);
	OCR1A = 62500-1;
	TIMSK |= (1<<OCIE1A);
	SREG |=(1<<7);
}



/*ISR for Timer 1*/
ISR(TIMER1_COMPA_vect){
	if(!(count_mode)){
		if(tick_1 == 9){
			tick_1 = 0;
			if(tick_2 == 5){
				tick_2 = 0;
				if(tick_3 == 9){
					tick_3 = 0;
					if(tick_4 == 5){
						tick_4 = 0;
						if((tick_5 == 9) || (tick_5 == 3)){
							if((tick_5 == 9)){
								tick_5 = 0;
								tick_6 ++;
							}
							else if((tick_5 == 3)&&(tick_6 == 2)){
								tick_1=tick_2=tick_3=tick_4=tick_5=tick_6=0;
							}
							else{
								tick_5 ++;
							}
						}
						else{
							tick_5 ++;
						}
					}
					else{
						tick_4++;
					}
				}
				else{
					tick_3 ++;
				}
			}
			else{
				tick_2 ++;
			}
		}
		else{
			tick_1 ++;
		}
	}
	else {
	    if (tick_1 > 0) {
	        tick_1--;
	    }
	    else if (tick_1 == 0 && tick_2 > 0) {
	        tick_1 = 9;
	        tick_2--;
	    }
	    else if (tick_1 == 0 && tick_2 == 0) {
	        if (tick_3 > 0) {
	            tick_1 = 9;
	            tick_2 = 5;
	            tick_3--;
	        }
	        else if (tick_3 == 0 && tick_4 > 0) {
	            tick_1 = 9;
	            tick_2 = 5;
	            tick_3 = 9;
	            tick_4--;
	        }
	        else if (tick_3 == 0 && tick_4 == 0) {
	            if (tick_5 > 0) {
	                tick_1 = 9;
	                tick_2 = 5;
	                tick_3 = 9;
	                tick_4 = 5;
	                tick_5--;
	            }
	            else if (tick_5 == 0 && tick_6 > 0) {
	                tick_1 = 9;
	                tick_2 = 5;
	                tick_3 = 9;
	                tick_4 = 5;
	                tick_5 = 9;
	                tick_6--;
	            }
	            else if (tick_5 == 0 && tick_6 == 0) {
	                PORTD |= (1<<0);  /* Alarm on */
	                _delay_ms(50);
	            }
	        }
	    }
	}
}


void INT0_INIT(void){
	MCUCR |= (1<<1);
	MCUCR &= ~(1<<0);/*INTERUPT0 gives interrupt request at fallen edge*/
	GICR |= (1<<6);
	SREG |= (1<<7);
}

/*ISR for INT0(RESET button)*/
ISR(INT0_vect){
	tick_1=tick_2=tick_3=tick_4=tick_5=tick_6=0;
}


void INT2_INIT(void){
	MCUCSR &= ~(1<<ISC2);/*INTERRUPT2 gives interrupt request at fallen edge*/
	GICR |= (1<<5);
	SREG |= (1<<7);
}

/*ISR for INT2(RESUME button)*/
ISR(INT2_vect){
	TIMSK |= (1<<OCIE1A);/*enable timer clock again*/
}

void INIT1_INIT(void){
	MCUCR |= (1<<ISC11)|(1<<ISC10);/*INTERRUPT1 gives interrupt request at rising edge*/
	GICR |= (1<<7);
	SREG |= (1<<7);
}

/*ISR for INT1(PAUSE button)*/
ISR(INT1_vect){
	TIMSK &= ~(1<<OCIE1A);
}
void display_time(void){
	PORTA &= 0x00;
	PORTA |= (1<<5); /*enable first 7 segment*/

	lightup(tick_1);
	_delay_ms(2);

	PORTA &= 0x00;
	PORTA |= (1<<4); /*enable 2nd 7 segment*/

	lightup(tick_2);
	_delay_ms(2);

	PORTA &= 0x00;
	PORTA |= (1<<3); /*enable third 7 segment*/

	lightup(tick_3);
	_delay_ms(2);

	PORTA &= 0x00;
	PORTA |= (1<<2); /*enable fourth 7 segment*/

	lightup(tick_4);
	_delay_ms(2);

	PORTA &= 0x00;
	PORTA |= (1<<1);/*enable fifth 7 segment*/

	lightup(tick_5);
	_delay_ms(2);

	PORTA &= 0x00;
	PORTA |= (1<<0);/*enable sixth 7 segment*/

	lightup(tick_6);
	_delay_ms(2);

}


