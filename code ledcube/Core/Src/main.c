/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TIME 150
#define delay 500
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
uint8_t layer;
uint8_t column[8];
uint8_t dataOut[9];
int currentEffect,flag;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void TransmitData(uint8_t* data);
void mergeData(uint8_t column_data[],uint8_t layer_data);
void lightCube();
void clearCube();
void growShrinkCube();
void upperCube();
void diagonalCube();
void sliderCube();
void randomRainCube();
void aroundEdgeCube();
void diaedgeCube();
void numberingCube();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0)
  {
	  if (currentEffect < 9) currentEffect++;
	  else currentEffect = 0;
  }
  HAL_Delay(200);
}

void TransmitData(uint8_t* data) //ok
{
	HAL_GPIO_WritePin(LATCH_PIN_GPIO_Port, LATCH_PIN_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1,data, 9, 10);
	HAL_GPIO_WritePin(LATCH_PIN_GPIO_Port, LATCH_PIN_Pin, GPIO_PIN_SET);
}

void mergeData(uint8_t column_data[], uint8_t layer_data) //ok
{
	dataOut[0] = layer_data;
	for (int i = 1; i < 9; i++)
	{
		dataOut[i] = column_data[i-1];
	}
}

void lightCube() //ok
{
	layer = 0xff;
	for (int i = 0; i < 8; i ++)
	{
		column[i] = 0xff;
	}
	mergeData(column, layer);
	TransmitData(dataOut);
}

void clearCube() //ok
{
	layer = 0x00;
	for (int i = 0; i < 8; i ++)
	{
		column[i] = 0x00;
	}
	mergeData(column, layer);
	TransmitData(dataOut);
}

void upperCube() //ok
{
	for (int i = 0; i < 8; i++)
	{
		column[i] = 0xff;
	}
	for (int i = 0; i < 8; i++)
	{
		layer = 0x01 << i;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(delay);
	}
}

void diagonalCube() //ok
{
	layer = 0x18;
	for (int i = 3; i < 5; i++)
	{
		column[i] = 0x18;
	}
	mergeData(column, layer);
	TransmitData(dataOut);
	HAL_Delay(delay/2);
	clearCube();

	layer = 0x24;
	for (int i = 2; i < 6; i++)
	{
		column[i] = 0x3c;
	}
	mergeData(column, layer);
	TransmitData(dataOut);
	HAL_Delay(delay/2);
	clearCube();

	layer = 0x42;
	for (int i = 1; i < 7; i++)
	{
		column[i] = 0x7e;
	}
	mergeData(column, layer);
	TransmitData(dataOut);
	HAL_Delay(delay/2);
	clearCube();

	layer = 0x81;
	for (int i = 0; i < 8; i++)
	{
		column[i]=  0xff;
	}
	mergeData(column, layer);
	TransmitData(dataOut);
	HAL_Delay(delay/2);
	clearCube();
}

void sliderCube() //ok
{
	layer = 0xff;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			column[j] = 0x01 << i;
		}
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(delay);
	}
}

void randomRainCube() //chua duoc
{
	clearCube();
	int tim = 70;
	int randomColumn[3];
		for(int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				randomColumn[j] = rand() % 8;
			}
		}
		for (int j = 0; j < 3; j++)
		{
	    column[randomColumn[j]] = rand() % 256;
		}

	    for (int j = 0; j < 8; j++)
	    {
	    	layer = 0x80 >> j;
	    	mergeData(column, layer);
	    	TransmitData(dataOut);
	    	HAL_Delay(tim);
	    }
	    for (int j = 0; j < 3; j++)
	    {
	    column[randomColumn[j]] = 0x00;
	    mergeData(column, layer);
	    TransmitData(dataOut);
	    }
}

