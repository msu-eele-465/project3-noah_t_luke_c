#include <msp430.h>
#include <stdbool.h>

#define unlock_code "1738"
const char keys[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
const char rowPins[4] = {BIT0, BIT1, BIT2, BIT3};
const char colPins[4] = {BIT0, BIT1, BIT2, BIT3};

void keypadInit(void){

    // Status LED setup
    P1DIR |= BIT1;  // P1.1 as output
    P1OUT &= ~BIT1;  // Clear P1.1
    P1DIR |= BIT2;  // P1.2 as output
    P1OUT &= ~BIT2;  // Clear P1.2
    P1DIR |= BIT3;  // P1.3 as output
    P1OUT &= ~BIT3;  // Clear P1.3

    // Column pins are 6.0 - 6.3, right 4 pins on Keypad, descending left to right
    // Pin 5.0 is column 0 (connected to the middle of the keypad) (column 0 is the furthest left column)
    // Pin 5.3 is column 3 (connected to the right of the keypad) (column 3 is the furthest right column)
    P6DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3);  // Clear column pins
    P6DIR |= (BIT0 + BIT1 + BIT2 + BIT3);  // Set column pins as outputs
    P6OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);  // Set column pins low

    // Row pins are 5.0 - 5.3, left 4 pins, descending left to right
    // Pin 6.0 is row 0 (connected to the middle of the keypad) (row 0 is the top column)
    // Pin 6.3 is row 3 (connected to the left of the keypad) (row 3 is the bottom column)
    P5DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3);  // Set row pins as inputs
    P5REN |= (BIT0 + BIT1 + BIT2 + BIT3);  // Enable pull-up/down resistors
    P5OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);  // Set pull-down for resistors

    // Interrupt Setup for 
}


void lockKeypad(char str[]){ // Reset system until correct password is typed in
        clear();
        P1OUT &= ~BIT1;
        P1OUT |= BIT3;
        while(scanPad() != str[0]);    // Wait for a 1
        P1OUT |= BIT2;
        while(scanPad() != str[1]);    // Wait for a 7
        while(scanPad() != str[2]);    // Wait for a 3
        while(scanPad() != str[3]);    // Wait for an 8
        P1OUT &= ~BIT2;
        P1OUT &= ~BIT3;
        P1OUT |= BIT1;
}


void testInput(void){ // Test the keypad after system unlocks
    char input = scanPad();
        switch(input){
            case 'D':   clear();
                        lockKeypad(unlock_code);
                        break;
            case '1':   pattern1();
                        break;
            case '2':   while(1){
                            clear();
                            pattern0();
                            testInput();
                        }
                        break;
                        
        }
}
        

char scanPad() { // Scan the keypad
    int row, col;  // Loop variables

    for (col = 0; col < 4; col++) {
        P6OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);  // Clear all column pins
        P6OUT |= colPins[col];  // Set the current column pin high

        for (row = 0; row < 4; row++) {
            if ((P5IN & rowPins[row]) != 0) {  // Check if the row pin is high
                while ((P5IN & rowPins[row]) != 0);  // Wait for key release
                __delay_cycles(50000);  // Debounce delay
                return keys[col][row];  // Return the pressed key
            }
        }
    }

    return 0;  // Return 0 if no key is pressed
}

