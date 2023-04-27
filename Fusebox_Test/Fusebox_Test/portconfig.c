/*
 * portconfig.c
 *
 * Created: 10.04.2023 14:42:48
 *  Author: nico
 */ 

#include "portconfig.h"

volatile unsigned long sys_time = 0;

void pin_config(void)
{
	DDRB |= (1<<PB3) | (1<<PB4);
	DDRD |= (1<<R2D);
}

void sys_timer_config(void)
{
	//8 bit Timer 0 config
	//ctc mode and 64 as prescaler
	TCCR0A = 0 | (1<<WGM01) | (1<<CS01) | (1<<CS00);
	TIMSK0 = 0 | (1<<OCIE0A); //compare interrupt enable
	OCR0A = 250-1; // compare value for 1ms;<
}

void R2D_config(void)
{
	TCCR2A = 0 | (1<<WGM21) | (1<<CS22);
	TIMSK2 = 0 | (1<<OCIE2A); //compare interrupt enable
	OCR2A = 81-1;
}

void R2D_function(uint8_t Hi_thresh, uint8_t Lo_thresh, uint8_t R2D_switch)
{
	if (R2D_switch == 1)
	{
		OCR2A--;
		
		if (OCR2A == Hi_thresh)
		{
			R2D_switch = 0;
		}
	}
	
	if (R2D_switch == 0)
	{
		OCR2A++;
		
		if (OCR2A == Lo_thresh)
		{
			R2D_switch = 1;
		}
	}
}

ISR(TIMER0_COMP_vect)
{
	cli();
	sys_time++; //system time generation
	PORTB ^= (1<<PB4);
	sei();
}

ISR(TIMER2_COMP_vect)
{
	cli();
	PORTD ^= (1<<R2D);
	sei();
}