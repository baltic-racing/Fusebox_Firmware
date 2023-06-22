/*
 * Fusebox_Firmware.c
 *
 * Created: 13.02.2023 11:41:48
 * Author : adaam
 */ 

//IMPORTANT TO KNOW BUZZER IS A CAPACITOR, NEEDS A RESISTOR TO COMPENSATE
//DONT FORGET THE 120 OHM TERMINATION RESISTOR BETWEEN THE CAN WIRES WHEN TESTING PCBs (stehende welle vermeiden)
 

#include "adc_functions.h"
#include "fuse_read_out_config.h"
#include "Misc_Functions.h"
#include "shutdown_circuit_indicator.h"
#include "ready_to_drive_sound_config.h"
#include "canlib.h"
#include "fan_power_unit_PWM_control.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//#include "timer_library.h"
#define F_CPU 16000000

unsigned long sys_time;
unsigned long time_old = 0;
unsigned long time_old_100ms = 0;
unsigned long time_200ms = 0;
unsigned long test_timer1 = 0; //testing variables
unsigned long useless_variable = 0; //testing variables
unsigned long useless_variable_1 =0; //testing variables
int o = 0; //testing variables
uint8_t increment_flag = 0; //testing...
uint8_t increment_flag_1 = 0;
uint8_t increment_flag_2 = 0;
uint8_t increment_flag_3 = 0;

uint8_t note_length;
uint8_t OCR2A_next;
uint8_t song[10];
uint8_t note_next ;
extern volatile unsigned long r2d_length;
volatile uint8_t temperature = 0;
volatile uint8_t x = 0;

extern volatile uint8_t fan_duty;
uint8_t R2D_pressed = 0;

extern volatile unsigned char DRV_EN;
uint16_t apps = 0;
int16_t ac_current = 0;
uint16_t current_limit = 15; //in Ampere

