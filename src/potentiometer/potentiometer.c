#include "potentiometer.h"

/* Get the potentiometer reading (0 to 4095, 12-bit resolution)*/
uint32_t potentiometer_reading(ADC_HandleTypeDef *hadc, UART_HandleTypeDef *huart){
    /* Start and wait for ADC conversion */
    HAL_ADC_Start(hadc);
    HAL_ADC_PollForConversion(hadc, 10);
    uint32_t potentiometer_reading = HAL_ADC_GetValue(hadc);
    /* Update the reading by rounding it */
    potentiometer_reading = round_reading(potentiometer_reading);

    /* Output potentiometer value for debugging purposes */
    // char buffer[12];
    // snprintf(buffer, sizeof(buffer), "%lu\r\n", potentiometer_reading);

    // HAL_UART_Transmit(huart, (uint8_t *) buffer, strlen(buffer), HAL_MAX_DELAY);

    HAL_Delay(25);
    /* Return value */
    return potentiometer_reading;
}

/* 
Round the reading value to the nearest 100, then turn it into an integer 
from 0 to 42 
*/
uint32_t round_reading(uint32_t reading){
    return ((reading+50)/100 *100/100);
}