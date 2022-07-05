#include "plane_cube.h"

Plane_way_t way_state;
const uint32_t time_todo1 = 100;
static uint8_t way;
static uint32_t timer = 0;
uint8_t layer;
static uint8_t column_y[8] = {};
static int i = 0;

void PlaneCube_Handle(SPI_HandleTypeDef hspi1){
	switch(way_state){
	case OX:
	{
		uint8_t column[8] = {};
		layer = 0xff;
		if (HAL_GetTick() - timer >= time_todo1)
		{
			if (way)
			{
				column[i] = 0xff;
				TransmitData(column, layer, hspi1);
				if (column[7] == 0xff) way = 0;
				else i++;
			} else
			{
				column[--i] = 0xff;
				TransmitData(column, layer, hspi1);
				if (column[0] == 0xff)
					{
						way = 1;
						i = 0;
						way_state = OY;
					}
			}
			timer = HAL_GetTick();
		}

	}
		break;
	case OY:
	{
		layer = 0xff;
		if (column_y[0] == 0)
		{
			for (int j = 0; j < 8; j++)
			{
				column_y[j] = 1;
			}
			TransmitData(column_y, layer, hspi1);
			timer = HAL_GetTick();
		}
		if (HAL_GetTick() - timer >= time_todo1)
		{
			if (way)
			{
				for (int j = 0; j < 8; j++)
				{
					column_y[j] <<= 1;
				}
				TransmitData(column_y, layer, hspi1);
				if (column_y[0] == 0x80) way = 0;
			} else
			{
				for (int j = 0; j < 8; j++)
				{
					column_y[j] >>= 1;
				}
				TransmitData(column_y, layer, hspi1);
				if (column_y[0] == 0x00)
				{
					layer = 0;
					way = 1;
					way_state = OZ;
				}
			}
			timer = HAL_GetTick();
		}
	}
		break;
	case OZ:
	{
		uint8_t column[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
		if(layer == 0)
		{
			layer = 1;
			TransmitData(column, layer, hspi1);
			timer = HAL_GetTick();
		}
		if(HAL_GetTick() - timer >= time_todo1)
		{
			if(way)
			{
				layer <<= 1;
				TransmitData(column, layer, hspi1);
				if(layer == 0x80) way = 0;
			} else
			{
				layer >>= 1;
				TransmitData(column, layer, hspi1);
				if(layer == 0x01)
				{
					i = 0;
					way = 1;
					way_state = OX;
					layer = 0;
				}
			}
			timer = HAL_GetTick();
		}
	}
		break;
	default:
		break;
	}



}

void PlaneCube_Set_State(){
	currentEffect = SWEEP_ALL_LEDS;
	for (int j = 0; j < 8; j++)
	{
		column_y[j] = 0;
	}
	i = 0;
	way = 1;
	layer = 0;
	way_state = OX;
}
