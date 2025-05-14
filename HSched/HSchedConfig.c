#include "../lib/std_types.h"
#include "../lib/BIT_MATH.h"
#include "HSchedConfig.h"
#include "../GPIO/inc/Gpio.h"


void blink_LED1(void) {
    static uint32_t pin_val1=1; 
    GPIOPortOutputDataRegister(GPIOA , MODER0 , pin_val1);
    pin_val1 ^=1;
}
void blink_LED2(void) {
    static uint32_t pin_val2=0; 
    GPIOPortOutputDataRegister(GPIOA , MODER1 , pin_val2);
    pin_val2 ^=1;
}

Task_t tasks[Num_Tasks] = {
    {blink_LED1, 1, 2, 0},   // Blink LED every 500ms
    {blink_LED2, 2, 4, 0}, // Read sensor every 1000ms
};

