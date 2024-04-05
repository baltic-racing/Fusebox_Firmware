#include "Fuse_Read_Out.h"

uint16_t Fuse_Read_Out()
{
	// KOMMENTAR LÖSCHEN WENN FUNKTION ÜBERPRÜFT WURDE !!!
	uint16_t FRO = 0;
	
	for (uint8_t i = 0; i < 14; i++)
	{
		PORTC = i;
		FRO += (PING1 << i);
	}

	return FRO;
}