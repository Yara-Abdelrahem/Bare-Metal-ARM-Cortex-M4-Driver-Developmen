#include "../../lib/std_types.h"
#include "../../lib/BIT_MATH.h"
#include"../../RCC/inc/RCC.h"
#include "../inc/Gpio.h"
#define Reset_value 0x00000000
#define Clear_bit 0
// GPIO Peripheral Base Addresses (for STM32F4 series, adjust for other models if needed)
#define GPIOA_BASE  (0x40020000UL)
#define GPIOB_BASE  (0x40020400UL)
#define GPIOC_BASE  (0x40020800UL)
#define GPIOD_BASE  (0x40020C00UL)
#define GPIOE_BASE  (0x40021000UL)
#define GPIOF_BASE  (0x40021400UL)
#define GPIOG_BASE  (0x40021800UL)
#define GPIOH_BASE  (0x40021C00UL)
#define GPIOI_BASE  (0x40022000UL)

// Macros for easy access to GPIO peripherals
#define GPIOAP       ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOBP       ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOCP       ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIODP       ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOEP       ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOFP       ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOGP       ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOHP       ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOIP       ((GPIO_TypeDef *) GPIOI_BASE)

// GPIO Register Structure (as defined earlier)
typedef struct {
    volatile uint32_t MODER;    // GPIO port mode register               (Offset: 0x00)
    volatile uint32_t OTYPER;   // GPIO port output type register        (Offset: 0x04)
    volatile uint32_t OSPEEDR;  // GPIO port output speed register       (Offset: 0x08)
    volatile uint32_t PUPDR;    // GPIO port pull-up/pull-down register  (Offset: 0x0C)
    volatile uint32_t IDR;      // GPIO port input data register         (Offset: 0x10)
    volatile uint32_t ODR;      // GPIO port output data register        (Offset: 0x14)
    volatile uint32_t BSRR;     // GPIO port bit set/reset register      (Offset: 0x18)
    volatile uint32_t LCKR;     // GPIO port configuration lock register (Offset: 0x1C)
    volatile uint32_t AFRL;     // GPIO alternate function low register  (Offset: 0x20)
    volatile uint32_t AFRH;     // GPIO alternate function high register (Offset: 0x24)
    volatile uint32_t BRR;      // GPIO bit reset register (only in some STM32) (Offset: 0x28)
} GPIO_TypeDef;
GPIO_enuErrorStatus_t GPIOPortModeRegister(GPIO_Peripherals_t copy_GPIOx, GPIO_Pins_t copy_PortPin,GPIO_Mode_t copy_GPIO_mode){
    GPIO_enuErrorStatus_t Loc_error = GPIO_OK;
    if (copy_GPIOx > GPIOI)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    if (copy_PortPin >MODER15)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    switch (copy_GPIOx)
    {
    case GPIOA:
        CLR_BIT(GPIOAP->MODER,copy_PortPin);
        GPIOAP->MODER |=(copy_GPIO_mode<<copy_PortPin);
    break;
    case GPIOB:
        CLR_BIT(GPIOBP->MODER,copy_PortPin);
        GPIOBP->MODER |=(copy_GPIO_mode<<copy_PortPin);
    break;
    case GPIOC:
        CLR_BIT(GPIOCP->MODER,copy_PortPin);
        GPIOCP->MODER |=(copy_GPIO_mode<<copy_PortPin);
        break;
    case GPIOD:
        CLR_BIT(GPIODP->MODER,copy_PortPin);
        GPIODP->MODER |=(copy_GPIO_mode<<copy_PortPin);
        break;
    case GPIOE:
        CLR_BIT(GPIOEP->MODER,copy_PortPin);
        GPIOEP->MODER |=(copy_GPIO_mode<<copy_PortPin);
        break;
    case GPIOF:
        CLR_BIT(GPIOFP->MODER,copy_PortPin);
        GPIOFP->MODER |=(copy_GPIO_mode<<copy_PortPin);
        break;
    case GPIOG:
        CLR_BIT(GPIOGP->MODER,copy_PortPin);
        GPIOGP->MODER |=(copy_GPIO_mode<<copy_PortPin);
        break;
    case GPIOH:
        CLR_BIT(GPIOHP->MODER,copy_PortPin);
        GPIOHP->MODER |=(copy_GPIO_mode<<copy_PortPin);
        break;
    case GPIOI:
        CLR_BIT(GPIOIP->MODER,copy_PortPin);
        GPIOIP->MODER |=(copy_GPIO_mode<<copy_PortPin);
        break;
    default:
        break;
    }

    return Loc_error;
}

