#ifndef _PLANE_CUBE_H_
#define _PLANE_CUBE_H_

#include "clear_cube.h"
#include "led_cube_handle.h"
#include "transmit_data.h"
#include "main.h"

typedef enum{
	OX,
	OY,
	OZ
} Plane_way_t;

void PlaneCube_Handle(SPI_HandleTypeDef hspi1);
void PlaneCube_Set_State();

#endif
