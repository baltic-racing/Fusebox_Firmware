/*
 * sdc.c
 *
 *  Created on: 10.08.2026
 *      Author: jakob
 */

#include "sdc.h"

uint16_t sdc_status = 0;

void SDC_ReadAll(void)
{
	uint16_t status = 0;

	if (HAL_GPIO_ReadPin(SDCI_ButtDB_GPIO_Port, SDCI_ButtDB_Pin) == GPIO_PIN_SET)
	{
		status |= (1 << 15);
	}

	if (HAL_GPIO_ReadPin(SDCI_Inertia_GPIO_Port, SDCI_Inertia_Pin) == GPIO_PIN_SET)
	{
		status |= (1 << 14);
	}

	if (HAL_GPIO_ReadPin(SDCI_BOTS_GPIO_Port, SDCI_BOTS_Pin) == GPIO_PIN_SET)
	{
		status |= (1 << 13);
	}

	if (HAL_GPIO_ReadPin(SDCI_ButtL_GPIO_Port, SDCI_ButtL_Pin) == GPIO_PIN_SET)
	{
		status |= (1 << 12);
	}

	if (HAL_GPIO_ReadPin(SDCI_HV_Distri_GPIO_Port, SDCI_HV_Distri_Pin) == GPIO_PIN_SET)
	{
		status |= (1 << 11);
	}

	if (HAL_GPIO_ReadPin(SDCI_INV1_GPIO_Port, SDCI_INV1_Pin) == GPIO_PIN_SET)
	{
		status |= (1 << 10);
	}

	if (HAL_GPIO_ReadPin(SDCI_INV0_GPIO_Port, SDCI_INV0_Pin) == GPIO_PIN_SET)
	{
		status |= (1 << 9);
	}

	if (HAL_GPIO_ReadPin(SDCI_TSAC_GPIO_Port, SDCI_TSAC_Pin) == GPIO_PIN_SET)
	{
		status |= (1 << 8);
	}

	if (HAL_GPIO_ReadPin(SDCI_ButtR_GPIO_Port, SDCI_ButtR_Pin) == GPIO_PIN_SET)
	{
		status |= (1 << 7);
	}

	if (HAL_GPIO_ReadPin(SDCI_TSMS_GPIO_Port, SDCI_TSMS_Pin) == GPIO_PIN_SET)
	{
		status |= (1 << 6);
	}

	sdc_status = status;
}
