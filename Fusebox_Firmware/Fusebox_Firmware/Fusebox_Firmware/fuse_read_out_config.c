/*
 * fuse_read_out_config.c
 *
 * Created: 08.04.2023 19:03:01
 *  Author: adaam
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t Fuse_Read_Out(char mux_select)
{
	PORTC = mux_select;
	return PING1;
}