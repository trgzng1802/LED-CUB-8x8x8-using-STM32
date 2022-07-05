#include "clear_cube.h"
#include "main.h"
#include "transmit_data.h"

void clearCube(SPI_HandleTypeDef hspi1)
{
	uint8_t column[8], layer;
	layer = 0x00;
	for (int i = 0; i < 8; i ++)
	{
		column[i] = 0x00;
	}
	TransmitData(column, layer, hspi1);
}
