/*
 * fan_power_unit_control.c
 *
 * Created: 10.04.2023 15:52:18
 *  Author: adaam
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void fan_power_unit_control(){
	
}

void timer1_config(){								//using mode 15 right now
TCCR1A = (1<<WGM11) | (1<<WGM10)	  // ?can use mode 14 with static frequency, variable duty cycle when OCR1A is incremented
		| (1<<COM1A0);// | (1<<CS11);  //NO PRESCALER HERE!!!! pre goes to the B counter
TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11);
			//|(1<<COM1B1)	;// | (1<<CS10);  //mode 14, need to set prescaler to 1, otherwise timer goes inactive and nothing happens
		
TIMSK1 = (1<<OCIE1A);		//interrupts on?
//ICR1 = 20000;   //       16000000/(8*(1+64)) = 30769.23077 Hz   //with TOP value 62+1 the resolution is 6 bit
OCR1A = 31; 
//OCR1B = 30;	//50% duty?, changing this does nothing to the blinky so far

  
//WGMA1
//sei();

// WGM1[1:0]	= 11;
// COM1[1:0]	= 11;
// CS1[2:0]`	= 010;
}

ISR(TIMER1_COMPA_vect){
PORTB ^= (1<<PB3);
}