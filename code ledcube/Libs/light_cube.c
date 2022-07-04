#include "light_cube.h"
#include "merge_data.h"
#include "transmit_data.h"

void lightCube()
{
	for (int i = 0;  i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			column[i] = 0xff;
		}
		layer = 0x80 >> i;
		mergeData(column, layer);
		TransmitData(dataOut);
	}
}
