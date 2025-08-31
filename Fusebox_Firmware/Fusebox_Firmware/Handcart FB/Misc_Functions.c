#include "Misc_Functions.h"

volatile unsigned long sys_time = 0;

volatile unsigned char DRV_EN = 0;

void port_config(){  //0 input, 1 output
	// WP, fan and LED outputs
	DDRB =0;
	DDRE = 0;
	DDRB  |=(1<<PB0) | (1<<PB4);//&= ~(1<<PB4);
	DDRE |= (1<<PE0)|(1<<PE4)|(1<<PE7);
	//DDRE &= ~(1<<PE5);
	

    PORTB |= (1<<PB4);
	PORTE |= (1<<PE4);
}

void sys_timer_config(void)
{
	//CTC-Mode, /64
	TCCR0A = 0 | (1<<WGM01) | (1<<CS01) | (1<<CS00);
	//Compare value for 1ms (Formula in Datasheet)
	OCR0A = 249; //249
	//Compare Interrupt Enable
	TIMSK0 = 0 | (1<<OCIE0A);
}

void sys_tick_heart()
{
	PORTB ^= (1<<PB2); //toggle the Heart led on Pin 4, will be used in the super loop in main.c to indicade that the loop is running correctly	
};

void fault_not_detected()
{
	PORTB &= ~(1<<PB1); //turn off red led in case of no fault
}

void fault_detected()
{
	PORTB |= (1<<PB1); //turn on red led when called (fault present)
}

int16_t calculate_ac_current(uint16_t limit, uint16_t value){
	
	return (int16_t)((float)limit * ((float)value/10));
}

ISR(TIMER0_COMP_vect)
{
	sys_time++;	//system time incremented on each interrupt flag from the CTC mode compare register => every OCR0A
}