#include "light_cube.h"

void lightCube()
{
	uint8_t column[8], layer;
	for (int i = 0;  i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			column[i] = 0xff;
		}
		layer = 0x80 >> i;
		TransmitData(column, layer);
	}
}
