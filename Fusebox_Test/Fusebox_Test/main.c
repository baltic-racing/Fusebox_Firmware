/*
 * Fusebox_Test.c
 *
 * Created: 10.04.2023 14:41:07
 * Author : nico
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "portconfig.h"


int main(void)
{
	PORTD |= (PD2<<1);
/*    uint8_t time_fault = 100;
	uint8_t time_R2D = 1;
	uint8_t TIM2_toggle = 0;
	uint8_t TIM2_Lo = 50;
	uint8_t TIM2_Hi = 30;
	extern unsigned long sys_time;
	
	pin_config();
	sys_timer_config();
	R2D_config();
	
	sei();
	
    while (1) 
    {		
		if (sys_time >= time_R2D)
		{
			R2D_function(TIM2_Hi, TIM2_Lo, TIM2_toggle);
		}
		if (sys_time >= time_fault)
		{
			sys_time = 0;
			PORTB ^= (1<<PB3);

		}
		
    }*/
}