void growShrinkCube() //ok
{

	uint8_t data1[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	uint8_t data2[9] = {0x7e,0x00,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x00};
	uint8_t data3[9] = {0x3c,0x00,0x00,0x3c,0x3c,0x3c,0x3c,0x00,0x00};
	uint8_t data4[9] = {0x18,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00};
	TransmitData(data1);
	HAL_Delay(TIME);
	TransmitData(data2);
	HAL_Delay(TIME);
	TransmitData(data3);
	HAL_Delay(TIME);
	TransmitData(data4);
	HAL_Delay(TIME);
	TransmitData(data3);
	HAL_Delay(TIME);
	TransmitData(data2);
	HAL_Delay(TIME);
	TransmitData(data1);
	HAL_Delay(TIME);
}

void aroundEdgeCube() //ok
{
		//layer 1
		layer = 0x81;
		column[0] = column[7] = 0xff;
		for (int i = 1; i < 7; i++)
		{
			column[i] = 0x81;
		}
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(0);
		//layer 2- 7
		layer = 0x7e;
		column[0] = column[7] = 0x81;
		for (int i = 1; i < 7; i++)
		{
			column[i] = 0x00;
		}
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(0);
}

void diaedgeCube() //ok
{
	int hold = 2;
	//layer 1-8
	layer = 0x81;
	column[0] = column[7] = 0xff;
	for (int i = 1; i < 7; i++) {
		column[i] = 0x81;
	}
	mergeData(column, layer);
	TransmitData(dataOut);
	HAL_Delay(hold);
	clearCube();

	//layer 2-7
	layer = 0x42;
	column[0] = column[7] = 0x81;
	column[1] = column[6] = 0x42;
	for (int i = 2; i < 6; i++) {
		column[i] = 0x00;
	}
	mergeData(column, layer);
	TransmitData(dataOut);
	HAL_Delay(hold);
	clearCube();

	//layer 3-6
	layer = 0x24;
	column[0] = column[7] = 0x81;
	column[1] = column[6] = column[3] = column[4] = 0x00;
	column[2] = column[5] = 0x24;
	mergeData(column, layer);
	TransmitData(dataOut);
	HAL_Delay(hold);
	clearCube();

	//layer 4-5
	layer = 0x18;
	column[3] =column[4] = 0x18;
	column[0] = column[7] = 0x81;
	column[1] = column[2] = column[5] = column[6] = 0x00;
	mergeData(column, layer);
	TransmitData(dataOut);
	HAL_Delay(hold);
	clearCube();
//			//layer
//			int hold = 0;
//			layer = 0x01;
//			column[0] = column[7] = 0xff;
//			for (int i = 1; i < 7; i++)
//			{
//				column[i] = 0x81;
//			}
//
//			//layer 8
//			layer = 0x80;
//			column[0] = column[7] = 0xff;
//			for (int i = 1; i < 7; i++)
//			{
//				column[i] = 0x81;
//			}
//			mergeData(column, layer);
//			TransmitData(dataOut);
//			HAL_Delay(hold);
//			//layer 2- 7
//			layer = 0x7e;
//			column[0] = column[7] = 0x81;
//			for (int i = 1; i < 7; i++)
//			{
//				column[i] = 0x00;
//			}
//			mergeData(column, layer);
//			TransmitData(dataOut);
//			HAL_Delay(hold);
//
//			for (int i = 0; i < 8; i++)
//			{
//				layer = 0x01 << i;
//				column[i] = 0x80 >> i;
//				mergeData(column, layer);
//				TransmitData(dataOut);
//				clearCube();
//				HAL_Delay(hold);
//			}
//
//			for (int i = 0; i < 8; i++)
//			{
//				layer = 0x80 >> i;
//				column[i] = 0x80 >> i;
//				mergeData(column, layer);
//				TransmitData(dataOut);
//				clearCube();
//				HAL_Delay(hold);
//			}
//
//			for (int i = 0; i < 8; i++)
//			{
//				layer = 0x80 >> i;
//				column[i] = 0x80 >> i;
//				mergeData(column, layer);
//				TransmitData(dataOut);
//				clearCube();
//				HAL_Delay(hold);
//			}
//
//			for (int i = 0; i < 8; i++)
//			{
//				layer = 0x80 >> i;
//				column[i] = 0x01 << i;
//				mergeData(column, layer);
//				TransmitData(dataOut);
//				clearCube();
//				HAL_Delay(hold);
//			}
//
//			for (int i = 0; i < 8; i++)
//			{
//				layer = 0x01 << i;
//				column[i] = 0x01 << i;
//				mergeData(column, layer);
//				TransmitData(dataOut);
//				clearCube();
//				HAL_Delay(hold);
//			}

}

void numberingCube() //ok
{
	int x = 0;
	int y = 40;
	clearCube();
	//digit 0
	for (int i = 0; i < 8; i++)
	{
		column[i] = 0x3c;
		layer = 0x81;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x66;
		layer = 0x42;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xc3;
		layer = 0x3c;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);
		clearCube();
		HAL_Delay(y);
	}
	HAL_Delay(delay);
	//digit 1
	for (int i = 0; i < 8; i++)
	{
		column[i] = 0xff;
		layer = 0x01;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x98;
		layer = 0x08;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xd8;
		layer = 0x10;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x78;
		layer = 0x20;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x38;
		layer = 0x40;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x18;
		layer = 0x86;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);
		clearCube();

		HAL_Delay(y);
	}
	HAL_Delay(delay);
	//digit 2
	for (int i = 0; i < 8; i++)
	{
		column[i] = 0x3c;
		layer = 0x80;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x66;
		layer = 0x40;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xc6;
		layer = 0x20;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x06;
		layer = 0x10;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x0c;
		layer = 0x08;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x18;
		layer = 0x04;
		mergeData(column, layer);
		TransmitData(dataOut);

		column[i] = 0x70;
		layer = 0x02;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xff;
		layer = 0x01;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);
		clearCube();

		HAL_Delay(y);
	}
	HAL_Delay(delay);
	//digit 3
	for (int i = 0; i < 8; i++)
	{
		column[i] = 0x7e;
		layer = 0x81;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xe7;
		layer = 0x42;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xc3;
		layer = 0x24;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x06;
		layer = 0x18;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);
		clearCube();

		HAL_Delay(y);
	}
	HAL_Delay(delay);
	//digit 4
	for (int i = 0; i < 8; i++)
	{
		column[i] = 0x06;
		layer = 0xf3;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xff;
		layer = 0x0c;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		for (int j = 0; j < 4; j++)
		{
		column[i] = 0x08 << j;
		layer = 0x80 >> j;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);
		}
		clearCube();
		HAL_Delay(y);
	}
	HAL_Delay(delay);
	//digit 5
	for (int i = 0; i < 8; i++)
	{
		column[i] = 0xff;
		layer = 0xc0;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xc0;
		layer = 0x20;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xfe;
		layer = 0x10;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x03;
		layer = 0x0c;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x83;
		layer = 0x02;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x7e;
		layer = 0x01;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);
		clearCube();
		HAL_Delay(y);
	}
	HAL_Delay(delay);
	//digit 6
	for (int i = 0; i < 8; i++)
	{
		column[i] = 0x7e;
		layer = 0x81;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xc3;
		layer = 0x4e;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xc0;
		layer = 0x20;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xfe;
		layer = 0x10;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);
		clearCube();
		HAL_Delay(y);
	}
	HAL_Delay(delay);
	//digit 7
	for (int i = 0; i < 8; i++)
	{
		column[i] = 0x7f;
		layer = 0xc0;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		for (int j = 0; j < 6; j++)
		{
			column[i] = 0x03 << j;
			layer = 0x20 >> j;
			mergeData(column, layer);
			TransmitData(dataOut);
			HAL_Delay(x);
		}
		clearCube();
		HAL_Delay(y);
	}
	HAL_Delay(delay);
	//digit 8
	for (int i = 0; i < 8; i++)
	{
		column[i] = 0xc3;
		layer = 0x66;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x7e;
		layer = 0x99;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);
		clearCube();
		HAL_Delay(y);
	}
	HAL_Delay(delay);
	//digit 9
	for (int i = 0; i < 8; i++)
	{
		column[i] = 0x7e;
		layer = 0x81;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xc3;
		layer = 0x60;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0xff;
		layer = 0x10;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x7f;
		layer = 0x08;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x03;
		layer = 0x04;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);

		column[i] = 0x83;
		layer = 0x02;
		mergeData(column, layer);
		TransmitData(dataOut);
		HAL_Delay(x);
		clearCube();
		HAL_Delay(y);
	}
	HAL_Delay(delay);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  currentEffect = 8;
	 switch (currentEffect) {
		case 0:
			lightCube();
			break;
		case 1:
			clearCube();
			break;
		case 2:
			growShrinkCube();
			break;
		case 3:
			upperCube();
			break;
		case 4:
			sliderCube();
			break;
		case 5:
			diagonalCube();
			break;
		case 6:
			randomRainCube();
			break;
		case 7:
			aroundEdgeCube();
			break;
		case 8:
			diaedgeCube();
			break;
		case 9:
			numberingCube();
			break;
		default:
			break;
	}
  }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LATCH_PIN_GPIO_Port, LATCH_PIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LATCH_PIN_Pin */
  GPIO_InitStruct.Pin = LATCH_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LATCH_PIN_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

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

#ifdef  USE_FULL_ASSERT
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
