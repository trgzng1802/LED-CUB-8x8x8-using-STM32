/*
 * display_led.c
 *
 *  Created on: 11 Jul 2022
 *      Author: phang
 */
#include "display_led.h"

uint8_t ICcolumn[8], IClayer;
int WhichByte, WhichBit, WhichColumn;
uint8_t dataOut[9];

void DisplayLed(int x, int y, int  z, SPI_HandleTypeDef hspi1, int display)
{

	WhichByte = (((z << 6)+(y << 3) + x) >> 3);
	WhichBit = ((z << 6) + (y << 3) + x) - (WhichByte << 3);
	WhichColumn = WhichByte - (z*8);
	IClayer = 0x01 <<  z;
	ICcolumn[WhichColumn] = 0x01 << WhichBit;
	dataOut[0] = IClayer;
	for (int i = 1; i < 9; i++)
	{
		dataOut[i] = ICcolumn[i-1];
	}
	HAL_GPIO_WritePin(LATCH_PIN_GPIO_Port, LATCH_PIN_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1,dataOut, 9, 100);
	HAL_GPIO_WritePin(LATCH_PIN_GPIO_Port, LATCH_PIN_Pin, GPIO_PIN_SET);
	if (!display)
	{
		IClayer = 0;
		ICcolumn[WhichColumn] = 0;
	}
}

