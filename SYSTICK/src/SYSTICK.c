#include "../inc/SYSTICK.h"

// #define max_delay 0xFFFFFF
#define min_STK_VAL 0x00000001
#define max_STK_VAL 0x00FFFFFF

#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR   (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

volatile uint32_t *STK_CTRL  = (volatile uint32_t *)0xE000E010;
volatile uint32_t *STK_LOAD  = (volatile uint32_t *)0xE000E014;
volatile uint32_t *STK_VAL   = (volatile uint32_t *)0xE000E018;
volatile uint32_t *STK_CALIB = (volatile uint32_t *)0xE000E01C;

SysticknuErrorStatus_t SystickCTRL(Enable_systick_t Enable_systick , Systick_Interrupt_t Systick_Interrupt, Clock_Source_Selection_t Clock_Source_Selection){
    SysticknuErrorStatus_t local_error = Systick_enu_OK ;
    *STK_CTRL = (Enable_systick << 0) | (Systick_Interrupt << 1) | (Clock_Source_Selection << 2);
    return local_error;
}
SysticknuErrorStatus_t SystickLOAD(uint32_t STK_val) {
    SysticknuErrorStatus_t local_error = Systick_enu_OK;
    if (STK_val < min_STK_VAL || STK_val > max_STK_VAL) {
        local_error = Systick_enu_NOK;
    } else {
        *STK_LOAD = STK_val;
    }
    return local_error;
}
SysticknuErrorStatus_t SystickCurrentVAL(uint32_t STK_val){
    SysticknuErrorStatus_t local_error = Systick_enu_OK ;
    *STK_VAL |= STK_val;
    return local_error;
}
void SysTick_Handler(){
    GPIOA_ODR ^= (1 << 5);
}

SysticknuErrorStatus_t Systickinit() {
    SysticknuErrorStatus_t status = Systick_enu_OK;
    status = SystickLOAD(16000);
    if (status == Systick_enu_OK) {
        status = SystickCTRL(Enable_systick,Enable_interrupt, AHB);
    }
    if (status == Systick_enu_OK) {
        status = SystickCurrentVAL(0);
    }
    return status;
}

SysticknuErrorStatus_t SystickStart();
SysticknuErrorStatus_t SystickStop();