GPIO_enuErrorStatus_t GPIOPortOutputTypeRegister(GPIO_Peripherals_t copy_GPIOx, GPIO_Pins_t copy_PortPin , GPIO_Config_t copy_Gpio_config)
{
    GPIO_enuErrorStatus_t Loc_error = GPIO_OK;
    if (copy_GPIOx > GPIOI)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    if (copy_PortPin >MODER15)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    if (copy_Gpio_config >OutputOpenDrain)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    uint32_t copy_PortPin_val=copy_PortPin/2;
    switch (copy_GPIOx)
    {
    case GPIOA:
        GPIOAP->OTYPER |=(copy_Gpio_config<<copy_PortPin_val);
    break;
    case GPIOB:
    GPIOBP->OTYPER |=(copy_Gpio_config<<copy_PortPin_val);
    break;
    case GPIOC:
        GPIOCP->OTYPER |=(copy_Gpio_config<<copy_PortPin_val);
        break;
    case GPIOD:
        GPIODP->OTYPER |=(copy_Gpio_config<<copy_PortPin_val);
        break;
    case GPIOE:
        GPIOEP->OTYPER |=(copy_Gpio_config<<copy_PortPin_val);
        break;
    case GPIOF:
        GPIOFP->OTYPER |=(copy_Gpio_config<<copy_PortPin_val);
        break;
    case GPIOG:
        GPIOGP->OTYPER |=(copy_Gpio_config<<copy_PortPin_val);
        break;
    case GPIOH:
        GPIOHP->OTYPER |=(copy_Gpio_config<<copy_PortPin_val);
        break;
    case GPIOI:
        GPIOIP->OTYPER |=(copy_Gpio_config<<copy_PortPin_val);
        break;
    default:
        break;
    }
    return Loc_error;
}

GPIO_enuErrorStatus_t GPIOPortOutputSpeedRegister(GPIO_Peripherals_t copy_GPIOx,GPIO_Pins_t copy_PortPin ,  GPIO_SPEED_t copy_Gpio_speed)
{
    GPIO_enuErrorStatus_t Loc_error = GPIO_OK;
    if (copy_GPIOx > GPIOI)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    if (copy_PortPin >MODER15)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    switch (copy_GPIOx)
    {
    case GPIOA:
        GPIOAP->OSPEEDR |=(copy_Gpio_speed<<copy_PortPin);
    break;
    case GPIOB:
    GPIOBP->OSPEEDR |=(copy_Gpio_speed<<copy_PortPin);
    break;
    case GPIOC:
        GPIOCP->OSPEEDR |=(copy_Gpio_speed<<copy_PortPin);
        break;
    case GPIOD:
        GPIODP->OSPEEDR |=(copy_Gpio_speed<<copy_PortPin);
        break;
    case GPIOE:
        GPIOEP->OSPEEDR |=(copy_Gpio_speed<<copy_PortPin);
        break;
    case GPIOF:
        GPIOFP->OSPEEDR |=(copy_Gpio_speed<<copy_PortPin);
        break;
    case GPIOG:
        GPIOGP->OSPEEDR |=(copy_Gpio_speed<<copy_PortPin);
        break;
    case GPIOH:
        GPIOHP->OSPEEDR |=(copy_Gpio_speed<<copy_PortPin);
        break;
    case GPIOI:
        GPIOIP->OSPEEDR |=(copy_Gpio_speed<<copy_PortPin);
        break;
    default:
        break;
    }

    return Loc_error;
}

