/*
 * fuse_read_out_config.h
 *
 * Created: 08.04.2023 19:04:01
 *  Author: adaam
 */ 


#ifndef FUSE_READ_OUT_CONFIG_H_
#define FUSE_READ_OUT_CONFIG_H_

#include <avr/io.h>
#include <avr/interrupt.h>
//uint16_t fuse_read_out();

#define fuse_read_out() (uint16_t) PINE | (PINA << 8)
//1111 1111 | 0000 1111 << 8
//1111 1111 | 1111 0000 0000 = 1111 1111 1111  => 12 fuses

// A pins
#define FRO_Aim_EVO		(uint8_t) (PINA & 1)		
#define FRO_Shutdown	(uint8_t) ((PINA >> 1) & 1)	
#define FRO_Brakelight	(uint8_t) ((PINA >> 2) & 1)		
#define FRO_24V			(uint8_t) ((PINA >> 3) & 1)
//E pins
#define FRO_HV_Distri	(uint8_t) (PINE & 1)		
#define FRO_TSAL		(uint8_t) ((PINE >> 1) & 1)		
#define FRO_TSAC		(uint8_t) ((PINE >> 2) & 1)	
#define FRO_INV0		(uint8_t) ((PINE >> 3) & 1)
#define FRO_INV1		(uint8_t) ((PINE >> 4) & 1)		
#define FRO_FAN_PU_Sup	(uint8_t) ((PINE >> 5) & 1)
#define FRO_FAN_ACC_Sup	(uint8_t) ((PINE >> 6) & 1)
#define FRO_WP_Sup		(uint8_t) ((PINE >> 7) & 1)


#define FUSES_ALL_IN ((fuse_read_out() & 0xFFF) == 0xFFF)


#endif /* FUSE_READ_OUT_CONFIG_H_ */