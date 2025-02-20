#include "intrinsics.h"
#include <msp430.h>
#include <stdbool.h>

int period = 1000;

void LEDbarInit(void){
    // Setting GPIO pins as outputs to control the LED bar
    // LED1
    P6DIR |= BIT4;
    P6OUT &= ~ BIT4;
    // LED2
    P3DIR |= BIT7;
    P3OUT &= ~ BIT7;
    // LED3
    P2DIR |= BIT4;
    P2OUT &= ~ BIT4;
    // LED4
    P4DIR |= BIT0;
    P4OUT &= ~BIT0;
    // LED5
    P3DIR |= BIT2;
    P3OUT &= ~ BIT2;
    // LED6
    P3DIR |= BIT0;
    P3OUT &= ~ BIT0;
    // LED7
    P2DIR |= BIT5;
    P2OUT &= ~ BIT5;
    // LED8
    P4DIR |= BIT4;
    P4OUT &= ~ BIT4;
}

void ON(int led){
    // Turns LED on the LED bar ON depending on the given int
    switch(led){
        case 1:     P6OUT |= BIT4;
                    break;
        case 2:     P3OUT |= BIT7;
                    break;
        case 3:     P2OUT |= BIT4;
                    break;
        case 4:     P4OUT |= BIT0;
                    break;
        case 5:     P3OUT |= BIT2;
                    break;
        case 6:     P3OUT |= BIT0;
                    break;
        case 7:     P2OUT |= BIT5;
                    break;
        case 8:     P4OUT |= BIT4;
                    break;
        default:    break;                                                                                                                              
    }
}

void OFF(int led){
    // Turns LED on the LED bar OFF depending on the given int
    switch(led){
        case 1:     P6OUT &= ~BIT4;
                    break;
        case 2:     P3OUT &= ~BIT7;
                    break;
        case 3:     P2OUT &= ~BIT4;
                    break;
        case 4:     P4OUT &= ~BIT0;
                    break;
        case 5:     P3OUT &= ~BIT2;
                    break;
        case 6:     P3OUT &= ~BIT0;
                    break;
        case 7:     P2OUT &= ~BIT5;
                    break;
        case 8:     P4OUT &= ~BIT4;
                    break;
        default:    break;                                                                                                                              
    }
}

void allOn(void){
    // Sets LED bar to a 0101010101 static pattern
    ON(1);
    ON(2);
    ON(3);
    ON(4);
    ON(5);
    ON(6);
    ON(7);
    ON(8);
}

void pattern0(void){
    // Sets LED bar to a 1010101010 static pattern
    ON(1);
    OFF(2);
    ON(3);
    OFF(4);
    ON(5);
    OFF(6);
    ON(7);
    OFF(8);
}

void pattern0_alt(void){
    // Sets LED bar to a 0101010101 static pattern
    OFF(1);
    ON(2);
    OFF(3);
    ON(4);
    OFF(5);
    ON(6);
    OFF(7);
    ON(8);
}

int pattern1(int start){
    if(start == 0){
        pattern0();
        return 1;
    }else if(start == 1){
        pattern0_alt();
        return 0;
    }
    else{
        return 0;
    }
}

int pattern2(int count){
    LEDON(count);
    if(count == 255){
        return 0;
    }
    count++;
    return count;
}

int pattern3(int start){
    switch (start){
        case 0:     clear();
                    ON(4);
                    ON(5);
                    return 1;
        case 1:     clear();
                    ON(3);
                    ON(6);
                    return 2;
        case 2:     clear();
                    ON(2);
                    ON(7);
                    return 3;
        case 3:     clear();
                    ON(1);
                    ON(8);
                    return 4;
        case 4:     clear();
                    ON(2);
                    ON(7);
                    return 5;
        case 5:     clear();
                    ON(3);
                    ON(6);
                    return 0;
    }
}

int pattern4(int count){  // Down counter 
    LEDON(count);
    if(count == 0){
        return 255;
    }
    count--;
    return count;
}

int pattern5(int current){  // Rotates the turned on LED one left each time
    if (current == 0){
        ON(8);
        return 1;
    }
    if (current == 1){
        ON(7);
        return 2;
    }
    if (current == 2){
        ON(6);
        return 3;
    }
    if (current == 3){
        ON(5);  
        return 4;  
    }
    if (current == 4){
        ON(4);   
        return 5; 
    }
    if (current == 5){
        ON(3);
        return 6;
    }
    if (current == 6){
        ON(2);
        return 7;
    }
    if (current == 7){
        ON(1);
        return 0;
    }
}

int pattern6(int current){  // Rotates the turned off LED one right each time
    if (current == 0){
        //allOn();
        OFF(1);
    }
    if (current == 1){
        //allOn();
        OFF(8);
    }
    if (current == 2){
        //allOn();
        OFF(7);
    }
    if (current == 4){
        //allOn();
        OFF(6);
    }
    if (current == 5){
        //allOn();
        OFF(5);
    }
    if (current == 6){
        //allOn();
        OFF(4);
    }
    if (current == 7){
        //allOn();
        OFF(3);
    }
    if (current == 8){
        //allOn();
        OFF(2);
    }
    if (current == 0){
        current = 8;
    }
    else{
        current--;
    }
    return current;
}

int pattern7(int current){  // Loading bar looking thing, turns on each led in a row
    if (current == 0){
        ON(8);
    }
    if (current == 1){
        ON(8);
        ON(7);
    }
    if (current == 2){
        ON(8);
        ON(7);
        ON(6);
    }
    if (current == 4){
        ON(8);
        ON(7);
        ON(6);
        ON(5);
    }
    if (current == 5){
        ON(8);
        ON(7);
        ON(6);
        ON(5);
        ON(4);
    }
    if (current == 6){
        ON(8);
        ON(7);
        ON(6);
        ON(5);
        ON(4);
        ON(3);
    }
    if (current == 7){
        ON(8);
        ON(7);
        ON(6);
        ON(5);
        ON(4);
        ON(3);
        ON(2);
    }
    if (current == 8){
        ON(8);
        ON(7);
        ON(6);
        ON(5);
        ON(4);
        ON(3);
        ON(2);
        ON(1);
    }
    if (current == 8){
        current = 0;
    }
    else{
        current++;
    }
    return current;
}

void clear(void){
    // Turns every LED off
    OFF(1);
    OFF(2);
    OFF(3);
    OFF(4);
    OFF(5);
    OFF(6);
    OFF(7);
    OFF(8);
}

void LEDON(int number){
        if((number & BIT7) != 0){
            ON(1);
        }
        if((number & BIT6) != 0){
            ON(2);
        }
        if((number & BIT5) != 0){
            ON(3);
        }
        if((number & BIT4) != 0){
            ON(4);
        }
        if((number & BIT3) != 0){
            ON(5);
        }
        if((number & BIT2) != 0){
            ON(6);
        }
        if((number & BIT1) != 0){
            ON(7);
        }
        if((number & BIT0) != 0){
            ON(8);
        }
    }


void delay(int cycles){
    while(cycles != 0){
        __delay_cycles(1000);
        cycles--;
    }
}