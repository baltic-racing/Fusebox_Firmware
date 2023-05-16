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





uint8_t heart_beat = 255;
unsigned long sys_time;
unsigned long time_old = 0;
unsigned long time_old_20 = 0;
unsigned long time_old_100ms = 0;

uint8_t note_length;
uint8_t OCR2A_next;
uint8_t song[10];
uint8_t note_next ;
extern volatile unsigned long r2d_length;

extern volatile uint8_t fan_duty;
uint8_t R2D_pressed = 0;
//extern uint8_t FRO_TSAC;

int main(void){
	
	//timer0_config(1000, CTC_Mode , 3, No_Mode );
	
	port_config();
	//fuse_read_out();
	can_cfg();
	adc_config();
	timer2_config();
	sys_timer_config();
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
 		
		
		

	if((sys_time - time_old) > 10){  //10ms
				time_old = sys_time; 
				time_old_100ms++;
// 				if((sys_time - sys_time_old) >= 1){
// 					sys_time_old = sys_time;
// 					time_X_ms++;
// 				}
// after this add any timers time_10_ms, time_20_ms ...
				
				
			
					
				//fuse_read_out(); // Fuse_States updates only once for some reason, taking out a fuse makes the fault go on
				//but putting it back in doesn't turn it off, need a loop within while(0)? need some way to make it update
				//its values with every 10 ms loop completed => a for loop in the FRO function to fill it out manually, array needed
				//SOLVED by deploying the function directly into the if statement and declaring Fuse_States locally in the function
				// a global declaration inside fuse_read_out_config.c prevented Fuse_States from being updated 
				if ((fuse_read_out() & 0b111111111111) == 0b111111111111){ //fuses in,   0b0000111111111111
					
					fault_not_detected();																									
				}																															
	/*else*/	if((fuse_read_out() & 0b111111111111) < 0b111111111111){						//at least 1 fuse out for example 0000 1111 0111 1111
					fault_detected();
					
				} 
				
	//INFO		
//fuse_read_out()&0xff;			// input &0xff gives you the first byte (8bit) (least significant byte)
//(fuse_read_out()>>8)&0xff;		//shifting 1 byte to the right gives us the next 8 bit bundle, now we've read the full 16 bit value

 	FB_databytes[0]	= fuse_read_out()&0xff		;			//  lsb
 	FB_databytes[1]	= (fuse_read_out()>>8)&0xff	;			//  msb
 	FB_databytes[2]	= SCI_read_out()			;			// fits in 8 bits
 	FB_databytes[3]	= adc_get(0)				;
	FB_databytes[4]	= adc_get(1)				;  
 	FB_databytes[6]	= 0							;
 	FB_databytes[7]	= 0							;


 	can_tx(&can_FB_mob, FB_databytes);  //& is a reference operator 
	
	can_rx(&can_R2D_mob, R2D_databytes);


	
	R2D_pressed = R2D_databytes[2];// | R2D_databytes[3];
//					//has to ring for 3s upon fulfilling the if-else condition  => nested interrupts? need interrupt to toggle the PD2
			//if ((fuse_read_out() & 0b111111111111) < 0b111111111111){
					//
					//
				//TCCR2A |= (1<<CS22); // starts timer
				//
				//OCR2A = song[note_next];
				//
				//note_length++;
//
				//if (note_length == 2){
					//note_length = 0;
					//note_next++;
				//}
				//if (note_next == 29){
					//note_next = 0;
				//}
			//}
  			//
			//else{			//stops the buzzer timer
  				//TCCR2A &= ~(1<<CS22);
  			//}	
	
			  
	
	
	
	
		
		if ((fuse_read_out() & 0b111111111111) < 0b111111111111) {  //debugging purposes fuse acts as my switch
			//r2d_length = 0;
			
		//	if (r2d_length < 100){
				//buzzer_noise();
// 						
 				TCCR2A |= (1<<CS22); // starts timer
// 						
// 			//	OCR2A = song[note_next];
// 						
// 				note_length++;
// 						
//  					if (note_length == 2){
// 					note_length = 0;
//  					note_next++;
//  					}
//  						if (note_next == 29){
//  						note_next = 0;
//  						
//  						}
						
								
			//}
			
			}
			
		if (r2d_length < 16000){ // under 3 seconds as long as the button is not held longer than a singular press => will lead into a 2nd cycle starting 
								//setting the length to 16000 leads to a ~2 sec long sound  (tested with a stopwatch)
			OCR2A = song[note_next];
						
				note_length++;
						//move to ISR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
						// to avoid timing issues!!!!!!!!!!!!!!!!!!!!!!!!!!
						//as of now length is variable and will decrease with decrementing OCR1A values 
 					if (note_length == 5){
					note_length = 0;
 					note_next++;
 					}
 						if (note_next == 10){
 						note_next = 0;
 						
 						}	
		}	
		if (r2d_length >= 16000){
							TCCR2A &= ~(1<<CS22);
							r2d_length = 0;
							note_next = 0;
						}
	
	
	}//end of 10 ms cycle
	
	
 	if (time_old_100ms >= 100){ //100 ms
 	time_old_100ms = 0;
 		sys_tick_heart();
 		int16_t x = 50;
		 
 		
 		//for (x = 5; x < 90; x++)  //testing the range of values to alter the duty%
 		//{
 			int16_t CAN_temperature = x; //from can
 			uint8_t T = (uint8_t) CAN_temperature;
 			//_delay_ms(1);   //use sys timer later
 			fan_power_unit_PWM_control(T, fan_duty);
 			
 			
 		//}
 		
 		
 		
 	}
	}
}
	