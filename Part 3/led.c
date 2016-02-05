/* 
 * File:   led.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"
#define OUTPUT 0
#define INPUT 1

void initLEDs(){
    TRISDbits.TRISD0=OUTPUT;
    LATDbits.LATD0=0;
    TRISDbits.TRISD1=OUTPUT;
    LATDbits.LATD1=0;
    TRISDbits.TRISD2=OUTPUT;
    LATDbits.LATD2=0;
    //TODO: Initialize LEDs
}

void turnOnLED(int led){
    
    //TODO: You may choose to write this function
    // as a matter of convenience
    
}