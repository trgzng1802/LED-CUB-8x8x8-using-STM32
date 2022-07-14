/*
 * spiral_cube.c
 *
 *  Created on: 11 Jul 2022
 *      Author: phang
 */
#include "spiral_cube.h"

rollSize_t rollSize;
axis_t axisDirection;
directRotate_t directRotate;
spiralDirect_t spiralDirect;
static uint8_t x,y;
const uint8_t z = 8;
const uint32_t timePerColumn = 60;
uint32_t timeStart = 0;

void SpiralCube_Handle()
{
	switch (directRotate) {
		case COUNTER_CLOCKWISE:
			switch (rollSize)
			{
				case ROLL_BIGGEST:
					RollBiggestCounterClockWise_Handle();
					break;
				case ROLL_BIGGER:
					RollBiggerCounterClockWise_Handle();
					break;
				case ROLL_MEDIUM:
					RollMediumCounterClockWise_Handle();
					break;
				case ROLL_SMALL:
					RollSmallCounterClockWise_Handle();
					break;
				default:
					break;
			}
			break;
		case CLOCKWISE:
			switch (rollSize)
			{
				case ROLL_BIGGEST:
					RollBiggestClockWise_Handle();
					break;
				case ROLL_BIGGER:
					RollBiggerClockWise_Handle();
					break;
				case ROLL_MEDIUM:
					RollMediumClockWise_Handle();
					break;
				case ROLL_SMALL:
					RollSmallClockWise_Handle();
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void RollBiggestCounterClockWise_Handle()
{
	switch (axisDirection)
	{
		case Y_AXIS_1:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(0, y, z, 1);
				if (y == 0)
				{
					x = 1;
					rollSize = ROLL_BIGGER;
				}
				else y--;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_1:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(x, 0, z, 1);
				if (x == 7)
				{
					axisDirection = Y_AXIS_2;
					y = 0;
				}
				else x++;
				timeStart = HAL_GetTick();
			}
			break;

		case Y_AXIS_2:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(7, y, z, 1);
				if (y == 7)
				{
					axisDirection = X_AXIS_2;
					x = 7;
				}
				else y++;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_2:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(x, 7, z, 1);
				if (x == 1)
				{
					axisDirection = Y_AXIS_1;
					rollSize = ROLL_BIGGER;
					y = 7;
				}
				else x--;
				timeStart = HAL_GetTick();
			}
			break;
		default:
			break;
	}
}

void RollBiggerCounterClockWise_Handle()
{
	switch (axisDirection)
	{
		case Y_AXIS_1:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(1, y, z, 1);
				if (y  == 1)
				{
					x = 1;
					axisDirection = X_AXIS_1;
				}
				else y--;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_1:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(x, 1, z, 1);
				if (x  == 1)
				{
					y = 1;
					axisDirection = Y_AXIS_2;
				}
				else x++;
				timeStart = HAL_GetTick();
			}
			break;

		case Y_AXIS_2:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(6, y, z, 1);
				if (y  == 6)
				{
					x = 6;
					axisDirection = X_AXIS_2;
				}
				else y++;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_2:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(x, 6, z, 1);
				if (x  == 2)
				{
					y = 6;
					axisDirection = Y_AXIS_1;
					rollSize = ROLL_MEDIUM;
				}
				else x--;
				timeStart = HAL_GetTick();
			}
			break;
		default:
			break;
	}
}

void RollMediumCounterClockWise_Handle()
{
	switch (axisDirection) {
		case Y_AXIS_1:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(2, y, z, 1);
				if (y == 2)
				{
					x = 2;
					axisDirection = X_AXIS_1;
				}
				else y--;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_1:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(x, 2, z, 1);
				if (x  == 5)
				{
					y = 2;
					axisDirection = Y_AXIS_2;
				}
				else x++;
				timeStart = HAL_GetTick();
			}
			break;

		case Y_AXIS_2:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(5, y, z, 1);
				if (y == 5)
				{
					x = 5;
					axisDirection = X_AXIS_2;
				}
				else y++;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_2:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(x, 5, z, 1);
				if (x  == 3)
				{
					y = 5;
					axisDirection = Y_AXIS_1;
					rollSize = ROLL_SMALL;
				}
				else x--;
				timeStart = HAL_GetTick();
			}
			break;

		default:
			break;
	}
}

