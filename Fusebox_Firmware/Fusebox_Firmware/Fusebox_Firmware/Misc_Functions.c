


/*
 ***********************************************************************************************************************************************************************************************
 *																				MISCELLANEOUS FUNCTIONS
 * Description : A "miscellaneous functions" or "misc_functions" file is typically used to contain general port, timer and rudimentary function configurations.
 *				 
 **				 "port_config" is usually the first piece of code written in a project, setting the Data Direction Registers to input/output. As described in the I/O 
 *				 section on page 68 of the AVR documentation, setting DDRx to 1, means that the x Pin is set to output => your uC will give you data (for example PWM signals or logic states),
 *				 writing DDRx to 0 changes it to input => you are the one providing data for your uC (for example sensors or CAN data). Note that the Data Direction needs to be set to output
 *				 to drive the logic levels of the pins (0 - low, 1 - high).
 *
 **				 "sys_timer_config" sets up the general timer for executing code in our main() function. Here it's set to go from BOTTOM to TOP and execute a compare
 *				 match at OCR0A = 124. Here we are using the CTC mode, described on page 104, to generate a 1kHz waveform.
 *				 
 **				 "ISR(TIMER0_COMP_vect)" increments the sys_time variable on each compare match, which is 1 ms in our example.
 *				 
 **				 "sys_tick_heart" toggles the blue LED whenever it's called. WHAT IS XOR
 *				 
 **				 "fault_not_detected" and "fault_detected" control the red LED whenever called. NAND AND OR WHAT DO?
 * Notes       : 1) The basis for calculating frequencies of various timers is the CLKio oscillator which runs at 16 MHz (16 000 000)				 
 *				 
 *				 
 ***********************************************************************************************************************************************************************************************
*/
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long sys_time = 0;

volatile unsigned char DRV_EN = 0;

void port_config(){  //0 input, 1 output
	DDRA = 0;   //Fuse Read Out Inputs
	DDRB = 0 | (1<<PB0) |(1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5); //WP, fan and LED outputs
	DDRC = 0; // Shutdown circuit just like FRO is an input 
	DDRD = 0 | (1<<PD2) | (1<<PD3) | (1<<PD5); /*| (1<<PD6);SET TO 0?*/ // timer for the buzzer and can outputs, PD5 transmits to CAN, PD6 is a receiver
	DDRE = 0; //Fuse Read Out Inputs
	DDRF = 0; //JTAG and 2 ADC readings inputs
}

void sys_timer_config(){  
	TCCR0A |= (1<<WGM01); //CTC mode
	TCCR0A |= (1<<CS01) | (1<<CS00); //prescaler 64 => page 111
	TIMSK0 |= (1<<OCF0A);  //interrupt flags enable
	OCR0A = 124;  //TOP for 1ms   => 16000000/2*64*(1+124) = 1000 Hz
}

void sys_tick_heart(){
	PORTB ^= (1<<PB4); //toggle the Heart led on Pin 4, will be used in the super loop in main.c to indicade that the loop is running correctly	
};

ISR(TIMER0_COMP_vect){
//	cli();
	sys_time++;  //system time incremented on each interrupt flag from the CTC mode compare register => every OCR0A
	//sei();
}

void fault_not_detected(){	
	PORTB &= ~(1<<PB3); //turn off red led in case of no fault
}

void fault_detected(){
	PORTB |= (1<<PB3); //turn on red led when called (fault present)
}

void tractive_system_activate(uint8_t *data){
	if (data[1]){
		DRV_EN = 1;
	}else{
		DRV_EN = 0;
	}
}

int16_t calculate_ac_current(uint16_t limit, uint16_t value){
		
	return ((int16_t)limit * ((int16_t)value/100) * 10);
}


//setting up sys timer
// 		if((sys_time - sys_time_old) >= 1){
// 			sys_time_old = sys_time;   //MAYBE USE THIS AS FIRST TIMER AND THE BUILD THE 10 and 100 ONES ON TOP OF IT?
// 			time_X_ms++;
// 		}
// after this add any timers time_10_ms, time_20_ms ...