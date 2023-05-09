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

//uint16_t Fuse_States = 0;


uint16_t fuse_read_out(){
	//shifting bits so  that an input in the register is always gonna be read as 1 (1 means a Fuse is in, 0 means a fuse is out), otherwise a Fuse 0b00000010 is a decimal 2
																												// with the  shit operation 0b00000010>>1 is a decimal 1 (0b00000001)
	FRO_Aim_EVO			=	(PINA & 0b00000001); //no need to shift 
	FRO_Shutdown		=	(PINA & 0b00000010)>>1;  //FRO_Shutdown at PA1, 1st bit of that register, therefore we shift the 1st bit to the 0th bit
	FRO_Brakelight		=	(PINA & 0b00000100)>>2;  //alternative way of writing this is PINA & (1<<PB2), meaning it reads out the state of the register at the bit of PIN 2 (2nd bit) (the bit still is not shifted in this form => (PINA & (1<<PB2))>>2)
	FRO_24V				=	(PINA & 0b00001000)>>3;
	
	FRO_HV_Distri		=	(PINE & 0b00000001);
	FRO_TSAL			=	(PINE & 0b00000010)>>1;
	FRO_TSAC			=	(PINE & 0b00000100)>>2;
	FRO_INV0			=	(PINE & 0b00001000)>>3;
	FRO_INV1			=	(PINE & 0b00010000)>>4;
	FRO_FAN_PU_Sup		=	(PINE & 0b00100000)>>5;
	FRO_FAN_ACC_Sup		=	(PINE & 0b01000000)>>6;
	FRO_WP_Sup			=	(PINE & 0b10000000)>>7;
	
//code that sends the pin states using CAN comes here? just throw all the data into an Integer that will later be sent using CAN
uint16_t Fuse_States = 0;

 /* set bits of this integer to correspond with our 11 fuses*/
Fuse_States |= (FRO_Aim_EVO) | (FRO_Shutdown<<1) | (FRO_Brakelight<<2/*>>0b0000000000000010*/) | (FRO_24V<<3) | (FRO_HV_Distri<<4) | (FRO_TSAL<<5) | (FRO_TSAC<<6) | (FRO_INV0<<7) | (FRO_INV1<<8) | (FRO_FAN_PU_Sup<<9) | (FRO_FAN_ACC_Sup<<10) | (FRO_WP_Sup<<11);

/* all fuses being a logical 1 (fuse is IN) give us the following value : 0b0000011111111111 = 11d , because we shifted fuse bits in the read function, we can just 
assign those 1s to any bit within our 16 bit integer, just like we do with registers*/
return Fuse_States;

}