GPIO_enuErrorStatus_t GPIOPortPullUp_PullDownRegister(GPIO_Peripherals_t copy_GPIOx, GPIO_Pins_t copy_PortPin  , GPIO_PUPD_t copy_Gpio_PUPD)
{
    GPIO_enuErrorStatus_t Loc_error = GPIO_OK;
    if (copy_GPIOx > GPIOI)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    if (copy_PortPin >MODER15)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    switch (copy_GPIOx)
    {
    case GPIOA:
        GPIOAP->PUPDR |=(copy_Gpio_PUPD<<copy_PortPin);
    break;
    case GPIOB:
    GPIOBP->PUPDR |=(copy_Gpio_PUPD<<copy_PortPin);
    break;
    case GPIOC:
        GPIOCP->PUPDR |=(copy_Gpio_PUPD<<copy_PortPin);
        break;
    case GPIOD:
        GPIODP->PUPDR |=(copy_Gpio_PUPD<<copy_PortPin);
        break;
    case GPIOE:
        GPIOEP->PUPDR |=(copy_Gpio_PUPD<<copy_PortPin);
        break;
    case GPIOF:
        GPIOFP->PUPDR |=(copy_Gpio_PUPD<<copy_PortPin);
        break;
    case GPIOG:
        GPIOGP->PUPDR |=(copy_Gpio_PUPD<<copy_PortPin);
        break;
    case GPIOH:
        GPIOHP->PUPDR |=(copy_Gpio_PUPD<<copy_PortPin);
        break;
    case GPIOI:
        GPIOIP->PUPDR |=(copy_Gpio_PUPD<<copy_PortPin);
        break;
    default:
        break;
    }
    return Loc_error;
}

GPIO_enuErrorStatus_t GPIOPortInputDataRegister(GPIO_Peripherals_t copy_GPIOx , GPIO_Pins_t copy_PortPin , uint32_t *IDRPin)
{
    GPIO_enuErrorStatus_t Loc_error = GPIO_OK;
    if (copy_GPIOx > GPIOI)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    if (copy_PortPin >MODER15)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
  
    uint32_t copy_PortPin_val=copy_PortPin/2;
    switch (copy_GPIOx)
    {
    case GPIOA:
        *IDRPin=GET_BIT(GPIOAP->IDR ,copy_PortPin_val);
    break;
    case GPIOB:
        *IDRPin=GET_BIT(GPIOBP->IDR ,copy_PortPin_val);
    break;
    case GPIOC:
        *IDRPin=GET_BIT(GPIOCP->IDR ,copy_PortPin_val);
        break;
    case GPIOD:
        *IDRPin=GET_BIT(GPIODP->IDR ,copy_PortPin_val);
        break;
    case GPIOE:
        *IDRPin=GET_BIT(GPIOEP->IDR ,copy_PortPin_val);
        break;
    case GPIOF:
        *IDRPin=GET_BIT(GPIOFP->IDR ,copy_PortPin_val);
        break;
    case GPIOG:
        *IDRPin=GET_BIT(GPIOGP->IDR ,copy_PortPin_val);
        break;
    case GPIOH:
        *IDRPin=GET_BIT(GPIOHP->IDR ,copy_PortPin_val);
        break;
    case GPIOI:
        *IDRPin=GET_BIT(GPIOIP->IDR ,copy_PortPin_val);
        break;
    default:
        break;
    }
    return Loc_error;
}

