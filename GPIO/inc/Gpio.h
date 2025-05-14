#ifndef GPIO_H
#define GPIO_H
#include "../../lib/std_types.h"
#include"../../RCC/inc/RCC.h"

//GPIO peripherals
typedef enum {
    GPIOA  ,
    GPIOB  ,
    GPIOC  ,
    GPIOD  ,
    GPIOE  ,
    GPIOF  ,
    GPIOG  ,
    GPIOH  ,
    GPIOI   

} GPIO_Peripherals_t;

typedef enum{
    MODER0  = 0,
    MODER1  =2,
    MODER2  =4,
    MODER3  = 6,
    MODER4  = 8,
    MODER5  = 10,
    MODER6  = 12,
    MODER7  = 14,
    MODER8  = 16,
    MODER9  = 18,
    MODER10 = 20,
    MODER11 = 22,
    MODER12 = 24,
    MODER13 = 26,
    MODER14 = 28,
    MODER15 = 30,

}GPIO_Pins_t;

typedef enum {
    GPIO_MODE_INPUT  = 0x00,  // Input mode
    GPIO_MODE_OUTPUT = 0x01,  // Output mode
    GPIO_MODE_AF     = 0x02,  // Alternate function mode
    GPIO_MODE_ANALOG = 0x03   // Analog mode
} GPIO_Mode_t;

typedef enum {
    GPIO_OK, 
    GPIO_NOK,   
    GPIO_ERROR,
      
} GPIO_enuErrorStatus_t;

typedef enum{
    OutputPushPull , 
    OutputOpenDrain
}GPIO_Config_t;

typedef enum{
    LowSpeed ,
    MediumSpeed,
    HighSpeed ,
    VeryHighSpeed
}GPIO_SPEED_t;

typedef enum{
   SET,
   RESET
}PortPInSet_Reset_t;
typedef enum {
    NoPullUpPullDown,
    PullUp,
    PullDown,
    Reserved
}GPIO_PUPD_t;

typedef enum{
    AF0     =  0000  ,
    AF1     =  0001  ,
    AF2     =  0010  ,
    AF3     =  0011  ,
    AF4     =  0100  ,
    AF5     =  0101  ,
    AF6     =  0110  ,
    AF7     =  0111  ,
    AF8     =  1000  ,
    AF9     =  1001  ,
    AF10    =  1010  ,
    AF11    =  1011  ,
    AF12    =  1100  ,
    AF13    =  1101  ,
    AF14    =  1110  ,
    AF15    =  1111  ,
}Alternative_Selection_t;
typedef enum{
    AFR0 = 0,
    AFR1 = 4,
    AFR2 = 8,
    AFR3 = 12,
    AFR4 = 16,
    AFR5 = 20,
    AFR6 = 24,
    AFR7 = 28,
}AFR_t;

// Function prototype
GPIO_enuErrorStatus_t GPIOPortModeRegister(GPIO_Peripherals_t copy_GPIOx, GPIO_Pins_t copy_PortPin,GPIO_Mode_t copy_GPIO_mode);

GPIO_enuErrorStatus_t GPIOPortOutputTypeRegister (GPIO_Peripherals_t copy_GPIOx,GPIO_Pins_t copy_PortPin ,  GPIO_Config_t copy_Gpio_config);
GPIO_enuErrorStatus_t GPIOPortOutputSpeedRegister (GPIO_Peripherals_t copy_GPIOx , GPIO_Pins_t copy_PortPin , GPIO_SPEED_t copy_Gpio_speed);

GPIO_enuErrorStatus_t GPIOPortPullUp_PullDownRegister (GPIO_Peripherals_t copy_GPIOx  , GPIO_Pins_t copy_PortPin  ,GPIO_PUPD_t copy_Gpio_PUPD);

GPIO_enuErrorStatus_t GPIOPortInputDataRegister (GPIO_Peripherals_t copy_GPIOx , GPIO_Pins_t copy_PortPin  ,uint32_t *IDRPin);
GPIO_enuErrorStatus_t GPIOPortOutputDataRegister (GPIO_Peripherals_t copy_GPIOx , GPIO_Pins_t copy_PortPin  , uint32_t ODRPin);

GPIO_enuErrorStatus_t GPIOPortBitSetResetRegister (GPIO_Peripherals_t copy_GPIOx , PortPInSet_Reset_t Set_Reset , GPIO_Pins_t copy_PortPin , uint32_t copy_PortPinValue );
GPIO_enuErrorStatus_t GPIOPortConfigurationLockRegister (GPIO_Peripherals_t copy_GPIOx , uint32_t LockKey , uint32_t LockKeyBit);

GPIO_enuErrorStatus_t GPIOAlternateFunctionLowRegister (GPIO_Peripherals_t copy_GPIOx , AFR_t AFR ,Alternative_Selection_t Alt_Selct);
GPIO_enuErrorStatus_t GPIOAlternateFunctionHighRegister (GPIO_Peripherals_t copy_GPIOx ,AFR_t AFR, Alternative_Selection_t Alt_Selct);


#endif 