#include "Fuse_Read_Out.h"



uint16_t readout = 0;

uint8_t Fuse_to_Can = 0;

uint16_t Fuse_Read_Out(uint8_t fuse)
{
		if (PING & (1<<1))
			{
				readout |= (1<<fuse);
			}
		else 
			{
				readout &= ~(1 << fuse);
			}
	readout &= 0x3FFF;
		
	return readout;
}
uint8_t Fuse_Byte(uint8_t FRO_Byte , uint16_t FRO)	// um jede Fuse einzeln zu senden  // xx0 -> Fuse tripped, xx1 -> fuse not tripped, xx -> no. of fuse 
{
	Fuse_to_Can = 0; 
	Fuse_to_Can = ((FRO_Byte*10) | ((FRO >> FRO_Byte) & 1));
 
	return Fuse_to_Can;
}