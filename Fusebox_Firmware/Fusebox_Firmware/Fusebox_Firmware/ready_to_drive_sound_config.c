/*
 * ready_to_drive_sound_config.c
 *
 * Created: 10.04.2023 16:54:44
 *  Author: adaam
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ready_to_drive_sound_config.h"

uint16_t note_length = 0;
uint8_t hold_note = 0;
uint8_t current_note = 0;
uint8_t OCR2A_next = 0;
uint8_t song[29] =	{160, 142, 95, 80, 80, 80, 95, 95, 95, 120, 95, 120,
					 160, 160, 142, 95, 80, 80, 80, 80, 95, 120, 160,
					 160, 160, 120, 120, 120, 120								};
// song[0] = 60;
// song[1] = 70;
// song[2] = 80;
uint8_t note_next = 0;


void timer2_config() // timer 1 needs to replace timer 0
{
	TCCR2A |= (1<<WGM21) | (1<<CS22);// | (1<<CS21) | (1<<CS20); //ctc mode 64 pre
	//TCCR0A |= (1<<COM0A1); //clear ocr0a on match
	TIMSK2 = (1<<OCIE2A);// Interrupt enabl
	OCR2A =42 ;		//	  16000000/(2*64*42) = 2976 Hz
	//sei();
		
}

void funny_function(){
	
}

ISR(TIMER2_COMP_vect){ //isr fur timer2 
	cli();
	PORTD ^= (1<<PD2);
	sei();
	/*current_note ++;
	
	if (current_note >= note_length){
		OCR2A = 70-1;
		current_note = 0;
	}*/
	/*OCR2A = song[note_next];
	
	note_length++;

	if (note_length == 1000)
	{
		note_length = 0;
		note_next++;	
	}
		if (note_next == 4)
	{
		note_next = 0;
	}
	*/
}