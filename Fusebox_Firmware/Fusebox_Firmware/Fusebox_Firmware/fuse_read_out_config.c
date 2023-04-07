#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t	FRO_Aim_EVO	 	=	0;
uint8_t	FRO_Shutdown 	=	0;
uint8_t	FRO_Brakelight	=	0; 
uint8_t	FRO_24V 		=	0;
uint8_t	FRO_HV_Distri 	=	0;
uint8_t	FRO_TSAL 		=	0;
uint8_t	FRO_TSAC 		=	0;
uint8_t	FRO_INV0 		=	0;
uint8_t	FRO_INV1 		=	0;
uint8_t	FRO_FAN_PU_Sup 	=	0;
uint8_t	FRO_FAN_ACC_Sup =	0;
uint8_t	FRO_WP_Sup		=	0;


uint16_t fuse_read_out(){
	//shifting bits so  that an input in the register is always gonna be read as 1 (1 means a Fuse is in, 0 means a fuse is out), otherwise a Fuse 0b00000010 is a decimal 2
																												// with the  shit operation 0b00000010>>1 is a decimal 1 (0b00000001)
	FRO_Aim_EVO			=	(PINA & 0b00000001); //no need to shift
	FRO_Shutdown		=	(PINA & 0b00000010)>>1;  //FRO_Shutdown at PA1, 1st bit of that register, therefore we shift the 1st bit to the 0th bit
	FRO_Brakelight		=	(PINA & 0b00000100)>>2;
	FRO_24V				=	(PINA & 0b00001000)>>3;
	
	FRO_HV_Distri		=	(PINE & 0b00000001);
	FRO_TSAL			=	(PINE & 0b00000010)>>1;
	FRO_TSAC			=	(PINE & 0b00000100)>>2;
	FRO_INV0			=	(PINE & 0b00001000)>>3;
	FRO_INV1			=	(PINE & 0b00010000)>>4;
	FRO_FAN_PU_Sup		=	(PINE & 0b00100000)>>5;
	FRO_FAN_ACC_Sup		=	(PINE & 0b01000000)>>6;
	FRO_WP_Sup			=	(PINE & 0b10000000)>>7;
	
//code that sends the pin states using CAN comes here	

}