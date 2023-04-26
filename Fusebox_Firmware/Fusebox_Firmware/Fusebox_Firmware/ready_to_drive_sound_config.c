/*
 * ready_to_drive_sound_config.c
 *
 * Created: 10.04.2023 16:54:44
 *  Author: adaam
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ready_to_drive_sound_config.h"

void timer2_config() // timer 1 needs to replace timer 0
{
	TCCR2A |= (1<<WGM21) | (1<<CS22);// | (1<<CS21) | (1<<CS20); //ctc mode 64 pre
	//TCCR0A |= (1<<COM0A1); //clear ocr0a on match
	TIMSK2 = (1<<OCIE2A);// Interrupt enabl
	OCR2A =42-1 ;		//	  16000000/(2*64*42) = 2976 Hz
	//sei();	
}

ISR(TIMER2_COMP_vect){ //isr fur timer2 
	cli();
	PORTD ^= (1<<PD2);
	sei();
}