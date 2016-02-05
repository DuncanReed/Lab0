#include <xc.h>
#include "led.h"
#define OUTPUT 0
#define INPUT 1

//test proves this init enables the CN and uses the correct switch.
//odd behavior of device due to bouncing?
//use state machine to program entire state machine (pencil)

void initSwitch(){
    //TODO initialize switch as input, enable interrupt, set flag down
    TRISDbits.TRISD6=INPUT; //enable pin RD6 as an input signal
    CNENDbits.CNIED6=1; //Enable change notification for PORTD  RD6
    CNPUDbits.CNPUD6=1;  //enable pull up resistor for RD6
    
    TRISDbits.TRISD7=INPUT; //enable pin RD7 as an input signal
    CNENDbits.CNIED7=1; //Enable change notification for PORTD RD7 
    CNPUDbits.CNPUD7=1;  //enable pull up resistor for RD7
    
    TRISDbits.TRISD13=INPUT; //enable pin RD13 as an input signal
    CNENDbits.CNIED13=1; //Enable change notification for PORTD 
    CNPUDbits.CNPUD13=1;  //enable pull up resistor for RD13
    
    CNCONDbits.ON=1; //turn on (1) change notifications for PORTD
    IFS1bits.CNDIF=0;  //put down PORTD interrupt flag
    IPC8bits.CNIP=3;  //configure interrupt priority
    IEC1bits.CNDIE=0;  //enable interrupt for D pin change notifications
    
    
}
