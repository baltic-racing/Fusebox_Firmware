/*
 * sdc.h
 *
 *  Created on: 10.08.2026
 *      Author: jakob
 */

#ifndef INC_SDC_H_
#define INC_SDC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

extern uint16_t sdc_status;

void SDC_ReadAll(void);

#ifdef __cplusplus
}
#endif



#endif /* INC_SDC_H_ */
