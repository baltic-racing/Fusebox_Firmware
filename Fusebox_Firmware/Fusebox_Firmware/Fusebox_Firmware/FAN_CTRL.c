#include "FAN_CTRL.h"

volatile uint16_t fan_dc;
volatile uint8_t case_counter = 0;

uint16_t getfanspeed(uint8_t temp){
	
	if (temp < TEMPMIN){
		temp = TEMPMIN;
	}
	if (temp > TEMPMAX){
		temp = TEMPMAX;
	}
	
	uint16_t speed = (((FANSPEEDMAX-FANSPEEDMIN)/(TEMPMAX-TEMPMIN))*(temp-TEMPMIN))+FANSPEEDMIN;
	return speed;
	 
}
void timer1_config(){
	
	//CONFIG FOR THE SERVO CONTROL
	//USING TIMER 1 COMPARE A INTERRUPT
	//16 bit Timer 1 config
	//CTC mode and a prescaler of 8
	TCCR1B |= (1<<CS11) | (1<<WGM12);
	TIMSK1 |= (1<<OCIE1A);
	OCR1A = 4200; 
	
}
	
// ISR for the timer 1, updating the duty cycle
ISR(TIMER1_COMPA_vect){
	//cli();
	uint16_t timer_max = 4300;
	switch (case_counter){
		case 0:
			FAN1_PORT |= (1<<FAN1_PIN);
			FAN2_PORT |= (1<<FAN2_PIN);
			case_counter=1;
			OCR1A = fan_dc;
			break;
		case 1:
			FAN1_PORT &= ~(1<<FAN1_PIN);
			FAN2_PORT &= ~(1<<FAN2_PIN);
			OCR1A = timer_max-fan_dc;
			case_counter=0;
			break;
		
	}
	
}