#include "led_cube_handle.h"

Cube_Status currentEffect = SWEEP_ALL_LEDS;

void Btn_press_Callback(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	switch(currentEffect){
	case TURN_OFF_ALL_LEDS:
		currentEffect = TURN_ON_ALL_LEDS;
		break;
	case TURN_ON_ALL_LEDS:
		PlaneCube_Set_State();
		break;
	case SWEEP_ALL_LEDS:
		GrowShrinkCube_Set_State();
		break;
	case GROW_SHRINK_CUBE:
		DiagonalCube_Set_State();
		break;
	case DIAGONAL_CUBE:
		AroundEdgeCube_Set_State();
		break;
	case AROUND_EDGE_CUBE:
		CountDownCube_Set_Sate();
		break;
	case COUNT_DOWN_CUBE:
		currentEffect = TURN_OFF_ALL_LEDS;
		break;
//	case RANDOM_RAIN_CUBE:
//		currentEffect = TURN_OFF_ALL_LEDS;
//		break;
	default:
		break;
	}
}

void Led_cube_Handle(Cube_Status cube_state,SPI_HandleTypeDef hspi1)
{
	switch (cube_state) {
		case TURN_OFF_ALL_LEDS:
			clearCube(hspi1);
			break;
		case TURN_ON_ALL_LEDS:
			lightCube(hspi1);
			break;
		case SWEEP_ALL_LEDS:
			PlaneCube_Handle(hspi1);
			break;
		case GROW_SHRINK_CUBE:
			GrowShrinkCube_Handle(hspi1);
			break;
		case DIAGONAL_CUBE:
			DiagonalCube_Handle(hspi1);
			break;
		case AROUND_EDGE_CUBE:
			AroundEdgeCube_Handle(hspi1);
			break;
		case COUNT_DOWN_CUBE:
			CountDownCube_Handle(hspi1);
			break;
//		case RANDOM_RAIN_CUBE:
//			RandomRainCube_Handle(hspi1);
//			break;
		default:
			break;
	}
}
