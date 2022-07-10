#ifndef _LED_HANDLE_H_
#define _LED_HANDLE_H_


#include "random_rain_cube.h"
#include "count_down_cube.h"
#include "around_edge_cube.h"
#include "diagonal_cube.h"
#include "grow_shrink_cube.h"
#include "plane_cube.h"
#include "light_cube.h"
#include "clear_cube.h"
#include "button.h"

typedef enum
{
	TURN_OFF_ALL_LEDS,
	TURN_ON_ALL_LEDS,
	SWEEP_ALL_LEDS,
	GROW_SHRINK_CUBE,
	DIAGONAL_CUBE,
	AROUND_EDGE_CUBE,
	COUNT_DOWN_CUBE,
	RANDOM_RAIN_CUBE
} Cube_Status;

void Led_cube_Handle(Cube_Status cube_state,SPI_HandleTypeDef hspi1);

extern Cube_Status currentEffect;

#endif
