#ifndef FUSE_READ_OUT_H_
#define FUSE_READ_OUT_H_

#include <avr/io.h>

uint16_t Fuse_Read_Out(uint8_t fuse);

uint8_t Fuse_Byte(uint8_t FRO_Byte , uint16_t FRO);


#endif /* FUSE_READ_OUT_H_ */