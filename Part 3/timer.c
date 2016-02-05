/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>

void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // 1 second. Enable its interrupt
    TMR1=0;
    T1CONbits.ON=0; //enable timer, turn on in btn fwd state for part 3;
    T1CONbits.TCKPS=3; //prescaler to 256
    T1CONbits.TCS=0; //set oscillator output
    IEC0bits.T1IE=1; //enable interrupt
    IPC1bits.T1IP=3; //timer priority
    IFS0bits.T1IF=0; //timer flag down
    PR1=39061;
    
}