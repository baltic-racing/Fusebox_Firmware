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

unsigned long sys_time;
unsigned long time_old = 0;
unsigned long time_old_100ms = 0;
unsigned long time_200ms = 0;

uint8_t R2D_pressed = 0;

extern volatile unsigned char DRV_EN;
uint16_t apps = 0;
int16_t ac_current = 0;
uint16_t current_limit = 25; //in Ampere

int main(void){

sys_timer_config();
port_config();
can_cfg();
adc_config();
timer2_config();

struct CAN_MOB can_Fusebox0_mob;
can_Fusebox0_mob.mob_id = 0x600;
can_Fusebox0_mob.mob_idmask = 0; //sent
can_Fusebox0_mob.mob_number = 0;
uint8_t Fusebox0_databytes[8];

struct CAN_MOB can_Fusebox1_mob;
can_Fusebox1_mob.mob_id = 0x601;
can_Fusebox1_mob.mob_idmask = 0xFF; //sent
can_Fusebox1_mob.mob_number = 1;
uint8_t Fusebox1_databytes[8];

//CAN IDs of Inverters, 0x1F for Broadcasting
uint8_t INV0_SN = 2; 
uint8_t INV1_SN = 1;
uint8_t INVX_SN = 0x1F; //(Broadcast)

struct CAN_MOB can_Fusebox2_mob; //to INVX (Drive Enable)
can_Fusebox2_mob.mob_id = (0x24 << 5) | (INVX_SN); //ID 0x481
can_Fusebox2_mob.mob_idmask = 0xFF; //sent
can_Fusebox2_mob.mob_number = 2;
uint8_t Fusebox2_databytes[8] = {0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct CAN_MOB can_Fusebox3_mob; //to INVX (AC Peak Current)
can_Fusebox3_mob.mob_id = (0x1A << 5) | (INVX_SN); //ID 0x342
can_Fusebox3_mob.mob_idmask = 0xFF; //sent
can_Fusebox3_mob.mob_number = 3;
uint8_t Fusebox3_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

/*	
struct CAN_MOB can_Fusebox3_1_mob; //to INVX (AC Peak Current)
can_Fusebox3_1_mob.mob_id = (0x1A << 5) | (INVX_SN); //ID 0x341
can_Fusebox3_1_mob.mob_idmask = 0xFF; //sent
can_Fusebox3_1_mob.mob_number = 4;
uint8_t Fusebox3_1_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
*/

struct CAN_MOB can_Fusebox4_mob; //to INVX (AC Peak Current Limit)
can_Fusebox4_mob.mob_id = (0x20 << 5) | (INVX_SN);
can_Fusebox4_mob.mob_idmask = 0xFF; //sent
can_Fusebox4_mob.mob_number = 5;
uint8_t Fusebox4_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct CAN_MOB can_SHR0_mob;
can_SHR0_mob.mob_id = 0x400;
can_SHR0_mob.mob_idmask = 0b11111111111; //receive with no filer?
can_SHR0_mob.mob_number = 6;  //IDs might be wrong
uint8_t SHR0_databytes[8];

struct CAN_MOB can_SHB0_mob;
can_SHB0_mob.mob_id = 0x420;
can_SHB0_mob.mob_idmask = 0b11111111111; //receive with no filter?
can_SHB0_mob.mob_number = 7;
uint8_t SHB0_databytes[8];

struct CAN_MOB can_DIC0_mob;	
can_DIC0_mob.mob_id = 0x500;
can_DIC0_mob.mob_idmask = 0xffff;
can_DIC0_mob.mob_number = 8;
uint8_t DIC0_databytes[8];
uint8_t TS_ACT = 0;

struct CAN_MOB can_BMS3_mob;
can_BMS3_mob.mob_id = 0x203;
can_BMS3_mob.mob_idmask = 0xffff;
can_BMS3_mob.mob_number = 9;
uint8_t BMS3_databytes[8];
uint8_t TS_RDY = 0;

uint8_t R2D_bit = 0;

sei();

//	SUPERLOOP STARTS HERE
	
	while (1){
		if(TIME_PASSED_10_MS)
			{
			time_old = sys_time; 
			time_old_100ms++; 
			time_200ms++;

			can_rx(&can_SHR0_mob, SHR0_databytes);
			can_rx(&can_SHB0_mob, SHB0_databytes);
			can_rx(&can_DIC0_mob, DIC0_databytes);
			can_rx(&can_BMS3_mob, BMS3_databytes);
			
			TS_ACT = DIC0_databytes[1];
			TS_RDY = BMS3_databytes[0];
			
			apps = ((SHR0_databytes[0]) | (SHR0_databytes[1] << 8))/10;	//APPS values from 0 to 1000 --> /10
			
			ac_current = calculate_ac_current(current_limit, apps);
			
 			Fusebox0_databytes[0]	=	adc_get(0)&0xff			;
			Fusebox0_databytes[1]	=	(adc_get(0)>>8)&0xff	;	
 			Fusebox0_databytes[2]	=	adc_get(1)&0xff			;	
 			Fusebox0_databytes[3]	=	(adc_get(1)>>8)&0xff	; 
			Fusebox0_databytes[4]	=	0						;
			Fusebox0_databytes[5]	=	0						;
 			Fusebox0_databytes[6]	=	0						;
			Fusebox0_databytes[7]	=	0						;
			
			Fusebox3_databytes[0] = (ac_current*10>> 8);
			Fusebox3_databytes[1] = ac_current*10;
			//Fusebox3_1_databytes[0] = (ac_current*10 >> 8);
			//Fusebox3_1_databytes[1] = ac_current*10;
			Fusebox4_databytes[0] = (current_limit*10 >> 8);
			Fusebox4_databytes[1] = current_limit*10;
			
			//	TS ACTIVATE PROCEDURE
			
			//TS_RDY = 1;
			
			if (TS_RDY == 1)
			{
				if ((TS_ACT == 1) && (R2D_bit == 0))
				{
					R2D();
					R2D_bit = 1;
					DRV_EN = 1;
				}
			}
			else
			{
				R2D_bit = 0;
				DRV_EN = 0;
			}
			
			Fusebox2_databytes[0] = DRV_EN;
			 
			can_tx(&can_Fusebox0_mob, Fusebox0_databytes);	//(0x600 --> Board Voltages)
			can_tx(&can_Fusebox1_mob, Fusebox1_databytes);	//(0x601 --> SDC Indicator)
			can_tx(&can_Fusebox2_mob, Fusebox2_databytes);	//(DRV Enable)
			can_tx(&can_Fusebox3_mob, Fusebox3_databytes);	//(AC Current)
			//can_tx(&can_Fusebox3_1_mob, Fusebox3_databytes);	//(AC Current)
			can_tx(&can_Fusebox4_mob, Fusebox4_databytes);	//(AC Current Limit)
	
			}	//end of 10 ms cycle
	
		if (TIME_PASSED_100_MS)
		{ //100 ms
 			time_old_100ms = 0;
 			sys_tick_heart();  //remove the sys_, tick_heart obvious by itself
			 
 		}  //end of 100ms
		if (time_200ms >= 20)
		{
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

	}  //end of while
} //end of main
//end of the world


