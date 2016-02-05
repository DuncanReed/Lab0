/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1
#define InitState 0
#define SL1 1
#define SL2 2
#define SL3 3
#define SBF 4
#define SBB 5


//TODO: Define states of the state machine
//typedef enum stateTypeEnum{
//} stateType;

//TODO: Use volatile variables that change within interrupts
volatile int state=0;

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function
    initLEDs();
    initTimer1();
    
    while(1){
        
        //TODO: Implement a state machine to create the desired functionality
        switch (state) {
              case SL1:
                   LATDbits.LATD0=1;
                   LATDbits.LATD1=0;
                   LATDbits.LATD2=0;
                  break;
        
              case SL2:
                  LATDbits.LATD0=0;
                  LATDbits.LATD1=1;
                  LATDbits.LATD2=0;
                  break;
        
              case SL3:
                  LATDbits.LATD0=0;
                  LATDbits.LATD1=0;
                  LATDbits.LATD2=1;
                  break;
        
              case SBF:
                  
                  break;
        
              case SBB:
                  
                  break;
        
              case InitState:
                  LATDbits.LATD0=0;
                  LATDbits.LATD1=0;
                  LATDbits.LATD2=0;
                  state=SL1;
                  break;
        
        }
        
    }
    
    return 0;
}

//TODO: Add interrupt service routines that manage the change of states
//for particular events as needed
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt(){
    IFS0bits.T1IF=0; //put down interrupt flag
    if(state==SL1){
        state=SL2;
    }
      else if(state==SL2){
          state=SL3;
    }
      else if(state==SL3){
          state=SL1;
    }
        
}