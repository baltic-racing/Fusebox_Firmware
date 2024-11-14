#include "CAN_DATA.h"


uint8_t Fusebox1_databytes[8];
uint8_t Fusebox0_databytes[8];
uint8_t Fusebox2_databytes[8] = {0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t Fusebox3_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t Fusebox4_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t Fusebox5_databytes[8] = {0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	
uint8_t SHR0_databytes[8];
uint8_t SHB0_databytes[8];
uint8_t DIC0_databytes[8];
uint8_t SWC0_databytes[8];

struct CAN_MOB can_Fusebox0_mob;
struct CAN_MOB can_Fusebox1_mob;
struct CAN_MOB can_Fusebox2_mob; //to INVX (Drive Enable)
struct CAN_MOB can_Fusebox3_mob; //to INVL (AC Peak Current INV0)
struct CAN_MOB can_Fusebox4_mob; //to INVR (AC Peak Current INV1)
struct CAN_MOB can_Fusebox5_mob; //to INVX (AC Peak Current limit)
struct CAN_MOB can_SHR0_mob;
struct CAN_MOB can_SHB0_mob;
struct CAN_MOB can_DIC0_mob;
struct CAN_MOB can_BMS3_mob;
struct CAN_MOB can_SWC0_mob;



void CAN_Init_Messages()
{
	can_Fusebox0_mob.mob_id = 0x600;
	can_Fusebox0_mob.mob_idmask = 0xFFFF; //sent
	can_Fusebox0_mob.mob_number = 0;

	can_Fusebox1_mob.mob_id = 0x601;
	can_Fusebox1_mob.mob_idmask = 0xFFFF; //sent
	can_Fusebox1_mob.mob_number = 1;
	

	//CAN IDs of Inverters, 0x1F for Broadcasting
	uint8_t INV0_SN = 10; //right
	uint8_t INV1_SN = 20; // left
	uint8_t INVX_SN = 0x1F; //(Broadcast)
// 
// 	can_Fusebox2_mob.mob_id = (0x24 << 5) | (INVX_SN); //ID 0x481	Drive Enable
// 	can_Fusebox2_mob.mob_idmask = 0xFFFF; //sent
// 	can_Fusebox2_mob.mob_number = 2;

	can_Fusebox3_mob.mob_id = (0x1A << 5) | (INV0_SN); // Set AC current
	can_Fusebox3_mob.mob_idmask = 0xFFFF; //sent
	can_Fusebox3_mob.mob_number = 2;

	can_Fusebox4_mob.mob_id = (0x1A << 5) | (INV1_SN);	// set AC current
	can_Fusebox4_mob.mob_idmask = 0xFFFF; //sent
	can_Fusebox4_mob.mob_number = 3;
	
	can_Fusebox5_mob.mob_id = (0x20 << 5) | (INVX_SN);	// set AC current limit 
	can_Fusebox5_mob.mob_idmask = 0xFFFF; //sent
	can_Fusebox5_mob.mob_number = 4;

	can_SHR0_mob.mob_id = 0x400;
	can_SHR0_mob.mob_idmask = 0b11111111111; //receive with no filter?
	can_SHR0_mob.mob_number = 5;  //IDs might be wrong

// 	can_SHB0_mob.mob_id = 0x420;
// 	can_SHB0_mob.mob_idmask = 0b11111111111; //receive with no filter?
// 	can_SHB0_mob.mob_number = 7;

	can_DIC0_mob.mob_id = 0x500;
	can_DIC0_mob.mob_idmask = 0xffff;
	can_DIC0_mob.mob_number = 6;

	can_BMS3_mob.mob_id = 0x200;
	can_BMS3_mob.mob_idmask = 0xffff;
	can_BMS3_mob.mob_number = 7;
	
	can_SWC0_mob.mob_id = 0x750;
	can_SWC0_mob.mob_idmask = 0xffff;
	can_SWC0_mob.mob_number = 8;
}