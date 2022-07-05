#include "grow_shrink_cube.h"

SizeCube_t size_cube;
const uint32_t time_todo2 = 200;
static uint32_t time_start = 0;
uint8_t column[4][8];
uint8_t layer_gs[4];

void GrowShrinkCube_Handle(SPI_HandleTypeDef hspi1) //ok
{
	uint8_t temp[8];
	column[0][0] = column[0][1] = column[0][2] = column[0][3] = column[0][4] = column[0][5] = column[0][6] = column[0][7] = 0xff;
	column[1][1] = column[1][2] = column[1][3] = column[1][4] = column[1][5] = column[1][6] = 0x7e;
    column[2][2] = column[2][3] = column[2][4] = column[2][5] = 0x3c;
    column[3][3] = column[3][4] = 0x18;

    layer_gs[0] = 0xff;
    layer_gs[1] = 0x7e;
    layer_gs[2] = 0x3c;
    layer_gs[3] = 0x18;

	switch (size_cube)
	{
		case TWO_X_TWO_CUBE:
			if (HAL_GetTick() - time_start >= time_todo2)
			{
				for (int j = 0; j < 8; j++)
				{
					temp[j] = column[3][j];
					TransmitData(temp, layer_gs[3], hspi1);
				}
				time_start = HAL_GetTick();
				size_cube = FOUR_X_FOUR_CUBE;
			}
			break;
		case FOUR_X_FOUR_CUBE:
			if (HAL_GetTick() - time_start >= time_todo2)
			{
				for (int j = 0; j < 8; j++)
				{
					temp[j] = column[2][j];
					TransmitData(temp, layer_gs[2], hspi1);
				}
				time_start = HAL_GetTick();
				size_cube = SIX_X_SIX_CUBE;
			}
			break;
		case SIX_X_SIX_CUBE:
			if (HAL_GetTick() - time_start >= time_todo2)
			{
				for (int j = 0; j < 8; j++)
				{
					temp[j] = column[1][j];
					TransmitData(temp, layer_gs[1], hspi1);
				}
				time_start = HAL_GetTick();
				size_cube = EIGHT_X_EIGHT_CUBE;
			}
			break;
		case EIGHT_X_EIGHT_CUBE:
			if (HAL_GetTick() - time_start >= time_todo2)
			{
				for (int j = 0; j < 8; j++)
				{
					temp[j] = column[0][j];
					TransmitData(temp, layer_gs[0], hspi1);
				}
				time_start = HAL_GetTick();
				size_cube = TWO_X_TWO_CUBE;
			}
			break;
		default:
			break;
	}
}

void GrowShrinkCube_Set_State()
{
	currentEffect = GROW_SHRINK_CUBE;
	for (int i = 0; i < 4; i++)
	{
		layer_gs[i] = 0;
		for (int j = 0; j < 8; j++)
		{
			column[i][j] = 0;
		}
	}
	size_cube = EIGHT_X_EIGHT_CUBE;
}
