/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, MUX_S3_Pin|MUX_S2_Pin|MUX_S1_Pin
                          |MUX_S0_Pin|LED_GN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOE, LED_RD_Pin|LED_BL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Reset_Radiator_Pin|Reset_WP_Pin|Reset_MAB_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MAB_SW_GPIO_Port, MAB_SW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SDCI_Inertia_GPIO_Port, SDCI_Inertia_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, WP_SW_Pin|FAN_Radiator_SW_Pin|FAN_TSAC_SW_Pin|WP_CTRL_Pin
                          |FAN_Radiator_CTRL_Pin|FAN_TSAC_CTRL_Pin|GP_SW_Pin|Reset_GP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RD_Pin MUX_S3_Pin MUX_S2_Pin MUX_S1_Pin
                           MUX_S0_Pin LED_GN_Pin LED_BL_Pin */
  GPIO_InitStruct.Pin = LED_RD_Pin|MUX_S3_Pin|MUX_S2_Pin|MUX_S1_Pin
                          |MUX_S0_Pin|LED_GN_Pin|LED_BL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : Reset_Radiator_Pin Reset_WP_Pin Reset_MAB_Pin */
  GPIO_InitStruct.Pin = Reset_Radiator_Pin|Reset_WP_Pin|Reset_MAB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : MAB_SW_Pin */
  GPIO_InitStruct.Pin = MAB_SW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MAB_SW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SDCI_ButtL_Pin SDCI_ButtDB_Pin SDCI_TSMS_Pin FRO_out_Pin */
  GPIO_InitStruct.Pin = SDCI_ButtL_Pin|SDCI_ButtDB_Pin|SDCI_TSMS_Pin|FRO_out_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SDCI_ButtR_Pin SDCI_TSAC_Pin SDCI_INV0_Pin SDCI_INV1_Pin */
  GPIO_InitStruct.Pin = SDCI_ButtR_Pin|SDCI_TSAC_Pin|SDCI_INV0_Pin|SDCI_INV1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : SDCI_Inertia_Pin */
  GPIO_InitStruct.Pin = SDCI_Inertia_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SDCI_Inertia_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SDCI_HV_Distri_Pin SDCI_BOTS_Pin */
  GPIO_InitStruct.Pin = SDCI_HV_Distri_Pin|SDCI_BOTS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : WP_SW_Pin FAN_Radiator_SW_Pin FAN_TSAC_SW_Pin WP_CTRL_Pin
                           FAN_Radiator_CTRL_Pin FAN_TSAC_CTRL_Pin GP_SW_Pin Reset_GP_Pin */
  GPIO_InitStruct.Pin = WP_SW_Pin|FAN_Radiator_SW_Pin|FAN_TSAC_SW_Pin|WP_CTRL_Pin
                          |FAN_Radiator_CTRL_Pin|FAN_TSAC_CTRL_Pin|GP_SW_Pin|Reset_GP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);




}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
