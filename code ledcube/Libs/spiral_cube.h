/*
 * spiral_cube.h
 *
 *  Created on: 11 Jul 2022
 *      Author: phang
 */

#ifndef SPIRAL_CUBE_H_
#define SPIRAL_CUBE_H_

#include "led_cube_handle.h"

typedef enum
{
	ROLL_BIGGEST,
	ROLL_BIGGER,
	ROLL_MEDIUM,
	ROLL_SMALL
} rollSize_t;

typedef enum
{
	CLOCKWISE,
	COUNTER_CLOCKWISE
} directRotate_t;

typedef enum
{
	Y_AXIS_1,
	X_AXIS_1,
	Y_AXIS_2,
	X_AXIS_2,
} axis_t;

typedef enum
{
	SPIRAL_IN,
	SPIRAL_OUT
} spiralDirect_t;

void SpiralCube_Handle();
void SpiralCube_Set_State();
void RollBiggest_Handle();
void RollBigger_Handle();
void RollMedium_Handle();
void RollSmall_Handle();

#endif /* SPIRAL_CUBE_H_ */
