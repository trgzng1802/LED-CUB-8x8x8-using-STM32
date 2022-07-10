#include "random_rain_cube.h"

static uint8_t layer_rain = 0x80, column_rain[8] = {};
const uint32_t time_rain = 100;
const uint32_t v_rain = 40;
static uint32_t time_start_rain = 0;
static uint32_t time_per_rain = 0;
static int times = 1, j;
static uint8_t temp;

void RandomRainCube_Handle(SPI_HandleTypeDef hspi1)
{
	if (HAL_GetTick() - time_start_rain >= time_rain)
	{
		srand(HAL_GetTick());

			if (layer_rain == 0x80)
			{
				j = rand() % 8;
				column_rain[j] = 0x01 << rand() % 8;
			}
		if (HAL_GetTick() - time_per_rain >= v_rain)
		{
			if (layer_rain == 1)
			{
				layer_rain = 0x80;
				column_rain[j] = 0;
			}
			else layer_rain >>= 1;
			TransmitData(column_rain, layer_rain, hspi1);
			time_per_rain = HAL_GetTick();
		}
		time_start_rain = HAL_GetTick();
	}

//	if (HAL_GetTick() - time_start_rain)
//	{
//		if (times)
//		for (int i = 0; i < 8; i++)
//		{
//			column_rain[i] = 0xff;
//
//		}
//		else if (times < 9)
//			{
//			temp = layer_rain;
//			layer_rain >>= times;
//			TransmitData(column_rain, layer_rain, hspi1);
//			layer_rain = temp;
//			times++;
//			}
//		else times = 0;
//		time_start_rain = HAL_GetTick();
//	}

}

void RandomRainCube_Set_State()
{
	currentEffect = RANDOM_RAIN_CUBE;
	layer_rain = 0x80;
	for (int k = 0; k < 8; k++)
	{
		column_rain[k] = 0;
	}
}
