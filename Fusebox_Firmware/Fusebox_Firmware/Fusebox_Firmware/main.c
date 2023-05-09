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
//#include "timer_library.h"

//#include <util/delay.h>
uint8_t R2D_databytes[8];


unsigned long long waste_cpu_time;
unsigned int loops_completed = 0;
uint16_t voltage = 0;
uint8_t heart_beat = 255;
unsigned long sys_time; //no need to write =0!!
unsigned long time_old = 0;
unsigned long time_old_100ms = 0;


uint8_t note_length;
uint8_t OCR2A_next;
uint8_t song[29];
uint8_t note_next ;

extern volatile uint8_t fan_duty;

uint8_t R2D_pressed = 0;



int main(void){
	
	//timer0_config(1000, CTC_Mode , 3, No_Mode );
	
	//can_check_free();

//	fuse_read_out();
	
	
	
	can_cfg();
//	adc_config();
	
	timer2_config();
	sys_timer_config();
	port_config(); 
//	timer1_config();
	
	


	//struct CAN_MOB can_FB_mob;//data to send  FB = fusebox, outgoing fusebox message with its 8 dataBYTES
	//can_FB_mob.mob_id = 0;
	//can_FB_mob.mob_idmask = 0;
	//can_FB_mob.mob_number = 0;
	//uint8_t FB_databytes[8];  

	
	struct CAN_MOB can_R2D_mob;
	can_R2D_mob.mob_id = 0b100000000;
	can_R2D_mob.mob_idmask = 0b11111111111;
	can_R2D_mob.mob_number = 0;
	uint8_t R2D_databytes[8];
	
//  	struct CAN_MOB mob_to_transmit;
//  	mob_to_transmit.mob_id = 0x100;
//  	mob_to_transmit.mob_idmask = 0xffff;
//  	mob_to_transmit.mob_number = 1;
//  	uint8_t mob_0_data[8];
	sei();

	while (1)
	{
		
		

	if((sys_time - time_old) > 10){  //10ms
				time_old = sys_time; //
				time_old_100ms++;// use for a longer loop later
				PORTB ^= (1<<PB3);
				
//fuse_read_out()&0xff			// input &0xff gives you the first byte (8bit) (least significant byte)
//(fuse_read_out()>>8)&0xff		//shifting 1 byte to the right gives us the next 8 bit bundle, now we've read the full 16 bit value

	//FB_databytes[0]	= fuse_read_out()&0xff		;			//  lsb
	//FB_databytes[1]	= (fuse_read_out()>>8)&0xff	;			//  msb
	//FB_databytes[2]	= SCI_read_out()			;			// fits in 8 bits
	//FB_databytes[3]	= adc_get(0)				;
	//FB_databytes[4]	= adc_get(1)				;  
	//FB_databytes[6]	= 0							;
	//FB_databytes[7]	= 0							;
		//
	//
	//can_tx(&can_FB_mob, FB_databytes);  //& is a reference operator 
	
	can_rx(&can_R2D_mob, R2D_databytes);

//	can_rx(&mob_to_transmit, mob_0_data);
	
	R2D_pressed = R2D_databytes[2];// | R2D_databytes[3];
//	R2D_pressed = mob_0_data[2];								
		if (R2D_pressed & 1){
			
			PORTB ^= (1<<PB3);
			OCR2A = song[note_next];
			
			note_length++;

			if (note_length == 2)
			{
				note_length = 0;
				note_next++;
			}
			if (note_next == 29)
			{
				note_next = 0;
			}
		}
		else{
			OCR2A = 0;
		}
	
	
	
	}
 	if (time_old_100ms >= 100){
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
	