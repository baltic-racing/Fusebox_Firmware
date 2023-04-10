/*
 * shutdown_circuit_indicator.c
 *
 * Created: 10.04.2023 15:34:19
 *  Author: adaam
 */ 
 #include <avr/io.h>
 #include <avr/interrupt.h>
 
 uint8_t	SCI_TSMS_5V			=	0;
 uint8_t	SCI_INV0_5V			=	0;
 uint8_t	SCI_TSAC_5V			=	0;
 uint8_t	SCI_SDB_Left_5V		=	0;
 uint8_t	SCI_HV_Distri_5V	=	0;
 uint8_t	SCI_SDB_Right_5V	=	0;
 uint8_t	SCI_INV1_5V			=	0;
 
uint8_t /* no need for 16?*/ SCI_read_out(){
	SCI_TSMS_5V			=	(PINA & 00000001);
	SCI_INV0_5V			=	(PINA & 00000010)>>1;
	SCI_TSAC_5V			=	(PINA & 00000100)>>2;
	SCI_SDB_Left_5V		=	(PINA & 00001000)>>3;
	SCI_HV_Distri_5V	=	(PINA & 00010000)>>4;
	SCI_SDB_Right_5V	=	(PINA & 00100000)>>5;
	SCI_INV1_5V			=	(PINA & 01000000)>>6;
	
	
	//can library?
}