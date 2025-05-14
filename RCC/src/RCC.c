#include "../../lib/std_types.h"
#include "../inc/RCC.h"

#define RCC_BASE       0x40023800
#define RCC_HSION_mask 0x00000001
#define RCC_HSEON_mask 0x00010000
#define RCC_PLLON_mask 0x01000000

#define RCC_HSIRD_mask 0x00000002
#define RCC_HSERD_mask 0x00020000
#define RCC_PLLRD_mask 0x02000000

#define RCC_HSEPLLCFG_mask  0x00400000
#define RCC_HSIPLLCFG_mask  0xFFBFFFFF

#define RCC_HSIRD_bit 1
#define RCC_HSERD_bit 17
#define RCC_PLLRD_bit 25

#define RCC_PLL_P_MASK      0xFFFCFFFF
#define RCC_PLL_P_2_MASK    0x00000000
#define RCC_PLL_P_4_MASK    0x00010000
#define RCC_PLL_P_6_MASK    0x00020000
#define RCC_PLL_P_8_MASK    0x00030000

#define RCC_PLLN_Bit 6
#define RCC_PLLM_Bit 0

#define RCC_SW_MASK         0xFFFFFFFC

typedef struct{
    volatile uint32_t CR;       /*Control register*/
    volatile uint32_t PLLCFGR;  /*PLL configuration register*/
    volatile uint32_t CFGR;     /*Clock configuration register*/
    volatile uint32_t CIR;      /*Clock interrupt register*/
    volatile uint32_t AHB1RSTR; /*AHB1 peripheral reset register*/
    volatile uint32_t AHB2RSTR; /*AHB2 peripheral reset register*/
    volatile const uint64_t reserved1;/*Reserved*/
    volatile uint32_t APB1RSTR; /*APB1 peripheral reset register*/
    volatile uint32_t APB2RSTR; /*APB2 peripheral reset register*/
    volatile const uint64_t reserved2;/*Reserved*/
    volatile uint32_t AHB1ENR;  /*AHB1 peripheral clock enable register*/
    volatile uint32_t AHB2ENR;  /*AHB2 peripheral clock enable register*/
    volatile const uint64_t reserved3;/*Reserved*/
    volatile uint32_t APB1ENR;  /*APB1 peripheral clock enable register*/
    volatile uint32_t APB2ENR;  /*APB2 peripheral clock enable register*/
    volatile const uint64_t reserved4;/*Reserved*/
    volatile uint32_t AHB1LPENR;/*AHB1 peripheral clock enable in low power mode register*/
    volatile uint32_t AHB2LPENR;/*AHB2 peripheral clock enable in low power mode register*/
    volatile const uint64_t reserved5;/*Reserved*/
    volatile uint32_t APB1LPENR;/*APB1 peripheral clock enable in low power mode register*/
    volatile uint32_t APB2LPENR;/*APB2 peripheral clock enable in low power mode register*/
    volatile const uint64_t reserved6;/*Reserved*/
    volatile uint32_t RCC_BDCR; /*Backup domain control register*/
    volatile uint32_t RCC_CSR;  /*Control/status register*/
    volatile const uint64_t reserved7;/*Reserved*/
    volatile uint32_t RCC_SSCGR;/*Spread spectrum clock generation register*/
    volatile uint32_t RCC_PLLI2SCFGR;/*PLLI2S configuration register*/
    volatile const uint32_t reserved8;/*Reserved*/
    volatile uint32_t RCC_DCKCFGR;/*Dedicated Clock Configuration Register*/
}RCC_REGS;



RCC_REGS * RCC_ptr = (RCC_REGS*)RCC_BASE;

