#ifndef OLED_CONTROL_H
#define OLED_CONTROL_H

#include "main.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"

/* To keep track of both the cursor and the index */
typedef struct {
    char icon[2]; // Fixed size array for a single character plus null terminator
    int index;
} screen_cursor;

extern char alphabet[];
extern screen_cursor cursor;

void cursor_set(uint32_t potentiometer_value);

void cursor_update(void);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN);

#endif