/*
 * fuse_read_out_config.c
 *
 * Created: 08.04.2023 19:03:01
 *  Author: adaam
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t fuse_read_out(){
	return PINE | PINA << 8;
}