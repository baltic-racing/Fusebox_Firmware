
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long sys_time = 0;

void port_config(){
	DDRA = 0;   //Fuse Read Out Inputs
	DDRB = 0 | (1<<PB0) | (1<<PB1) |(1<<PB2) | (1<<PB3) | (1<<PB4); //WP, fan and LED outputs
	DDRC = 0; // Shutdown circuit just like FRO is an input (indicates the state of those pins for debugging purposes)
	DDRD = 0 | (1<<PD2) | (1<<PD3) | (1<<PD5) | (1<<PD6); // timer for the buzzer and can outputs
	DDRE = 0; //Fuse Read Out Inputs
	DDRF = 0; /*| (1<<PF4) | (1<<PF5) | (1<<PF6) | (1<<PF7);*/ // should i set these as output?
}

void sys_timer_config(){   //all previous software uses a 1ms timer/counter =>CTC with OCR0A=250
	TCCR0A |= (1<<WGM01);
	TCCR0A |= (1<<CS01) | (1<<CS00);
	TIMSK0 |= (1<<OCF0A);  //interrupt flags possible
	OCR0A = 250; // what timer do we need, btw the compiler doesnt like anything bigger than 300 for some reason (reason is the 2^8 bits = 256)
}

void sys_tick_heart(){
	PORTB ^= (1<<PB4); //toggle the Heart led on Pin 4, will be controlled by the super loop in main.c
	
};

ISR(TIMER0_COMP_vect){
	sys_time++;  //system time incremented on each interrupt flag from the CTC compare register => every OCR0A
}