RCC_enuErrorStatus_t RCC_enuEnableCLk(RCC_enuCLK_t Copy_enuCLK){

    RCC_enuErrorStatus_t loc_error = RCC_enu_OK;
    uint32_t time_out = 500;
    uint32_t rcc_mask_on; 
    uint32_t rcc_mask_ready ;
    switch (Copy_enuCLK)
    {
    case RCC_HSI:
        rcc_mask_on = RCC_HSION_mask;
        rcc_mask_ready = RCC_HSIRD_mask;
        break;
    case RCC_HSE:
        rcc_mask_on = RCC_HSEON_mask;
        rcc_mask_ready = RCC_HSERD_mask;

        break;
    case RCC_PLL:
        rcc_mask_on =RCC_PLLON_mask;
        rcc_mask_ready = RCC_PLLRD_mask;
    default:
        loc_error = RCC_enu_INVALID_CLK;
        break;
    }
    RCC_ptr->CR |= rcc_mask_on;  
    while ((time_out--) && !(RCC_ptr->CR & rcc_mask_ready));
    return loc_error;
}
RCC_enuErrorStatus_t RCC_enuDisableClk(RCC_enuCLK_t Copy_enuCLK){
    RCC_enuErrorStatus_t loc_error = RCC_enu_OK;

    switch (Copy_enuCLK)
    {
    case RCC_HSI:
        RCC_ptr->CR &= ~RCC_HSION_mask;
        break;
    case RCC_HSE:
        RCC_ptr->CR &= ~RCC_HSEON_mask;
        break;
    case RCC_PLL:
        RCC_ptr->CR &= ~RCC_PLLON_mask;
    default:
        loc_error = RCC_enu_INVALID_CLK;
        break;
    }
    return loc_error;
    
}

RCC_enuErrorStatus_t RCC_enuGetClkStatus(RCC_enuCLK_t Copy_enuClockCfg,uint32_t* Add_ret){

    RCC_enuErrorStatus_t loc_error = RCC_enu_OK;

    switch (Copy_enuClockCfg)
    {
    case RCC_HSI:
        Add_ret = (RCC_ptr->CR &RCC_HSIRD_mask)>>RCC_HSIRD_bit;
        break;
    case RCC_HSE:
        Add_ret = (RCC_ptr->CR& RCC_HSERD_mask)>>RCC_HSERD_bit;
        break;
    case RCC_PLL:
        Add_ret =(RCC_ptr->CR & RCC_PLLRD_mask)>>RCC_PLLRD_bit;
    default:
        loc_error = RCC_enu_INVALID_CLK;
        break;
    }
    return loc_error;
}

RCC_enuErrorStatus_t RCC_enuControlCLK(RCC_enuCLK_t Copy_enuCLK){
    RCC_enuErrorStatus_t loc_error = RCC_enu_OK;
    uint32_t Loc_u32isOn;
    uint32_t temp ;
    RCC_enuErrorStatus_t Loc_enuStatus =  RCC_enuGetClkStatus(Copy_enuCLK,&Loc_u32isOn);
    
    if(!Loc_u32isOn){
        Loc_enuStatus = RCC_enu_NOK;
    }
    switch (Copy_enuCLK)
    {
    case RCC_HSI:
        temp = ((RCC_ptr->CFGR&RCC_SW_MASK));
        RCC_ptr->CFGR = temp; 
        break;
    case RCC_HSE:
        temp = ((RCC_ptr->CFGR&RCC_SW_MASK));
        temp |= 0xFFFFFFD;
        RCC_ptr->CFGR = temp; 
        break;
    case RCC_PLL:
        temp = ((RCC_ptr->CFGR&RCC_SW_MASK));
        temp |= 0xFFFFFFFE;
        RCC_ptr->CFGR = temp;     
    default:
        loc_error = RCC_enu_INVALID_CLK;
        break;
    }
    return loc_error;

}

