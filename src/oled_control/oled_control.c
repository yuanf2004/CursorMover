#include "oled_control.h"

#include <ssd1306.h>

/* Available characters to switch to */
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* Init state of cursor */
screen_cursor cursor = {"A", 0};

/* Write to screen (128 x 64) based on the value of the potentiometer */
void cursor_set(uint32_t potentiometer_value){
    /* Reset the screen */
    ssd1306_Fill(Black);
    uint8_t pot_val_eightbit = (uint8_t) potentiometer_value;
    if(pot_val_eightbit>128){
        pot_val_eightbit=128;
    }

    /* Set and write the cursor */
    ssd1306_SetCursor((pot_val_eightbit * 3), 32);
    ssd1306_WriteString(cursor.icon, Font_16x26, White);

    /* Update */
    ssd1306_UpdateScreen();
}

/* Update the cursor everytime an interrupt happens */
void cursor_update(void){
    /* If it goes above range, reset */
    if(cursor.index + 1 > 25){
        cursor.index = 0;
    }
    /* Else, set cursor to the next character in the alphabet */
    else{
        cursor.index += 1;
    }
    cursor.icon[0] = alphabet[cursor.index];
    cursor.icon[1] = '\n';
}

/* EXTI */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN){
    /* Debounce handler by comparing times since last press */
    static uint32_t last_tick = 0;
    uint32_t curr_tick = HAL_GetTick();
    if(GPIO_PIN == GPIO_PIN_1){
        /* Add a 200s time period post press to prevent debounce */
        if(curr_tick - last_tick > 200){
            cursor_update();
            last_tick = curr_tick;
        }
    }
}