GPIO_enuErrorStatus_t GPIOPortOutputDataRegister(GPIO_Peripherals_t copy_GPIOx, GPIO_Pins_t copy_PortPin  , uint32_t ODRPin)
{
    GPIO_enuErrorStatus_t Loc_error = GPIO_OK;
    if (copy_GPIOx > GPIOI)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    if (copy_PortPin >MODER15)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    uint32_t copy_PortPin_val=copy_PortPin/2;
    switch (copy_GPIOx) {
        case GPIOA:
            (ODRPin) ? SET_BIT(GPIOAP->ODR, copy_PortPin_val) : CLR_BIT(GPIOAP->ODR, copy_PortPin_val);
            break;
        case GPIOB:
            (ODRPin) ? SET_BIT(GPIOBP->ODR, copy_PortPin_val) : CLR_BIT(GPIOBP->ODR, copy_PortPin_val);
            break;
        case GPIOC:
            (ODRPin) ? SET_BIT(GPIOCP->ODR, copy_PortPin_val) : CLR_BIT(GPIOCP->ODR, copy_PortPin_val);
            break;
        case GPIOD:
            (ODRPin) ? SET_BIT(GPIODP->ODR, copy_PortPin_val) : CLR_BIT(GPIODP->ODR, copy_PortPin_val);
            break;
        case GPIOE:
            (ODRPin) ? SET_BIT(GPIOEP->ODR, copy_PortPin_val) : CLR_BIT(GPIOEP->ODR, copy_PortPin_val);
            break;
        case GPIOF:
            (ODRPin) ? SET_BIT(GPIOFP->ODR, copy_PortPin_val) : CLR_BIT(GPIOFP->ODR, copy_PortPin_val);
            break;
        case GPIOG:
            (ODRPin) ? SET_BIT(GPIOGP->ODR, copy_PortPin_val) : CLR_BIT(GPIOGP->ODR, copy_PortPin_val);
            break;
        case GPIOH:
            (ODRPin) ? SET_BIT(GPIOHP->ODR, copy_PortPin_val) : CLR_BIT(GPIOHP->ODR, copy_PortPin_val);
            break;
        case GPIOI:
            (ODRPin) ? SET_BIT(GPIOIP->ODR, copy_PortPin_val) : CLR_BIT(GPIOIP->ODR, copy_PortPin_val);
            break;
        default:
            Loc_error = GPIO_NOK;
            break;
    }

    //copy_PortPin=copy_PortPin/2;
    // switch (copy_GPIOx)
    // {
    // case GPIOA:
    //     GPIOAP->ODR &=(Clear_bit<<copy_PortPin_val);
    //     GPIOAP->ODR |=(ODRPin<<copy_PortPin_val);

    // break;
    // case GPIOB:
    //     GPIOBP->ODR |=(ODRPin<<copy_PortPin);
    // break;
    // case GPIOC:
    //     GPIOCP->ODR |=(ODRPin<<copy_PortPin);
    // break;
    // case GPIOD:
    //     GPIODP->ODR |=(ODRPin<<copy_PortPin);
    // break;
    // case GPIOE:
    //     GPIOEP->ODR |=(ODRPin<<copy_PortPin);
    // break;
    // case GPIOF:
    //     GPIOFP->ODR |=(ODRPin<<copy_PortPin);
    // break;
    // case GPIOG:
    //     GPIOGP->ODR |=(ODRPin<<copy_PortPin);
    // break;
    // case GPIOH:
    //     GPIOHP->ODR |=(ODRPin<<copy_PortPin);
    // break;
    // case GPIOI:
    //     GPIOIP->ODR |=(ODRPin<<copy_PortPin);
    // break;
    // default:
    //     break;
    // }
    return Loc_error;
}

GPIO_enuErrorStatus_t GPIOPortBitSetResetRegister (GPIO_Peripherals_t copy_GPIOx , PortPInSet_Reset_t Set_Reset , GPIO_Pins_t copy_PortPin ,uint32_t copy_PortPinValue)
{
    GPIO_enuErrorStatus_t Loc_error = GPIO_OK;

    if (copy_GPIOx > GPIOI)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    if (copy_PortPin >MODER15)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
        uint32_t copy_PortPin_bit;
    if (Set_Reset ==SET)
    {
        copy_PortPin_bit=copy_PortPin;
    }else if (Set_Reset ==RESET)
    {
        copy_PortPin_bit=copy_PortPin+16;
    }
    
        switch (copy_GPIOx)
    {
    case GPIOA:
        GPIOAP->BSRR |=(copy_PortPinValue<<copy_PortPin_bit);
    break;
    case GPIOB:
    GPIOBP->BSRR |=(copy_PortPinValue<<copy_PortPin_bit);
    break;
    case GPIOC:
        GPIOCP->BSRR |=(copy_PortPinValue<<copy_PortPin_bit);
        break;
    case GPIOD:
        GPIODP->BSRR |=(copy_PortPinValue<<copy_PortPin_bit);
        break;
    case GPIOE:
        GPIOEP->BSRR |=(copy_PortPinValue<<copy_PortPin_bit);
        break;
    case GPIOF:
        GPIOFP->BSRR |=(copy_PortPinValue<<copy_PortPin_bit);
        break;
    case GPIOG:
        GPIOGP->BSRR |=(copy_PortPinValue<<copy_PortPin_bit);
        break;
    case GPIOH:
        GPIOHP->BSRR |=(copy_PortPinValue<<copy_PortPin_bit);
        break;
    case GPIOI:
        GPIOIP->BSRR |=(copy_PortPinValue<<copy_PortPin_bit);
        break;
    default:
        break;
    }
    return Loc_error;
}

