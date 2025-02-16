#include <msp430.h>
#include <stdbool.h>

void LEDbarInit(void){
    P6DIR &= ~BIT4;
}