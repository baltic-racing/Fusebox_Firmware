/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "fdcan.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sdc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define WP_start_time  5000
#define TSAC_FANS_start_time 10000
#define Radiator_start_time  15000

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */



extern uint32_t sys_time;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void WP_HSD_Init(void)
{
	  /* Pin für WP dauerhaft HIGH */
	  HAL_GPIO_WritePin(GPIOD, WP_SW_Pin, GPIO_PIN_SET);
	  /* Pin für WP Standby high */
	  HAL_GPIO_WritePin(GPIOC, Reset_WP_Pin, GPIO_PIN_SET);
}
void FAN_RADIATOR_HSD_Init(void)
{
		/* Pin für Radiator Fans dauerhaft HIGH */
	  HAL_GPIO_WritePin(GPIOD, FAN_Radiator_SW_Pin, GPIO_PIN_SET);
	  /* Pin für Radiator Fans Standby high */
	  HAL_GPIO_WritePin(GPIOC, Reset_Radiator_Pin, GPIO_PIN_SET);
}

void TSAC_FANS_Init(void)
{
	/*Pin für TSAC Fan dauerhaft HIGH */
	HAL_GPIO_WritePin(GPIOD, FAN_TSAC_SW_Pin, GPIO_PIN_SET);
}

void setFanSpeed(uint8_t percent) {
    uint32_t ccr = (percent * 1000) / 100;
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, ccr);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	uint32_t last10 = 0;;
	uint32_t last100 = 0;
	uint32_t last1000 = 0;

	uint8_t radiator_startup_complete = 0;

	uint8_t fanspeed = 12;

	uint8_t inv_temp_r_C = 0;

	uint16_t board_voltage_mV = 0;
	uint16_t bat_sense_mV = 0;

	uint16_t board_voltage_history[5] = {0};
	uint8_t  board_voltage_index = 0;
	uint16_t board_voltage_avg_raw = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_FDCAN1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);

  config_FDCAN1();

  // Start FDCAN1
  if(HAL_FDCAN_Start(&hfdcan1)!= HAL_OK)
  {

   Error_Handler();
  }

  // Activate the notification for new data in FIFO0 for FDCAN1

  if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }
  // start PWM
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

  // set to 0% duty cycle
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


	  if (sys_time>= last10 + 10)
	  	{

		  	/*Calculate physical units */
		  	board_voltage_raw          = ADC_Read(ADC_CHANNEL_2);
		  	bat_sense_raw               = ADC_Read(ADC_CHANNEL_1);
		  	currentsense_radiator_raw   = ADC_Read(ADC_CHANNEL_3);
		  	currentsense_wp_raw         = ADC_Read(ADC_CHANNEL_4);
		  	currentsense_mab_raw        = ADC_Read(ADC_CHANNEL_6);
		  	currentsense_gp_raw         = ADC_Read(ADC_CHANNEL_7);

		  	board_voltage_raw = ADC_Read(ADC_CHANNEL_2);

		  	board_voltage_history[board_voltage_index] = board_voltage_raw;
		  	board_voltage_index = (board_voltage_index + 1) % 5;

		  	uint32_t board_voltage_sum = 0;
		  	for (uint8_t i = 0; i < 5; i++)
		  	{
		  		board_voltage_sum += board_voltage_history[i];
		  	}
		  	board_voltage_avg_raw = (uint16_t)(board_voltage_sum / 5);


		  	float board_voltage_calc = 20.0f + (board_voltage_avg_raw - 2150) * 0.011907f;
		  	board_voltage_mV = (uint16_t)(board_voltage_calc * 10.0f);

		  	bat_sense_mV     = (bat_sense_raw     * 3300UL) / 4095UL;

	  		TxData1[0] = (bat_sense_mV);
	  		TxData1[1] = (bat_sense_mV>>8);
	  		TxData1[2] = (board_voltage_mV);
	  		TxData1[3] = (board_voltage_mV>>8);
	  		TxData1[4] = (sdc_status);
	  		TxData1[5] = (sdc_status>>8);
	  		TxData1[6] = 0;
	  		TxData1[7] = fanspeed;

	  		 if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader1, TxData1)!= HAL_OK)
	  		 {
	  		  //Error_Handler();
	  		 }

	  		/*
	  		 * Bit 15: SDCI_DB
	  		 * Bit 14: SDCI_Inertia
	  		 * Bit 13: SDCI_BOTS
	  		 * Bit 12: SDCI_BL
	  		 * Bit 11: SDCI_HV_Distri
	  		 * Bit 10: SDCI_INV1
	  		 * Bit  9: SDCI_INV0
	  		 * Bit  8: SDCI_TSAC
	  		 * Bit  7: SDCI_BR
	  		 * Bit  6: SDCI_TSMS
	  		 * Bit 5-0: ungenutzt
	  		 */

	  		last10 = sys_time;
	  	}

	  	if (sys_time>= last100 + 100)
	  	{

	  		SDC_ReadAll();


			if(radiator_startup_complete)
			{
				if (inv_temp_r_raw < 100 || inv_temp_r_raw > 640 )
				{
					inv_temp_r_C = 65;
				}
				else
				{

					inv_temp_r_C = (uint8_t)(inv_temp_r_raw / 10);
				}

				fanspeed = inv_temp_r_C + 35;
				setFanSpeed(fanspeed);
			}

	  		HAL_GPIO_TogglePin(GPIOE, LED_RD_Pin);
	  		last100 = sys_time;
	  	}


	  	/* end 100ms
	  	#############################################################################################################*/

		if (sys_time>= last1000 + 1000)
		{
			if (radiator_startup_complete == 0 )
			{	  	if(sys_time > WP_start_time)
					{
				  		WP_HSD_Init();

				  	}

					if(sys_time > TSAC_FANS_start_time)
					{
						TSAC_FANS_Init();
					}

					if(sys_time > Radiator_start_time)
					{
						FAN_RADIATOR_HSD_Init();
						fanspeed += 1 ;
						setFanSpeed(fanspeed);

						if(fanspeed > 34){
						   radiator_startup_complete = 1;
						}
					}


			}
			last1000 = sys_time;
		}

		//end of 1s
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
