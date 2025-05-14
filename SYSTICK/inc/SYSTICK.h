#ifndef  SYSTICK_H
#define SYSTICK_H

#include "../../lib/std_types.h"
#include "../../lib/BIT_MATH.h"

#define Enable_preherial 
typedef enum{
    Disable_systick , 
    Enable_systick
}Enable_systick_t;

typedef enum{
    Disable_interrupt , 
    Enable_interrupt
}Systick_Interrupt_t;

typedef enum{
    AHB8 ,
    AHB
}Clock_Source_Selection_t;

typedef enum {
    Systick_enu_OK,
    Systick_enu_NOK,
    Systick_enu_INVALID_CLK,

}SysticknuErrorStatus_t;

SysticknuErrorStatus_t SystickCTRL(Enable_systick_t , Systick_Interrupt_t , Clock_Source_Selection_t);
SysticknuErrorStatus_t SystickLOAD(uint32_t STK_VAL);
SysticknuErrorStatus_t SystickCurrentVAL(uint32_t STK_VAL);
void Systick_Handler();
SysticknuErrorStatus_t Systickinit();

SysticknuErrorStatus_t SystickStart();
SysticknuErrorStatus_t SystickStop();


#endif
