/*
 * ready_to_drive_sound_config.c
 *
 * Created: 10.04.2023 16:54:44
 *  Author: adaam
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

void timer0_config() // timer 1 needs to replace timer 0
{
	TCCR0A |= (1<<WGM01) | (1<<CS01) | (1<<CS00); //ctc mode 64 pre
	//TCCR0A |= (1<<COM0A1); //clear ocr0a on match
	TIMSK0 = (1<<OCIE0A);// Interrupt enable???
	OCR0A =42 ;		//	  16000000/(2*64*42) = 2976 Hz
	//DDRD |= (1 << PD3); //Set PD3 as an output (done in misc)
	sei();

	
}

ISR(TIMER0_COMP_vect){ //isr fur timer0 NEEDS TO BE CHANGED TO TIMER 1, MULTIPLE COUNTERS!!!!!!
	PORTB = (1<<PB3);
	