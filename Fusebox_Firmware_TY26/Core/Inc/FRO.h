/*
 * FRO.h
 *
 *  Created on: Oct 4, 2026
 *      Author: Lilly
 */

#ifndef FRO_H_
#define FRO_H_

#include <stdint.h>

/* Liest die 14 Sicherungskanäle über den Multiplexer. */
void FRO_Init(uint32_t now_ms);
void FRO_Task(uint32_t now_ms);

/* Bit 0–13 enthält den zuletzt gelesenen Zustand jedes Kanals. */
uint16_t FRO_GetStatus(void);

#endif /* FRO_H_ */
