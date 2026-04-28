/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_RD_Pin GPIO_PIN_2
#define LED_RD_GPIO_Port GPIOE
#define MUX_S3_Pin GPIO_PIN_3
#define MUX_S3_GPIO_Port GPIOE
#define MUX_S2_Pin GPIO_PIN_4
#define MUX_S2_GPIO_Port GPIOE
#define MUX_S1_Pin GPIO_PIN_5
#define MUX_S1_GPIO_Port GPIOE
#define MUX_S0_Pin GPIO_PIN_6
#define MUX_S0_GPIO_Port GPIOE
#define Reset_Radiator_Pin GPIO_PIN_13
#define Reset_Radiator_GPIO_Port GPIOC
#define Reset_WP_Pin GPIO_PIN_14
#define Reset_WP_GPIO_Port GPIOC
#define Reset_MAB_Pin GPIO_PIN_15
#define Reset_MAB_GPIO_Port GPIOC
#define MAB_SW_Pin GPIO_PIN_9
#define MAB_SW_GPIO_Port GPIOF
#define CurrentSense_MAB_Pin GPIO_PIN_0
#define CurrentSense_MAB_GPIO_Port GPIOC
#define CurrentSense_GP_Pin GPIO_PIN_1
#define CurrentSense_GP_GPIO_Port GPIOC
#define BAT_Sense_Pin GPIO_PIN_0
#define BAT_Sense_GPIO_Port GPIOA
#define Board_Voltage_Pin GPIO_PIN_1
#define Board_Voltage_GPIO_Port GPIOA
#define CurrentSense_Radiator_Pin GPIO_PIN_2
#define CurrentSense_Radiator_GPIO_Port GPIOA
#define CurrentSense_WP_Pin GPIO_PIN_3
#define CurrentSense_WP_GPIO_Port GPIOA
#define SDCI_ButtL_Pin GPIO_PIN_1
#define SDCI_ButtL_GPIO_Port GPIOB
#define SDCI_ButtDB_Pin GPIO_PIN_2
#define SDCI_ButtDB_GPIO_Port GPIOB
#define SDCI_ButtR_Pin GPIO_PIN_7
#define SDCI_ButtR_GPIO_Port GPIOE
#define SDCI_TSAC_Pin GPIO_PIN_8
#define SDCI_TSAC_GPIO_Port GPIOE
#define SDCI_INV0_Pin GPIO_PIN_9
#define SDCI_INV0_GPIO_Port GPIOE
#define SDCI_INV1_Pin GPIO_PIN_13
#define SDCI_INV1_GPIO_Port GPIOE
#define SDCI_Inertia_Pin GPIO_PIN_11
#define SDCI_Inertia_GPIO_Port GPIOB
#define SDCI_TSMS_Pin GPIO_PIN_13
#define SDCI_TSMS_GPIO_Port GPIOB
#define SDCI_HV_Distri_Pin GPIO_PIN_10
#define SDCI_HV_Distri_GPIO_Port GPIOD
#define SDCI_BOTS_Pin GPIO_PIN_11
#define SDCI_BOTS_GPIO_Port GPIOD
#define WP_SW_Pin GPIO_PIN_0
#define WP_SW_GPIO_Port GPIOD
#define FAN_Radiator_SW_Pin GPIO_PIN_1
#define FAN_Radiator_SW_GPIO_Port GPIOD
#define FAN_TSAC_SW_Pin GPIO_PIN_2
#define FAN_TSAC_SW_GPIO_Port GPIOD
#define WP_CTRL_Pin GPIO_PIN_3
#define WP_CTRL_GPIO_Port GPIOD
#define FAN_Radiator_CTRL_Pin GPIO_PIN_4
#define FAN_Radiator_CTRL_GPIO_Port GPIOD
#define FAN_TSAC_CTRL_Pin GPIO_PIN_5
#define FAN_TSAC_CTRL_GPIO_Port GPIOD
#define GP_SW_Pin GPIO_PIN_6
#define GP_SW_GPIO_Port GPIOD
#define Reset_GP_Pin GPIO_PIN_7
#define Reset_GP_GPIO_Port GPIOD
#define FRO_out_Pin GPIO_PIN_9
#define FRO_out_GPIO_Port GPIOB
#define LED_GN_Pin GPIO_PIN_0
#define LED_GN_GPIO_Port GPIOE
#define LED_BL_Pin GPIO_PIN_1
#define LED_BL_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
