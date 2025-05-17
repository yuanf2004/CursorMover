#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "main.h"

uint32_t potentiometer_reading(ADC_HandleTypeDef *hadc, UART_HandleTypeDef *huart);

uint32_t round_reading(uint32_t reading);

#endif