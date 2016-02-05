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
#define DOWN 0
#define UP 1
#define InitState 0
#define SL1 1
#define SL2 2
#define SL3 3
#define SBF 4
#define SBB 5
//#define delay1 6
//#define delay2 7
//#define delay3 8


//TODO: Define states of the state machine
//typedef enum stateTypeEnum{
//} stateType;

//TODO: Use volatile variables that change within interrupts
volatile int state=0;
volatile int forward=1;

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function
    initLEDs();
    initTimer1();
    initSwitch();
    
        
    
    

    
    while(1){
        //state=nextState;
        //TODO: Implement a state machine to create the desired functionality
        switch (state) {
              case SL1:
                   LATDbits.LATD0=1;
                   LATDbits.LATD1=0;
                   LATDbits.LATD2=0;
                   T1CONbits.ON=0;
                   forward=1;
                    if(PORTDbits.RD6==DOWN || PORTDbits.RD7==DOWN || PORTDbits.RD13==DOWN){
                       state=SBF;
                       TMR1=0;
                       PR1=39061;
                      T1CONbits.ON=1;
                   }
                   else{
                       state=SL1;
                   }
                  break;
        
              case SL2:
                   LATDbits.LATD0=0;
                   LATDbits.LATD1=1;
                   LATDbits.LATD2=0;
                   T1CONbits.ON=0;
                   forward=1;
                    if(PORTDbits.RD6==DOWN || PORTDbits.RD7==DOWN || PORTDbits.RD13==DOWN){
                       state=SBF;
                       TMR1=0;
                       PR1=39061;
                      T1CONbits.ON=1;
                   }
                   else{
                       state=SL2;
                   }
                  break;
        
              case SL3:
                   LATDbits.LATD0=0;
                   LATDbits.LATD1=0;
                   LATDbits.LATD2=1;
                   T1CONbits.ON=0;
                   forward=1;
                   if(PORTDbits.RD6==DOWN || PORTDbits.RD7==DOWN || PORTDbits.RD13==DOWN){
                       state=SBF;
                       TMR1=0;
                       PR1=39061;
                      T1CONbits.ON=1;
                   }
                   else{
                       state=SL3;
                   }
                  break;
        
              case SBF:
                   if(forward && (LATDbits.LATD0==1) && (PORTDbits.RD6==UP) && (PORTDbits.RD7==UP) && (PORTDbits.RD13==UP)){
                       state=SL2;
                   }
                   else if (forward && (LATDbits.LATD1==1) && (PORTDbits.RD6==UP) && (PORTDbits.RD7==UP) && (PORTDbits.RD13==UP)){
                       state=SL3;
                   }                  
                   else if (forward && (LATDbits.LATD2==1) && (PORTDbits.RD6==UP) && (PORTDbits.RD7==UP) && (PORTDbits.RD13==UP)){
                       state=SL1;
                   }
                   else if (!forward && (LATDbits.LATD0==1)&& (PORTDbits.RD6==UP) && (PORTDbits.RD7==UP) && (PORTDbits.RD13==UP)){
                       state=SL3;
                   }
                   else if (!forward && (LATDbits.LATD1==1)&& (PORTDbits.RD6==UP) && (PORTDbits.RD7==UP) && (PORTDbits.RD13==UP)){
                       state=SL1;
                   }                  
                   else if (!forward && (LATDbits.LATD2==1)&& (PORTDbits.RD6==UP) && (PORTDbits.RD7==UP) && (PORTDbits.RD13==UP)){
                       state=SL2;
                   }
                   else {
                       state=SBF;
                   } 
                  
                  break;
             /* case SBB:
                   if(!forward && (LATDbits.LATD0==1)&& (PORTDbits.RD6==UP)){
                       state=SL2;
                   }
                   else if (!forward && (LATDbits.LATD1==1)&& (PORTDbits.RD6==UP)){
                       state=SL3;
                   }                  
                   else if (!forward && (LATDbits.LATD2==1)&& (PORTDbits.RD6==UP)){
                       state=SL1;
                   } 
                   else {
                       state=SBB;
                   }
                  break;*/
              
              case InitState:
                   LATDbits.LATD0=0;
                   LATDbits.LATD1=0;
                   LATDbits.LATD2=0;
                   state=SL1;
                  break;
              default:
                   state=InitState;
                  break;
        
        }
        
    }
    
    return 0;
}

//TODO: Add interrupt service routines that manage the change of states
//for particular events as needed
void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt(){
    IFS0bits.T1IF=0; //put down interrupt flag
    T1CONbits.ON=0; //turn off timer
    TMR1=0;
    forward=0;
              
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(){
    IFS1bits.CNDIF=0;  //put down interrupt flag
    
    
}