void RollSmallCounterClockWise_Handle()
{
	switch (axisDirection) {
		case Y_AXIS_1:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(3, y, z, 1);
				if (y == 3)
				{
					x = 3;
					axisDirection = X_AXIS_1;
				}
				else y--;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_1:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(x, 3, z, 1);
				if (x  == 4)
				{
					y = 3;
					axisDirection = Y_AXIS_2;
				}
				else x++;
				timeStart = HAL_GetTick();
			}
			break;

		case Y_AXIS_2:
			if (HAL_GetTick() - timeStart  >= timePerColumn)
			{
				DisplayLed(4, y, z, 1);
				if (y == 4)
				{
					clearCube();
					directRotate = CLOCKWISE;
					axisDirection = Y_AXIS_1;
					y = 0;
					x = 7;
				}
				else y++;
				timeStart = HAL_GetTick();
			}
			break;

		default:
			break;
	}
}

void RollBiggestClockWise_Handle()
{
	switch (axisDirection) {
		case Y_AXIS_1:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (y == 7) axisDirection = X_AXIS_1;
				else y++;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_1:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (x == 0) axisDirection = Y_AXIS_2;
				else x--;
				timeStart = HAL_GetTick();
			}
			break;

		case Y_AXIS_2:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (y == 0) axisDirection = X_AXIS_2;
				else y--;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_2:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (x == 6)
				{
					rollSize = ROLL_BIGGER;
					axisDirection = Y_AXIS_1;
				}
				else x++;
				timeStart = HAL_GetTick();
			}
			break;
		default:
			break;
	}
}

void RollBiggerClockWise_Handle()
{
	switch (axisDirection) {
		case Y_AXIS_1:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (y == 6) axisDirection = X_AXIS_1;
				else y++;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_1:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (x == 1) axisDirection = Y_AXIS_2;
				else x--;
				timeStart = HAL_GetTick();
			}
			break;

		case Y_AXIS_2:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (y == 1) axisDirection = X_AXIS_2;
				else y--;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_2:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (x == 5)
				{
					axisDirection = Y_AXIS_1;
					rollSize = ROLL_MEDIUM;
				}
				else x++;
				timeStart = HAL_GetTick();
			}
			break;
		default:
			break;
	}
}

void RollMediumClockWise_Handle()
{
	switch (axisDirection) {
		case Y_AXIS_1:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (y == 5) axisDirection = X_AXIS_1;
				else y++;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_1:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (x == 2) axisDirection = Y_AXIS_2;
				else x--;
				timeStart = HAL_GetTick();
			}
			break;

		case Y_AXIS_2:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (y == 2) axisDirection = X_AXIS_2;
				else y--;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_2:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (x == 4)
				{
					rollSize = ROLL_SMALL;
					axisDirection = Y_AXIS_1;
				}
				else x++;
				timeStart = HAL_GetTick();
			}
			break;
		default:
			break;
	}
}

void RollSmallClockWise_Handle()
{
	switch (axisDirection) {
		case Y_AXIS_1:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (y == 4) axisDirection = X_AXIS_1;
				else y++;
				timeStart = HAL_GetTick();
			}
			break;

		case X_AXIS_1:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (x == 3) axisDirection = Y_AXIS_2;
				else x--;
				timeStart = HAL_GetTick();
			}
			break;

		case Y_AXIS_2:
			if (HAL_GetTick() - timeStart >= timePerColumn)
			{
				DisplayLed(x, y, z, 1);
				if (y == 3)
				{
					clearCube();
					axisDirection = Y_AXIS_1;
					rollSize = ROLL_BIGGEST;
					x = 0;
					y = 7;
					directRotate = COUNTER_CLOCKWISE;
				}
				else y--;
				timeStart = HAL_GetTick();
			}
			break;

		default:
			break;
	}
}

void SpiralCube_Set_State()
{
	y = 7;
	directRotate = COUNTER_CLOCKWISE;
	axisDirection = Y_AXIS_1;
	spiralDirect = SPIRAL_IN;
}
