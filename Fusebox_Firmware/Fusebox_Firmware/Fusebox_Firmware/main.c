#include "main.h"


extern struct CAN_MOB can_Fusebox0_mob;
extern struct CAN_MOB can_Fusebox1_mob;
extern struct CAN_MOB can_Fusebox2_mob;
extern struct CAN_MOB can_Fusebox3_mob;
extern struct CAN_MOB can_Fusebox4_mob;

extern struct CAN_MOB can_SHR0_mob;
extern struct CAN_MOB can_SHB0_mob;
extern struct CAN_MOB can_DIC0_mob;
extern struct CAN_MOB can_BMS3_mob;
extern uint8_t Fusebox0_databytes[8];


int main(void)
{
	sys_timer_config();
	port_config();
	timer1_config();
	timer3_config();
	can_cfg();
	adc_config();
	CAN_Init_Messages();

	uint8_t BMS3_databytes[8];
	uint8_t AIR_close = 0;
	uint8_t IMD_LED_light = 0;
	

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
			
<<<<<<< Updated upstream
			AIR_close = ((~PINB & (1 << PB6 ))>> PB6);		// TS_ACT on PB6 
=======
			AIR_close = ((~PINB & (1 << PB6 ))>> PB6);		// TS_ACT on PB6
>>>>>>> Stashed changes
			
			PINB = (IMD_LED_light << PB4);					// IMD light on PB4

			can_rx(&can_BMS3_mob, BMS3_databytes);
			
			
			IMD_LED_light = (BMS3_databytes[6]>>7);
			
			
			
			
			
<<<<<<< Updated upstream
 			Fusebox0_databytes[0]	=	0						;
			Fusebox0_databytes[1]	=	0						;	
 			Fusebox0_databytes[2]	=	0						;	
 			Fusebox0_databytes[3]	=	0						; 
			Fusebox0_databytes[4]	=	0						;
			Fusebox0_databytes[5]	=	AIR_close				;
 			Fusebox0_databytes[6]	=	0						;
=======
			Fusebox0_databytes[0]	=	0						;
			Fusebox0_databytes[1]	=	0						;
			Fusebox0_databytes[2]	=	0						;
			Fusebox0_databytes[3]	=	0						;
			Fusebox0_databytes[4]	=	0						;
			Fusebox0_databytes[5]	=	AIR_close				;
			Fusebox0_databytes[6]	=	0						;
>>>>>>> Stashed changes
			Fusebox0_databytes[7]	=	0						;
			
			
		
			
<<<<<<< Updated upstream
		
			 
=======
			
			
			
>>>>>>> Stashed changes
			can_tx(&can_Fusebox0_mob, Fusebox0_databytes);	//(0x600 --> Board Voltages)
			
			
			
		}	//end of 10 ms cycle
		
		if (TIME_PASSED_100_MS)
		{
			time_100ms = sys_time;
			sys_tick_heart();
			
			
			
<<<<<<< Updated upstream
	
 		}  //end of 100ms
		 
=======
			
		}  //end of 100ms
		
>>>>>>> Stashed changes
		if (TIME_PASSED_200_MS)
		{
			time_200ms = sys_time;
			
<<<<<<< Updated upstream
		
			
		
=======
			
			
			
>>>>>>> Stashed changes
		} //end of 200ms

	}  //end of while
} //end of main
//end of the world


