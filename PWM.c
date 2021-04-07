/*
 * File:   PWM.c
 * Author: Jaime
 *
 * Created on April 7, 2021, 9:48 AM
 */


#include <xc.h>
#include "PWM.h"

void init_PWM_TMR2(void){            //USIING TIMER2
    //------------------------RC5 PWM out to BUZZER----------------------------
         
    BUZZER_TRIS = 1;       //SET PORT C5 TO INPUT
    RC5PPS = 0b01100;           //PPS FOR CCP1 TO RC5
    CCPTMRSbits.CCP1TSEL = 0b00; // CCP1 is based off of TIMER2 in PWM mode
    
    PR2 = red_tone;                   ////sets pwm period TO GET 25mS
    
    CCP1CONbits.MODE = 0b1100;  //SET CCP TO PWM MODE
    CCP1CONbits.FMT = 0;        //DUTY CYCLE ALIGNMENT TO THE RIGHT
    CCP1CONbits.EN =1;          //TURN ON
    
    CCPR1H = 0b00;              //MSB
    CCPR1L = tone_off;        //LSB
    
    PIR1bits.TMR2IF = 0;        //Disabling the interrupt flag of the timer 
    T2CONbits.CKPS = 0b111;     //pre scalar: 128
    T2CONbits.OUTPS = 0x0;      //post scalar
    T2CONbits.ON =1;            //SET TIMER2 ON BIT 
    T2CLKCONbits.CS = 0x0;      //select FOSC/4
    T2HLTbits.PSYNC = 1;
    T2HLTbits.T2CKSYNC =1;   
    T2HLTbits.MODE = 0b0000;
    
    while(PIR1bits.TMR2IF == 1 & TMR2 ==0){
        PIR1bits.TMR2IF = 0;
    }
    BUZZER_TRIS = 0;
}