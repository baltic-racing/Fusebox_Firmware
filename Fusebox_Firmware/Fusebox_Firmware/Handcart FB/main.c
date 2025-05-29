#include "main.h"

extern struct CAN_MOB can_Fusebox0_mob;
extern struct CAN_MOB can_Fusebox1_mob;
extern struct CAN_MOB can_Fusebox2_mob;
extern struct CAN_MOB can_Fusebox3_mob;
extern struct CAN_MOB can_Fusebox4_mob;

extern struct CAN_MOB can_BMS3_mob;
extern uint8_t Fusebox0_databytes[8];



uint32_t accufan_counter=0;
uint8_t Akku_fan_on = 0;
uint8_t AKKUFAN =0;
int main(void)
{
	sys_timer_config();
	port_config();
	can_cfg();
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
			
			AIR_close = ((PINE & (1 << PE2 ))>> PE2);		// TS_ACT on PB4
			AKKUFAN = (PINE & (1 << PE5));

			PINE = (IMD_LED_light << PE0);					// IMD light on PE0

			can_rx(&can_BMS3_mob, BMS3_databytes);
			
			IMD_LED_light = (BMS3_databytes[6]<<1>>7);
			
 			Fusebox0_databytes[0]	=	0						;
			Fusebox0_databytes[1]	=	0						;	
 			Fusebox0_databytes[2]	=	0						;	
 			Fusebox0_databytes[3]	=	0						; 
			Fusebox0_databytes[4]	=	0						;
			Fusebox0_databytes[5]	=	AIR_close				;
 			Fusebox0_databytes[6]	=	0						;
			Fusebox0_databytes[7]	=	0						;
			
			can_tx(&can_Fusebox0_mob, Fusebox0_databytes);	//(0x600 --> Board Voltages)
			
			
			if(AKKUFAN && accufan_counter>10)
			{
				//(Akku_fan_on += 1 ) & 1;
				
				if(Akku_fan_on == 1 )
				{
					Akku_fan_on = 0;
					PORTB &= ~(1<<PB0);
				}
				else
				{
					Akku_fan_on = 1;
					PORTB |= (1<<PB0);
				}
				
				accufan_counter = 0;
				
			}
			
		}	//end of 10 ms cycle
		
		if(TIME_PASSED_100_MS)
		{
			time_100ms = sys_time;
			accufan_counter++;
			sys_tick_heart();
			
		}  //end of 100ms
	}  //end of while
} //end of main
//end of the world


