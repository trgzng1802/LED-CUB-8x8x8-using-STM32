#include "diagonal_cube.h"

void DiagonalCube(SPI_HandleTypeDef hspi1)
{
	uint8_t layer, column[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	layer = 0x18;
	static uint32_t time_start;
	const uint32_t time_todo = 250;
	for (int i = 3; i < 5; i++)
	{
		column[i] = 0x18;
	}
	TransmitData(column, layer, hspi1);
	time_start = HAL_GetTick();
	start1: if (HAL_GetTick() - time_start < time_todo) goto start1;
	clearCube(hspi1);

	layer = 0x24;
	for (int i = 2; i < 6; i++)
	{
		column[i] = 0x3c;
	}
	TransmitData(column, layer, hspi1);
	time_start = HAL_GetTick();
	start2: if (HAL_GetTick() - time_start < time_todo) goto start2;
	clearCube(hspi1);

	layer = 0x42;
	for (int i = 1; i < 7; i++)
	{
		column[i] = 0x7e;
	}
	TransmitData(column, layer, hspi1);
	time_start = HAL_GetTick();
	start3: if (HAL_GetTick() - time_start < time_todo) goto start3;
	clearCube(hspi1);

	layer = 0x81;
	for (int i = 0; i < 8; i++)
	{
		column[i]=  0xff;
	}
	TransmitData(column, layer, hspi1);
	time_start = HAL_GetTick();
	start4: if (HAL_GetTick() - time_start < time_todo) goto start4;
	clearCube(hspi1);
}