int main(void){

sys_timer_config();
port_config();
can_cfg();
adc_config();
timer2_config();
timer1_config();
_delay_ms(50);  //temporary band aid (uC needed time between setup and arming
//fan only works for 50 ms delay between arming and cfg (look up the requirements later
//i pretty much got this 50ms though trial and error

struct CAN_MOB can_Fusebox0_mob;
can_Fusebox0_mob.mob_id = 0x600;
can_Fusebox0_mob.mob_idmask = 0; //sent
can_Fusebox0_mob.mob_number = 1;
uint8_t Fusebox0_databytes[8];

struct CAN_MOB can_Fusebox1_mob;
can_Fusebox0_mob.mob_id = 0x601;
can_Fusebox0_mob.mob_idmask = 0; //sent
can_Fusebox0_mob.mob_number = 2;
uint8_t Fusebox1_databytes[8];

//Serial Numbers of Inverters, 0x1F for Broadcasting
uint8_t INV0_SN = 0x1F; 
uint8_t INV1_SN = 0x1F;

struct CAN_MOB can_Fusebox2_mob; //to INV0 (Drive Enable)
can_Fusebox0_mob.mob_id = (0x0C << 5) + (INV0_SN);
can_Fusebox0_mob.mob_idmask = 0; //sent
can_Fusebox0_mob.mob_number = 3;
uint8_t Fusebox2_databytes[8] = {0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct CAN_MOB can_Fusebox3_mob; //to INV1 (Drive Enable)
can_Fusebox0_mob.mob_id = (0x0C << 5) + (INV1_SN);
can_Fusebox0_mob.mob_idmask = 0; //sent
can_Fusebox0_mob.mob_number = 4;
uint8_t Fusebox3_databytes[8] = {0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct CAN_MOB can_Fusebox4_mob; //to INV0 (AC Peak Current)
can_Fusebox0_mob.mob_id = (0x01 << 5) + (INV0_SN);
can_Fusebox0_mob.mob_idmask = 0; //sent
can_Fusebox0_mob.mob_number = 5;
uint8_t Fusebox4_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct CAN_MOB can_Fusebox5_mob; //to INV1 (AC Peak Current)
can_Fusebox0_mob.mob_id = (0x01 << 5) + (INV1_SN);
can_Fusebox0_mob.mob_idmask = 0; //sent
can_Fusebox0_mob.mob_number = 6;
uint8_t Fusebox5_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	
struct CAN_MOB can_Fusebox6_mob; //to INV0 (AC Peak Current Limit)
can_Fusebox0_mob.mob_id = (0x08 << 5) + (INV0_SN);
can_Fusebox0_mob.mob_idmask = 0; //sent
can_Fusebox0_mob.mob_number = 7;
uint8_t Fusebox6_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct CAN_MOB can_Fusebox7_mob; //to INV1 (AC Peak Current Limit)
can_Fusebox0_mob.mob_id = (0x08 << 5) + (INV1_SN);
can_Fusebox0_mob.mob_idmask = 0; //sent
can_Fusebox0_mob.mob_number = 8;
uint8_t Fusebox7_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct CAN_MOB can_SHR0_mob;
can_SHR0_mob.mob_id = 0x400;
can_SHR0_mob.mob_idmask = 0b11111111111; //receive with no filer?
can_SHR0_mob.mob_number = 9;  //IDs might be wrong
uint8_t SHR0_databytes[8];

struct CAN_MOB can_SHB0_mob;
can_SHB0_mob.mob_id = 0x420;
can_SHB0_mob.mob_idmask = 0b11111111111; //receive with no filter?
can_SHB0_mob.mob_number = 10;
uint8_t SHB0_databytes[8];

struct CAN_MOB can_DIC0_mob;	
can_DIC0_mob.mob_id = 0x500;
can_DIC0_mob.mob_idmask = 0xffff;
can_DIC0_mob.mob_number = 11;
uint8_t DIC0_databytes[8];

//timer1_config();
sei();

//need a delay between cfg and arming sequence?

	//function: give freq in cfg, wait a bit, increase duty cycle to like 30%, go back to 0%, fan is armed and ready
// 	while (sys_time <= 5000){ //3s to let fan arm
// 			if ((sys_time - useless_variable) > 125){			//every XXXms increment duty up to X/63				//nesting only for testing purposes
// 				useless_variable = sys_time;					//edit: 100ms intervals up to 15 and back to 0 NEED A SEPARATE LOOP?
// 				if (fan_duty <= 60){ //from 0% to 40% in 5000ms
// 					fan_duty++;     // incremented by 1% every 125ms
// 				}
// 			}
// 	}
// 	
// 	while(sys_time > 5000 && sys_time <= 10000){   // loop for decrementing the Throttle of our fan, to finish the Arming sequence, runs only once per power up
// 		if ((sys_time - useless_variable_1) > 125){
// 			useless_variable_1 = sys_time;
// 			if (fan_duty >= 0){ //from 40% to 0 in 5000 ms
// 				fan_duty--;
// 			}
// 		}
// 	}
// 	while (/*sys_time > 0 &&*/ sys_time < 3800){
// 	//	while(sys_time < 3000){
// 		if (fan_duty == 37){
// 			increment_flag = 1;
// 		}//waiting to switch to decrementing duty% after 37% was reached
// 		if(increment_flag == 0){// use && or OR to combine both ifs =>less nesting	
// 			if ((sys_time - useless_variable) > 50){//50ms steps until throttle 60%
// 				useless_variable = sys_time;
// 					if (fan_duty <= 37){ //  37/63 = 60%
// 						fan_duty++;
// 					} //end of duty% incrementing loop
// 			}//end of 50 step if loop (if)
// 		} //end of if containing the incrementing condition = 0
// 		if (increment_flag == 1){
// 			if ((sys_time - useless_variable) > 50){//50ms steps until throttle 60%
// 				useless_variable = sys_time;
// 					if (fan_duty >= 0){ //  back to 0 (close to 0) duty%
// 						o = 88; //test var to see if we even get here
// 						fan_duty--;  //running from 37 to 0
// 					} //end of duty% incrementing loop
// 			}//end of 50 step if loop (if)
// 		}//end of if containing the decrementing condition = 1
// 	} //end first 3s of arming seq (while)
		
	//} //end of 6s arming seq
	
	while (sys_time < 2000){
// 		if (sys_time == 5000){
// 			increment_flag = 2;
// 		}
		if (sys_time == 1000){
			increment_flag = 1;
		}
		if(increment_flag == 0){
			fan_duty = 20;
		} //end of if containing the incrementing condition = 0
		if (increment_flag == 1){	
			fan_duty = 0;
		}//end of if containing the decrementing condition = 1
// 		if (increment_flag == 2){
// 			fan_duty = 20;
// 		}
	} //end first XXXms of arming seq (while)
	
	
	while (1){
		if(TIME_PASSED_10_MS){			// (sys_time - time_old) > 10
			time_old = sys_time; 
			time_old_100ms++;   //FIND BETTER NAME, WHY OLD??
			time_200ms++;
			test_timer1++;
			
			if (FUSES_ALL_IN){	
				fault_not_detected();																					
			}																															
			else{
				fault_detected();	
			} 
	//MOVE THESE NOTES TO THE MAIN DESCRIPTION THAT WILL COME ON TOP OF THE C FILE JUST LIKE IN THE FAN POWER UNIT 					
//fuse_read_out()&0xff;			// input &0xff gives you the first byte (8bit) (least significant byte)  
//(fuse_read_out()>>8)&0xff;		//shifting 1 byte to the right gives us the next 8 bit bundle, now we've read the full 16 bit value

			//can_rx(&can_R2D_mob, R2D_databytes);
			can_rx(&can_SHB0_mob, SHB0_databytes);
			can_rx(&can_SHR0_mob, SHR0_databytes); //receive at same freq as sender right?
			can_rx(&can_DIC0_mob, DIC0_databytes);
			
			apps = (SHR0_databytes[0]) + (SHR0_databytes[1] << 8)/2;
			
			ac_current = calculate_ac_current(current_limit, apps);
			
 			Fusebox0_databytes[0]	=	adc_get(0)&0xff			;
			Fusebox0_databytes[1]	=	(adc_get(0)>>8)&0xff	;	
 			Fusebox0_databytes[2]	=	adc_get(1)&0xff			;	
 			Fusebox0_databytes[3]	=	(adc_get(1)>>8)&0xff	; 
			Fusebox0_databytes[4]	=	0						;
			Fusebox0_databytes[5]	=	0						;
 			Fusebox0_databytes[6]	=	0						;
			Fusebox0_databytes[7]	=	0						;
			
			Fusebox4_databytes[0] = ac_current;
			Fusebox4_databytes[1] = (ac_current >> 8);
			Fusebox5_databytes[0] = ac_current;
			Fusebox5_databytes[1] = (ac_current >> 8);
			Fusebox6_databytes[0] = current_limit;
			Fusebox6_databytes[1] = (current_limit >> 8);
			Fusebox7_databytes[0] = (current_limit * 10);
			Fusebox7_databytes[1] = ((current_limit * 10) >> 8);
			
			tractive_system_activate(DIC0_databytes);
 			
			can_tx(&can_Fusebox0_mob, Fusebox0_databytes);
			can_tx(&can_Fusebox1_mob, Fusebox1_databytes);
			can_tx(&can_Fusebox2_mob, Fusebox2_databytes); 
			can_tx(&can_Fusebox3_mob, Fusebox3_databytes); 
			can_tx(&can_Fusebox4_mob, Fusebox4_databytes); 
			can_tx(&can_Fusebox5_mob, Fusebox5_databytes);  
			can_tx(&can_Fusebox6_mob, Fusebox6_databytes);
			can_tx(&can_Fusebox7_mob, Fusebox7_databytes);
			
		//	R2D_pressed = R2D_databytes[2];
											// define CAR_IS_READY_TO_DRIVE [combines the 3 conditions]
			if ((fuse_read_out() & 0xFFF) < 0xFFF){  //debugging purposes fuse acts as my switch, NO MACRO NOW THE 3 CONDITIONS COME HERE: READY TO DRIVE, POWER ON and BUTTON PRESSED?
 					START_TIMER_2; 				
			}  

				//define SOUND_STILL_GOING? r2dl < xxx  // <= make that macro and a function that caclulates the time or soemthing, input time in seconds (1-3s) and it will calculate the value for the condition 2,5 seconds = 23000 or something (need to measure it better)
			if (r2d_length < 23000/*<noise_length (change r2dlength to something like r2d_ticks*/){ // under 3 seconds (tested with a stopwatch) as long as the button is not held longer than a singular press => will lead into a 2nd cycle starting 
									
				note_length++;

 				if (note_length == 5){
				note_length = 0;
 				note_next++;
				}
 				if (note_next == 10){
 				note_next = 0;
 				}	
			}	
			if (r2d_length >= 23000){   //turn into an else{}
				TCCR2A &= ~(1<<CS22);
				r2d_length = 0;
				note_next = 0;
			}
	
		}	//end of 10 ms cycle
	
		if (/*time_old_100ms >= 100*/TIME_PASSED_100_MS){ //100 ms
 			time_old_100ms = 0;
 			sys_tick_heart();  //remove the sys_, tick_heart obvious by itself
 			int8_t x = 25; //test code, x = SHB_databytes[temp we need];
 			
			// if (increment_flag_2 == 0){
			 
			 
			// for (int8_t x = 5; x < 40; x++){  //testing the range of values to alter the duty%
 				//int16_t CAN_temperature = x; //from can
 				uint8_t temperature = x;//(uint8_t) CAN_temperature;
 			//	_delay_ms(8);   //use sys timer later
 			//	fan_power_unit_PWM_control(temperature, fan_duty); 	
			 fan_duty = (temperature*63)/100;
			// if (x == 20){
			//	 increment_flag_2 = 1;
			// }
			 
 			//} //end of for
		
			// }
			 
 		}  //end of 100ms
		if (time_200ms >= 20){
			time_200ms = 0;
			
			Fusebox1_databytes[0]	=	SCI_read_out()			;
			Fusebox1_databytes[1]	= 0;
			Fusebox1_databytes[2]	=	fuse_read_out()&0xff		;
			Fusebox1_databytes[3]	=	(fuse_read_out()>>8)&0xff	;
			Fusebox1_databytes[4]	= 0;
			Fusebox1_databytes[5]	= 0;
			Fusebox1_databytes[6]	= 0;
			Fusebox1_databytes[7]	= 0;
			
			can_tx(&can_Fusebox1_mob, Fusebox1_databytes);
		} //end of 200ms
// 		if (test_timer1 >= 3000){
// 			test_timer1 = 0;
// 			OCR1A = 64;
// 		}
	}  //end of while
} //end of main
//end of the world


