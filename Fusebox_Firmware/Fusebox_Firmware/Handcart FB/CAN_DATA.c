#include "CAN_DATA.h"


uint8_t Fusebox1_databytes[8];
uint8_t Fusebox0_databytes[8];
uint8_t Fusebox2_databytes[8] = {0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t Fusebox3_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t Fusebox4_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct CAN_MOB can_Fusebox0_mob;
struct CAN_MOB can_Fusebox1_mob;
struct CAN_MOB can_BMS3_mob;

void CAN_Init_Messages()
{
	can_Fusebox0_mob.mob_id = 0x500;
	can_Fusebox0_mob.mob_idmask = 0xFFFF; //sent
	can_Fusebox0_mob.mob_number = 0;

	can_Fusebox1_mob.mob_id = 0x601;
	can_Fusebox1_mob.mob_idmask = 0xFFFF; //sent
	can_Fusebox1_mob.mob_number = 1;
	
	/*
	struct CAN_MOB can_Fusebox3_1_mob; //to INVX (AC Peak Current)
	can_Fusebox3_1_mob.mob_id = (0x1A << 5) | (INVX_SN); //ID 0x341
	can_Fusebox3_1_mob.mob_idmask = 0xFF; //sent
	can_Fusebox3_1_mob.mob_number = 4;
	uint8_t Fusebox3_1_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	*/

	

	can_BMS3_mob.mob_id = 0x200;
	can_BMS3_mob.mob_idmask = 0xffff;
	can_BMS3_mob.mob_number = 9;
}