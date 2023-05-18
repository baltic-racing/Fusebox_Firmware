/*
 * Fusebox_Firmware.c
 *
 * Created: 13.02.2023 11:41:48
 * Author : adaam
 */ 

//IMPORTANT TO KNOW BUZZER IS A CAPACITOR, NEEDS A RESISTOR TO COMPENSATE
// 220 OHM RESISTOR BETWEEN THE CAN WIRES( stehende welle vermeiden)
 

#include "adc_functions.h"
#include "fuse_read_out_config.h"
#include "Misc_Functions.h"
#include "shutdown_circuit_indicator.h"
#include "ready_to_drive_sound_config.h"
#include "canlib.h"
#include "fan_power_unit_PWM_control.h"
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "timer_library.h"
//#include <util/delay.h>

unsigned long sys_time;
unsigned long time_old = 0;
unsigned long time_old_100ms = 0;

uint8_t note_length;
uint8_t OCR2A_next;
uint8_t song[10];
uint8_t note_next ;
extern volatile unsigned long r2d_length;

extern volatile uint8_t fan_duty;
uint8_t R2D_pressed = 0;

int main(void){
sys_timer_config();
port_config();
can_cfg();
adc_config();
timer2_config();
timer1_config();
	
struct CAN_MOB can_FB_mob;//data to send  FB = fusebox, outgoing fusebox message with its 8 dataBYTES
can_FB_mob.mob_id = 0;
can_FB_mob.mob_idmask = 0;
can_FB_mob.mob_number = 0;
uint8_t FB_databytes[8];  

struct CAN_MOB can_R2D_mob;
can_R2D_mob.mob_id = 0b100000000;
can_R2D_mob.mob_idmask = 0b11111111111;
can_R2D_mob.mob_number = 0;
uint8_t R2D_databytes[8];
	
sei();
	
	while (1){
		if(/*(sys_time - time_old) > 10*/TIME_PASSED_10_MS){  //10ms  //define 10_MS_PASSED ((sys_time - time_old) > 10)
			time_old = sys_time; 
			time_old_100ms++;   //FIND BETTER NAME, WHY OLD??
// 		if((sys_time - sys_time_old) >= 1){
// 			sys_time_old = sys_time;   //MAYBE USE THIS AS FIRST TIMER AND THE BUILD THE 10 and 100 ONES ON TOP OF IT?
// 			time_X_ms++;
// 		}
// after this add any timers time_10_ms, time_20_ms ...
			if (FUSES_ALL_IN){ //fuses in,   0b0000111111111111  	
				fault_not_detected();																					
			}																															
			else{
				fault_detected();	
			} 
						
//fuse_read_out()&0xff;			// input &0xff gives you the first byte (8bit) (least significant byte)
//(fuse_read_out()>>8)&0xff;		//shifting 1 byte to the right gives us the next 8 bit bundle, now we've read the full 16 bit value

 			FB_databytes[0]	= fuse_read_out()&0xff		;			//  lsb  //define FUSES_LEAST_SIGNIFICANT_BITS
			FB_databytes[1]	= (fuse_read_out()>>8)&0xff	;			//  msb		//define FUSES_MOST_SIGNIFICANT_BITS
 			FB_databytes[2]	= SCI_read_out()			;			// fits in 8 bits  //MAYBE NO DEFINE MACROS NEEDED?
 			FB_databytes[3]	= /*adc_get(0)*/ adc_get(0)&0xff;//this is more than 8 bit (around 575) 
			FB_databytes[4]	= /*adc_get(1)*/ (adc_get(0)>>8)&0xff;  //this is more than 8 bit (around 770) both estimates for 21.0V supply ONLY
			FB_databytes[5] = adc_get(1)&0xff			;
 			FB_databytes[6]	= (adc_get(1)>>8)&0xff		;
			FB_databytes[7]	= 0							;

 			can_tx(&can_FB_mob, FB_databytes);  //& is a reference operator 
			can_rx(&can_R2D_mob, R2D_databytes);
		
			R2D_pressed = R2D_databytes[2];// | R2D_databytes[3];
	
			if ((fuse_read_out() & 0xFFF) < 0xFFF){  //debugging purposes fuse acts as my switch, NO MACRO NOW THE 3 CONDITIONS COME HERE: READY TO DRIVE, POWER ON and BUTTON PRESSED?
 					START_TIMER_2; /*TCCR2A |= (1<<CS22);*/ // starts timer //use defines to just have a START TIMER thingy => no commenting needed						
			}    //define START_TIMER_2

	
			if (r2d_length < 23000){ // under 3 seconds as long as the button is not held longer than a singular press => will lead into a 2nd cycle starting 
									//setting the length to 16000 leads to a ~2 sec long sound  (tested with a stopwatch)
				/*OCR2A = song[note_next];*/
				note_length++;
						//move to ISR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
						// to avoid timing issues!!!!!!!!!!!!!!!!!!!!!!!!!!
						//as of now length is variable and will decrease with decrementing OCR1A values
						//[SOLVED] moved increments to ISR like a normal person 
 				if (note_length == 5){
				note_length = 0;
 				note_next++;
				}
 				if (note_next == 10){
 				note_next = 0;
 				}	
			}	
			if (r2d_length >= 23000){
				TCCR2A &= ~(1<<CS22);
				r2d_length = 0;
				note_next = 0;
			}
	
		}	//end of 10 ms cycle
	
		if (/*time_old_100ms >= 100*/TIME_PASSED_100_MS){ //100 ms
 			time_old_100ms = 0;
 			sys_tick_heart();
 			int16_t x = 50;
 			//for (x = 5; x < 90; x++){  //testing the range of values to alter the duty%
 				int16_t CAN_temperature = x; //from can
 				uint8_t T = (uint8_t) CAN_temperature;
 				//_delay_ms(1);   //use sys timer later
 				fan_power_unit_PWM_control(T, fan_duty);	
 			//} //end of for
 		}  //end of 100ms
	}  //end of while
} //end of main
//end of the world