/*
 * Fusebox_Firmware.c
 *
 * Created: 13.02.2023 11:41:48
 * Author : adaam
 */ 
//attempt 1
// int main(void)
//     DDRB = 00011000;   //PB3 and 4 set to output with the data direction register
//     PORTB = 0x00;  // Initial state - all ports logic 0
//     while (1)
//     {
// 	PORTB |= (1<<PB3);		 // Bit 3 set to 1 (red on)
// 	_delay_ms(250);
// 	PORTB &= ~(1<<PB3);		//bit 3 set to 0 (red off)
// 	PORTB |= (1<<PB4);		//bit 4 set to 1 (blue on)
// 	_delay_ms(250);
// 	PORTB |= (1<<PB3);
// 	PORTB &= ~(1<<PB4);
// 	_delay_ms(250);

//attempt 2 - overflow + interrupt
// DDRB |= (1<<PB4) | (1<<PB3); //0b00011000;   //PB3 and 4 set to output with the data direction register
// // PORTB = 0x00;  // Initial state - all ports logic 0
// TCCR1B = (1<<CS10) | ~(1<<CS11) | (1<<CS12);   //page 139 setup of the clock (counter 1 in control register B)
// TCNT1 = 0;  // utilized counter is the counter 1 therefore TCNT1
// OCR1A = 1; //a OCF1A flag will be set once TCNT1 Reaches this value (page 144), here the value is the clk frequency/1 (approx every 4,16 sec)
// while (1)
// {
// 	while (TIFR1 &(1<< OCF1A) == 0);  // Interrupt requests signals are all visible in the Timer Interrupt Flag Register (TIFRn) (page 114)
// 	PORTB ^= (1<< PB4)  | (1<<PB3);	//toggle with xor
// 	TCNT1 = 0; //set back to 0 in preparation to repeat the process
// 	TIFR1 |= (1<< OCF1A);	// "the OCF0A flag can be cleared by software by writing a logical one to its I/O bit location" page 101

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL //1mhz
int main(void)
{
	DDRB |= (1<<PB3) | (1<<PB4) | (1<<PB2); //ob00111000
	
     while (1)
     {
	 PORTB ^= (1<<PB3) ; //toggle red, wait 2 sec, toggle blue, repeat
	 _delay_ms(2000);
 	 PORTB ^= (1<<PB4);
// 	_delay_ms(500);
// 		PORTB |= (1<<PB3);		 // Bit 3 set to 1 (red on)
// 		_delay_ms(250);
// 		PORTB &= ~(1<<PB3);		//bit 3 set to 0 (red off)
// 		_delay_ms(250);
// 		PORTB |= (1<<PB4);		//bit 4 set to 1 (blue on)
// 		_delay_ms(250);
// 		PORTB |= (1<<PB3);			// red on
// 		_delay_ms(250);
// 		PORTB &= ~(1<<PB4);			//blue off
// 	 	_delay_ms(250);
//  		
    }
	
	
    						

    }


