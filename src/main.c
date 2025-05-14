#include "../include/RCC.h"

int main(void){
    RCC_enuEnableCLk( RCC_HSE);
    RCC_enuControlCLK(RCC_HSE);

    RCC_enuEnableCLk( RCC_HSI);
    RCC_enuControlCLK(RCC_HSI);

    RCC_enuEnableCLk( RCC_PLL);
    RCC_enuControlCLK(RCC_PLL);

RCC_enuPeripheral_t RCC_enuPeripheral = {
    
};
    
    while (1) {
        // Main loop
    }
    return 0;
}