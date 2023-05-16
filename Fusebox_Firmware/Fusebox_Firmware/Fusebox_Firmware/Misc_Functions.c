


/*
 ***********************************************************************************************************************************************************************************************
 *																				MISCELLANEOUS FUNCTIONS
 * Description : A "miscellaneous functions" or "misc_functions" file is typically used to contain general port, timer and rudimentary function configurations.
 *				 
 **				 "port_config" is usually the first piece of code written in a project, setting the Data Direction Registers to input/output.  1/0 WHAT IS
 *				 
 **				 "sys_timer_config" sets up the general timer for executing code in our main() function. Here it's set to go from BOTTOM to TOP and execute a compare
 *				 match at OCR0A = 250. GO STEP BY STEP AND EXPLAIN CHOICE
 *				 
 **				 "ISR(TIMER0_COMP_vect)" increments the sys_time variable on each compare match, which is 1 ms in our example.
 *				 
 **				 "sys_tick_heart" toggles the blue LED whenever it's called. WHAT IS XOR
 *				 
 **				 "fault_not_detected" and "fault_detected" control the red LED whenever called. NAND AND OR WHAT DO?
 * 				 
 *				 
 *				 
 ***********************************************************************************************************************************************************************************************
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long sys_time = 0;


void port_config(){  //0 input, 1 output
	DDRA = 0;   //Fuse Read Out Inputs
	
	//DDRB &= ~(1<<PB1);
	//PORTB |= (1<<PB1);
	//MCUCR &= ~(1<<PUD);

	DDRB = 0 | (1<<PB0) |(1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5); //WP, fan and LED outputs
	DDRC = 0; // Shutdown circuit just like FRO is an input (indicates the state of those pins for debugging purposes)
	DDRD = 0 | (1<<PD2) | (1<<PD3) | (1<<PD5) | (1<<PD6); // timer for the buzzer and can outputs
	DDRE = 0; //Fuse Read Out Inputs
	DDRF = 0;
}

void sys_timer_config(){  
	TCCR0A |= (1<<WGM01); //CTC mode
	TCCR0A |= (1<<CS01) | (1<<CS00); //prescaler 64
	TIMSK0 |= (1<<OCF0A);  //interrupt flags enable
	OCR0A = 250;  //TOP for 1ms 
}

void sys_tick_heart(){
	PORTB ^= (1<<PB4); //toggle the Heart led on Pin 4, will be controlled by the super loop in main.c
	
};

ISR(TIMER0_COMP_vect){
	sys_time++;  //system time incremented on each interrupt flag from the CTC compare register => every OCR0A
	
}

void fault_not_detected(){
	
	PORTB &= ~(1<<PB3); //turn off red led in case of no fault
}
void fault_detected(){
	
	PORTB |= (1<<PB3); //turn on red led when called (fault present)
}