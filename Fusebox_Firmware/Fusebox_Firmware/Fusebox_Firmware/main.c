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
extern struct CAN_MOB can_SWC0_mob;
extern uint8_t Fusebox0_databytes[8];
extern uint8_t Fusebox1_databytes[8];
extern uint8_t Fusebox2_databytes[8];
extern uint8_t Fusebox3_databytes[8];
extern uint8_t Fusebox4_databytes[8];
extern uint8_t SHR0_databytes[8];
extern uint8_t SHB0_databytes[8];
extern uint8_t DIC0_databytes[8];
extern uint8_t SWC0_databytes[8];

#define TSACT DIC0_databytes[1]
#define TSON DIC0_databytes[0]
#define APPS (uint16_t)(((SHR0_databytes[2]) | (SHR0_databytes[3] << 8))/10)
#define TSRDY ((BMS3_databytes[6]>>3) & 1)
#define APPSOK (uint8_t) SHR0_databytes[6]
#define AKKUFAN (uint8_t) SWC0_databytes[3]
#define COOLINGFAN (uint8_t) SWC0_databytes[2]

uint8_t DRV_EN = 0;
uint8_t R2D_pressed = 0;
int16_t ac_current = 0;
uint16_t current_limit = 300;	//in Ampere
uint16_t R2D_counter;
uint8_t R2D_active;
uint32_t accufan_counter=0;
uint8_t Akku_fan_on = 0;
//uint16_t adc0 = 0;
//uint16_t l_lv = 0;
//uint16_t v_NIMH = 0;
uint8_t BMS3_databytes[8];
uint8_t TS_RDY = 0;
uint8_t R2D_bit = 0;
uint8_t FRO_Byte = 0;
uint16_t FRO =0;
uint8_t Fuse_Can = 0;
uint8_t SDCI_FB = 0;

volatile uint16_t Motor_Temp;
extern volatile uint16_t fan_dc;
extern volatile uint16_t wp_dc;

uint8_t cooling_fan_offset = 0;
uint8_t fuse = 0;
int main(void)
{
	sys_timer_config();
	port_config();
	timer1_config();
	timer3_config();
	can_cfg();
	adc_config();
	CAN_Init_Messages();

	sei();

	//	SUPERLOOP STARTS HERE
	
	while (1)
	{
		if(TIME_PASSED_1_MS)
		{
			time_1ms = sys_time;
			adc_start_conversion();
		}
		
		if(TIME_PASSED_10_MS)
		{
			time_10ms = sys_time;
			

			fan_dc = 2500;
			
			can_rx(&can_SHR0_mob, SHR0_databytes);
			can_rx(&can_SHB0_mob, SHB0_databytes);
			can_rx(&can_DIC0_mob, DIC0_databytes);
			can_rx(&can_BMS3_mob, BMS3_databytes);
			can_rx(&can_SWC0_mob, SWC0_databytes);
			
			if (R2D_bit==1)
			{
				ac_current = calculate_ac_current(current_limit, APPS);
			}
			else
			{
				ac_current = 0;
			}
			
			
			uint16_t adc1 = adc_get(1); 
			uint16_t l_lv = ((20+(adc1-564.0)*0.037)*10.0); // calculated with rise of a regression line (0.037) and *10 for decimal place
			
			uint16_t adc0 = adc_get(0);
			uint16_t v_NIMH =  (adc0*4.8875); // voltage in mV
			
			PORTC = ((PORTC & 0xF0)|(fuse & 0x0F));	//PortC for Multiplexer for Fuse_Read_Out
			
			Fuse_Can = Fuse_Byte(FRO_Byte , FRO);
						 
 			Fusebox0_databytes[0]	=	v_NIMH			&0xff	;
			Fusebox0_databytes[1]	=	(v_NIMH	>>8)	&0xff	;	
 			Fusebox0_databytes[2]	=	l_lv			&0xff   ;	
 			Fusebox0_databytes[3]	=   (l_lv >>8)		&0xff   ; 
			Fusebox0_databytes[4]	=	0						;//SDCI_FB			&0xff	;
			Fusebox0_databytes[5]	=	0						;
 			Fusebox0_databytes[6]	=	Akku_fan_on		&0xff	;	//Akku_fan_on 
			Fusebox0_databytes[7]	=	Fuse_Can		&0xff	;	// für Einzelabfrage der Fuses
			
			Fusebox3_databytes[0] = (ac_current*10>> 8);
			Fusebox3_databytes[1] = ac_current*10;
			
			Fusebox4_databytes[0] = (current_limit*10 >> 8);
			Fusebox4_databytes[1] = current_limit*10;
			
			
			
			
			
			//	TS ACTIVATE PROCEDURE
			if (TSRDY == 1)
			{
				if ((TSACT == 1) && (R2D_bit == 0))// && (APPSOK == 0))
				{
					R2D_activation();
					R2D_bit = 1;
					DRV_EN = 1;
				}
				//if (APPSOK==1)
				//{
					//DRV_EN = 0;
					//R2D_bit = 0;
					//
				//}
			}
			else
			{
				R2D_bit = 0;
				DRV_EN = 0;
			}
			
			
			if(AKKUFAN == 1 && accufan_counter>10)
			{
				//(Akku_fan_on += 1 ) & 1;
				
				if (Akku_fan_on == 1 )
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
			
			if (COOLINGFAN == 1){
				PORTB &= ~(1<<PB6);
			}
			
			//Fusebox2_databytes[0] = DRV_EN;
			 
			can_tx(&can_Fusebox0_mob, Fusebox0_databytes);	//(0x600 --> Board Voltages)
			can_tx(&can_Fusebox1_mob, Fusebox1_databytes);	//(0x601 --> SDC Indicator)
			//can_tx(&can_Fusebox2_mob, Fusebox2_databytes);	//(DRV Enable)
			can_tx(&can_Fusebox3_mob, Fusebox3_databytes);	//(AC Current)
			can_tx(&can_Fusebox4_mob, Fusebox4_databytes);	//(AC Current Limit)
				
		}	//end of 10 ms cycle

		if (TIME_PASSED_100_MS)
		{
			time_100ms = sys_time;
			sys_tick_heart();
			accufan_counter++;
			
			FRO_Byte++;
			if (FRO_Byte>14)
			{
				FRO_Byte = 0;
			}
			
 			FRO = Fuse_Read_Out(fuse);
 			fuse++;
 			if (fuse>13)
 			{
	 			fuse = 0;
 			}
			
			SDCI_FB = SDCI_read_out();
			
 		}  //end of 100ms
		 
		if (TIME_PASSED_200_MS)
		{
			time_200ms = sys_time;
			 
			//
			//FRO_Byte = Fuse_Read_Out();
			//
			//
			//Fusebox1_databytes[0]	= 0;
			//Fusebox1_databytes[1]	= 0;
			//Fusebox1_databytes[2]	=	FRO_Byte & 0xFF;
			//Fusebox1_databytes[3]	=	(FRO_Byte >> 8) & 0xFF;
			//Fusebox1_databytes[4]	= 0;
			//Fusebox1_databytes[5]	= 0;
			//Fusebox1_databytes[6]	= 0;
			//Fusebox1_databytes[7]	= 0;
			//
			
		} //end of 200ms

	}  //end of while
} //end of main
//end of the world


