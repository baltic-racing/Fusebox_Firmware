/*
 * ready_to_drive_sound_config.c
 *
 * Created: 10.04.2023 16:54:44
 *  Author: adaam
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ready_to_drive_sound_config.h"

unsigned long r2d_length = 0;

uint8_t note_length = 0;
uint8_t hold_note = 0;
uint8_t current_note = 0;
uint8_t OCR2A_next = 0;
uint8_t song[10] =	{ /*30,25,30,25,30,25,30,25,30,25*/32 ,31 ,30 ,29 ,28 ,27 ,28 ,29 ,30 ,31/*30, 40, 50,40, 30, 40, 50,40,30, 40, 50,40,30, 40, 50,40,30, 40, 50,40,
	30, 40, 50,40,30, 40, 50,40*/};  /*80, 80, 80, 95, 95, 95, 120, 95, 120,
					 160, 160, 142, 95, 80, 80, 80, 80, 95, 120, 160,					//temporary, will change to a simple note progression later
					 160, 160, 120, 120, 120, 120								};*/
// song[0] = 60;
// song[1] = 70;
// song[2] = 80;
uint8_t note_next = 0;


void timer2_config() // timer 1 needs to replace timer 0   //NO NEED FOR GLOBAL CONFIG, TIMER SHOULD ONLY START WHEN THE SOUND IS REQUIRED
{
	TCCR2A |= (1<<WGM21);// | (1<<CS22);// | (1<<CS21) | (1<<CS20); //ctc mode 64 pre
	//TCCR0A |= (1<<COM0A1); //clear ocr0a on match
	TIMSK2 = (1<<OCIE2A);// Interrupt enabl
	//OCR2A =42 ;		//	  16000000/(2*64*42) = 2976 Hz
	//sei();
		
}

void buzzer_noise(){
		
	TCCR2A |= (1<<CS22); // starts timer
			
			
	OCR2A = song[note_next];
			
	note_length++;

		if (note_length == 2){
			note_length = 0;
			note_next++;
		}
		if (note_next == 10){
			note_next = 0;
		}
		
// 		else{			//stops the buzzer  hold_r2d_timer() function?
// 			TCCR2A &= ~(1<<CS22);
// 		}
}

ISR(TIMER2_COMP_vect){ //isr fur timer2 
	//cli();
	PORTD ^= (1<<PD2);
	r2d_length++;
	//OCR2A = song[note_next];
	//
	//note_length++;
//note_next++;
	//if (note_length == 2){
		//note_length = 0;
		//note_next++;
	//}
	//if (note_next == 29){
		//note_next = 0;
	//}
	//sei();
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