RCC_enuErrorStatus_t RCC_enuSelSysClk(PLL_CONFIG *Add_stPLL){
    RCC_enuErrorStatus_t loc_error = RCC_enu_OK;
    uint32_t* Loc_u32Clkstatus, Loc_u32PLLstatus;
    RCC_enuErrorStatus_t loc_error_clck = RCC_enuGetClkStatus(Add_stPLL->RCC_enu_CLK,&Loc_u32Clkstatus);
    RCC_enuErrorStatus_t loc_error_clck2 = RCC_enuGetClkStatus(RCC_PLL,&Loc_u32PLLstatus);

    if (Loc_u32Clkstatus ==RCC_enu_INVALID_CLK || !(Loc_u32PLLstatus))
    {
        loc_error = RCC_enu_INVALID_CLK;
    }else if (Loc_u32Clkstatus == RCC_HSE)
    {
        RCC_ptr->PLLCFGR |= RCC_HSEPLLCFG_mask;
    }else if (Loc_u32Clkstatus == RCC_HSI)
    {
        RCC_ptr->PLLCFGR &= RCC_HSIPLLCFG_mask;
    }
    //PLLQ with 2 ≤PLLQ ≤15
    else if (Add_stPLL->Q <2 || Add_stPLL->Q>15)
    {
       loc_error = RCC_enu_INVALID_CLK;
    }
    //P = 2,4,6,8
    //Add_stPLL->P != 2 ||Add_stPLL->P != 4 ||Add_stPLL->P != 6 || Add_stPLL->P != 8
    else if (Add_stPLL->P < PLLP_2 || Add_stPLL>PLLP_8)
    {
        loc_error = RCC_enu_INVALID_CLK;
    }
    //PLLN with 192 ≤PLLN ≤432
    else if (Add_stPLL->N <192 || Add_stPLL->N >432)
    {
        loc_error = RCC_enu_INVALID_CLK;
    }
    //PLLM with 2 ≤PLLM ≤63
    else if (Add_stPLL->M <2 || Add_stPLL->M>63)
    {
        loc_error = RCC_enu_INVALID_CLK;
    }
    else{
        switch (Add_stPLL->P)
        {
            case PLLP_2:
                RCC_ptr->PLLCFGR = (RCC_ptr->PLLCFGR&RCC_PLL_P_MASK) | RCC_PLL_P_2_MASK;
                break;
            case PLLP_4:
                RCC_ptr->PLLCFGR = (RCC_ptr->PLLCFGR&RCC_PLL_P_MASK) | RCC_PLL_P_4_MASK;
            break;
        case PLLP_6:
                RCC_ptr->PLLCFGR = (RCC_ptr->PLLCFGR&RCC_PLL_P_MASK) | RCC_PLL_P_6_MASK;
            break;
        case PLLP_8:
            RCC_ptr->PLLCFGR |= RCC_PLL_P_8_MASK;
            break;
        default:
            break;
        }


    }
    RCC_ptr->PLLCFGR |= (Add_stPLL->N<<RCC_PLLN_Bit);
    RCC_ptr->PLLCFGR |= (Add_stPLL->M << RCC_PLLM_Bit);
    
    
    
    return loc_error;
}

RCC_enuErrorStatus_t RCC_enuEnablePeripheral(RCC_enuPeripheral_t RCC_enuPeripheral)
{
    RCC_enuErrorStatus_t loc_error;

    switch (RCC_enuPeripheral.RCC_enuPeripheralClock)
    {
    case AHB1ENR:
        RCC_ptr->AHB1ENR |= (1<<RCC_enuPeripheral.Clock_Enable);
        break;
    case AHB2ENR : 
        RCC_ptr->AHB2ENR |= (1<<RCC_enuPeripheral.Clock_Enable);
        break;
    case APB1ENR:
        RCC_ptr->APB1ENR |= (1<<RCC_enuPeripheral.Clock_Enable);
        break;
    case APB2ENR : 
        RCC_ptr->APB2ENR |= (1<<RCC_enuPeripheral.Clock_Enable);
        break;
    default:
        loc_error = RCC_enu_NOK;
        break;
    }
    return loc_error;
}

RCC_enuErrorStatus_t RCC_enuDisablePeripheral(RCC_enuPeripheral_t RCC_enuPeripheral)
{
    RCC_enuErrorStatus_t loc_error = RCC_enu_OK;

    switch (RCC_enuPeripheral.RCC_enuPeripheralClock)
    {
    case AHB1ENR:
        RCC_ptr->AHB1ENR |= ~(1<<RCC_enuPeripheral.Clock_Enable);
        break;
    case AHB2ENR : 
        RCC_ptr->AHB2ENR |= ~(1<<RCC_enuPeripheral.Clock_Enable);
        break;
    case APB1ENR:
        RCC_ptr->APB1ENR |= ~(1<<RCC_enuPeripheral.Clock_Enable);
        break;
    case APB2ENR : 
        RCC_ptr->APB2ENR |= ~(1<<RCC_enuPeripheral.Clock_Enable);
        break;
    default:
        loc_error = RCC_enu_NOK;
        break;
    }
    return loc_error;
}

