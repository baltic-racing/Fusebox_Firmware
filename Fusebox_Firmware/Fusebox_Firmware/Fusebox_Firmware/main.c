#include "main.h"

/*
extern struct CAN_MOB can_Fusebox0_mob;
extern struct CAN_MOB can_Fusebox1_mob;
extern struct CAN_MOB can_Fusebox2_mob;
extern struct CAN_MOB can_Fusebox3_mob;

extern struct CAN_MOB can_SHR0_mob;
extern struct CAN_MOB can_SHB0_mob;
extern struct CAN_MOB can_DIC0_mob;
extern struct CAN_MOB can_BMS3_mob;
*/

// uint8_t Fusebox1_databytes[8];

//uint8_t R2D_pressed = 0;

//extern volatile unsigned char DRV_EN;
//uint16_t apps = 0;
//int16_t ac_current = 0;
//uint16_t current_limit = 25; //in Ampere

uint16_t Motor_Temp;
extern volatile uint16_t fan_dc;

int main(void)
{
	sys_timer_config();
	port_config();
	timer1_config();
	//can_cfg();
	//adc_config();
	//CAN_Init_Messages();

	//uint8_t BMS3_databytes[8];
	//uint8_t TS_RDY = 0;

	//uint8_t R2D_bit = 0;
	uint16_t FRO_Byte = 0;

	sei();

	//	SUPERLOOP STARTS HERE
	
	while (1)
	{
		if(TIME_PASSED_1_MS)
		{
			time_1ms = sys_time;
			
		}
		
		if(TIME_PASSED_10_MS)
		{
			time_10ms = sys_time;
			

			/*
			can_rx(&can_SHR0_mob, SHR0_databytes);
			can_rx(&can_SHB0_mob, SHB0_databytes);
			can_rx(&can_DIC0_mob, DIC0_databytes);
			can_rx(&can_BMS3_mob, BMS3_databytes);
			*/
			/*
			TS_ACT = DIC0_databytes[1];
			TS_RDY = BMS3_databytes[0];
			*/
			/*
			apps = ((SHR0_databytes[0]) | (SHR0_databytes[1] << 8))/10;	//APPS values from 0 to 1000 --> /10
			*/
			/*
			ac_current = calculate_ac_current(current_limit, apps);
			*/
			/*
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
			*/
			
			//	TS ACTIVATE PROCEDURE
			
			//TS_RDY = 1;
			/*
			if (TS_RDY == 1)
			{
				if ((TS_ACT == 1) && (R2D_bit == 0))
				{
					//R2D();
					R2D_bit = 1;
					DRV_EN = 1;
				}
			}
			else
			{
				R2D_bit = 0;
				DRV_EN = 0;
			}
			*/
			/*
			Fusebox2_databytes[0] = DRV_EN;
			 
			can_tx(&can_Fusebox0_mob, Fusebox0_databytes);	//(0x600 --> Board Voltages)
			can_tx(&can_Fusebox1_mob, Fusebox1_databytes);	//(0x601 --> SDC Indicator)
			can_tx(&can_Fusebox2_mob, Fusebox2_databytes);	//(DRV Enable)
			can_tx(&can_Fusebox3_mob, Fusebox3_databytes);	//(AC Current)
			//can_tx(&can_Fusebox3_1_mob, Fusebox3_databytes);	//(AC Current)
			can_tx(&can_Fusebox4_mob, Fusebox4_databytes);	//(AC Current Limit)
			*/
			
			
			
		}	//end of 10 ms cycle
	
		if (TIME_PASSED_100_MS)
		{
			time_100ms = sys_time;
			sys_tick_heart();
			
			Motor_Temp = 60;
			
			fan_dc = FAN_PU_SET_PWM( Motor_Temp );
			
			 
 		}  //end of 100ms
		 
		if (TIME_PASSED_200_MS)
		{
			time_200ms = sys_time;
			
			/*
			FRO_Byte = Fuse_Read_Out();
			
			Fusebox1_databytes[0]	=	SDCI_read_out();
			Fusebox1_databytes[1]	= 0;
			Fusebox1_databytes[2]	=	FRO_Byte & 0xFF;
			Fusebox1_databytes[3]	=	(FRO_Byte >> 8) & 0xFF;
			Fusebox1_databytes[4]	= 0;
			Fusebox1_databytes[5]	= 0;
			Fusebox1_databytes[6]	= 0;
			Fusebox1_databytes[7]	= 0;
			*/
			
			/*
			can_tx(&can_Fusebox1_mob, Fusebox1_databytes);
			*/
		} //end of 200ms

	}  //end of while
} //end of main
//end of the world