GPIO_enuErrorStatus_t GPIOPortConfigurationLockRegister(GPIO_Peripherals_t copy_GPIOx, uint32_t LockKey, uint32_t LockKeyBit)
{
    GPIO_enuErrorStatus_t Loc_error = GPIO_OK;

    return Loc_error;
}

GPIO_enuErrorStatus_t GPIOAlternateFunctionLowRegister(GPIO_Peripherals_t copy_GPIOx  , AFR_t AFR , Alternative_Selection_t Alt_Selct)
{
    GPIO_enuErrorStatus_t Loc_error = GPIO_OK;
    if (copy_GPIOx > GPIOI)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    if (AFR >AFR7)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    switch (copy_GPIOx)
    {
    case GPIOA:
        GPIOAP->AFRL |=(Alt_Selct<<AFR);
    break;
    case GPIOB:
    GPIOBP->AFRL |=(Alt_Selct<<AFR);
    break;
    case GPIOC:
        GPIOCP->AFRL |=(Alt_Selct<<AFR);
        break;
    case GPIOD:
        GPIODP->AFRL |=(Alt_Selct<<AFR);
        break;
    case GPIOE:
        GPIOEP->AFRL |=(Alt_Selct<<AFR);
        break;
    case GPIOF:
        GPIOFP->AFRL |=(Alt_Selct<<AFR);
        break;
    case GPIOG:
        GPIOGP->AFRL |=(Alt_Selct<<AFR);
        break;
    case GPIOH:
        GPIOHP->AFRL |=(Alt_Selct<<AFR);
        break;
    case GPIOI:
        GPIOIP->AFRL |=(Alt_Selct<<AFR);
        break;
    default:
        break;
    }
    return Loc_error;
}

GPIO_enuErrorStatus_t GPIOAlternateFunctionHighRegister(GPIO_Peripherals_t copy_GPIOx , AFR_t AFR , Alternative_Selection_t Alt_Selct)
{
    GPIO_enuErrorStatus_t Loc_error = GPIO_OK;
if (copy_GPIOx > GPIOI)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    if (AFR >AFR7)
    {
        Loc_error = GPIO_NOK;
        return Loc_error;
    }
    switch (copy_GPIOx)
    {
    case GPIOA:
        GPIOAP->AFRH |=(Alt_Selct<<AFR);
    break;
    case GPIOB:
    GPIOBP->AFRH |=(Alt_Selct<<AFR);
    break;
    case GPIOC:
        GPIOCP->AFRH |=(Alt_Selct<<AFR);
        break;
    case GPIOD:
        GPIODP->AFRH |=(Alt_Selct<<AFR);
        break;
    case GPIOE:
        GPIOEP->AFRH |=(Alt_Selct<<AFR);
        break;
    case GPIOF:
        GPIOFP->AFRH |=(Alt_Selct<<AFR);
        break;
    case GPIOG:
        GPIOGP->AFRH |=(Alt_Selct<<AFR);
        break;
    case GPIOH:
        GPIOHP->AFRH |=(Alt_Selct<<AFR);
        break;
    case GPIOI:
        GPIOIP->AFRH |=(Alt_Selct<<AFR);
        break;
    default:
        break;
    }
    return Loc_error;
}
