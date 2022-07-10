#ifndef _COUNT_DOWN_CUBE_H_
#define _COUNT_DOWN_CUBE_H_

#include "main.h"
#include "transmit_data.h"
#include "led_cube_handle.h"

typedef enum
{
	DIGIT_ZERO,
	DIGIT_ONE,
	DIGIT_TWO,
	DIGIT_THREE,
	DIGIT_FOUR,
	DIGIT_FIVE,
	DIGIT_SIX,
	DIGIT_SEVEN,
	DIGIT_EIGHT,
	DIGIT_NINE

} digit_t;

void CountDownCube_Handle(SPI_HandleTypeDef hspi1);
void CountDownCube_Set_Sate();
void DigitNine(int i,SPI_HandleTypeDef hspi1);
void DigitEight(int i,SPI_HandleTypeDef hspi1);
void DigitSeven(int i,SPI_HandleTypeDef hspi1);
void DigitSix(int i,SPI_HandleTypeDef hspi1);
void DigitFive(int i,SPI_HandleTypeDef hspi1);
void DigitFour(int i,SPI_HandleTypeDef hspi1);
void DigitThree(int i, SPI_HandleTypeDef hspi1);
void DigitTwo(int i, SPI_HandleTypeDef hspi1);
void DigitOne(int i, SPI_HandleTypeDef hspi1);
void DigitZero(int i, SPI_HandleTypeDef hspi1);

#endif
