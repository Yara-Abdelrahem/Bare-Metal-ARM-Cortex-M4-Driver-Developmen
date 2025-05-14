#ifndef RCC_H
#define RCC_H
#include "../../lib/std_types.h"

typedef enum {
    RCC_enu_OK,
    RCC_enu_NOK,
    RCC_enu_INVALID_CLK,

}RCC_enuErrorStatus_t;

typedef enum {
    RCC_HSI,
    RCC_HSE,
    RCC_PLL,
}RCC_enuCLK_t;

typedef enum {
    AHB1ENR,
    AHB2ENR,
    APB1ENR,
    APB2ENR,

}peripheral_clock_t;

typedef enum
{
    PLLP_2  ,
    PLLP_4  ,
    PLLP_6  ,
    PLLP_8  ,
}PLLP_t;

typedef struct {
    peripheral_clock_t RCC_enuPeripheralClock;
    uint32_t Clock_Enable ;
}RCC_enuPeripheral_t;

typedef struct
{
    uint32_t M;
    PLLP_t P;
    uint32_t Q;
    uint32_t N;
    RCC_enuCLK_t RCC_enu_CLK;
}PLL_CONFIG;

RCC_enuErrorStatus_t RCC_enuEnableCLk(RCC_enuCLK_t Copy_enuCLK);

RCC_enuErrorStatus_t RCC_enuDisableClk(RCC_enuCLK_t Copy_enuCLK);

RCC_enuErrorStatus_t RCC_enuGetClkStatus(RCC_enuCLK_t Copy_enuClockCfg,uint32_t* Add_ret);

RCC_enuErrorStatus_t RCC_enuControlCLK(RCC_enuCLK_t Copy_enuCLK);

RCC_enuErrorStatus_t RCC_enuSelSysClk(PLL_CONFIG *Add_stPLL);

RCC_enuErrorStatus_t RCC_enuEnablePeripheral(RCC_enuPeripheral_t RCC_enuPeripheral);

RCC_enuErrorStatus_t RCC_enuDisablePeripheral(RCC_enuPeripheral_t RCC_enuPeripheral);


/* 
RCC_enuErrorStatus_t RCC_enuEnPeriphal(uint64_t Periperal);
RCC_enuErrorStatus_t RCC_enuDisPeriphal(uint64_t Periperal);
RCC_enuErrorStatus_t RCC_enuEnPeriphal(uint64_t Periperal);
RCC_enuErrorStatus_t RCC_enuSetPLLCFG(PLL_Cfg* Add_stPLL);
RCC_enuErrorStatus_t RCC_enuSelSysClk(RCC_enuCLK_t Copy_enuCLK)
*/

/*
RCC_enuErrorStatus_t RCC_enuDisPeriphal(uint64_t Periperal);
RCC_enuErrorStatus_t RCC_enuEnPeriphal(uint64_t Periperal);
RCC_enuErrorStatus_t RCC_enuSetPLLCFG(PLL_Cfg* Add_stPLL);
RCC_enuErrorStatus_t RCC_enuSelSysClk(RCC_enuCLK_t Copy_enuCLK)
*/

#endif 