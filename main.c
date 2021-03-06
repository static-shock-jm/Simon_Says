/*
 * File:   main.c
 * Author: Jaime
 * Description: 
 * Simon Says game with 4 button inputs, 4 LED outputs,
 * and optional buzzer.
 * 
 * Notes: 
 * Pin assignments:
 * RC0-RC3 -> button1-button4
 * RA2,RA4,RA5,RC4 -> LED1-LED4
 * RC5 -> BUZZER
 * 
 *
 * Created on July 23, 2020, 12:34 PM
 */
#include "pinConfig.h"
#include "HW_GPIO.h"
//#include "PWM.h"



#define RED_LED_TRIS    TRISCbits.TRISC0
#define BLUE_LED_TRIS   TRISCbits.TRISC1
#define YELLOW_LED_TRIS TRISCbits.TRISC2
#define GREEN_LED_TRIS  TRISAbits.TRISA4
             

#define RED_LED     PORTCbits.RC0
#define BLUE_LED    PORTCbits.RC1
#define YELLOW_LED  PORTCbits.RC2
#define GREEN_LED   PORTAbits.RA4

#define BTN1_TRIS    TRISAbits.TRISA2
#define BTN2_TRIS    TRISAbits.TRISA5
#define BTN3_TRIS    TRISCbits.TRISC3
#define BTN4_TRIS    TRISCbits.TRISC4

#define BTN1_PSH    PORTAbits.RA2
#define BTN2_PSH    PORTAbits.RA5
#define BTN3_PSH    PORTCbits.RC3
#define BTN4_PSH    PORTCbits.RC4

#define BTN1_IF IOCAF2
#define BTN2_IF IOCAF5
#define BTN3_IF IOCCF3
#define BTN4_IF IOCCF4

#define RED 0
#define BLUE 1
#define YELLOW 2
#define GREEN 3

//Timer delays
#define SHORT_DELAY 100
#define LONG_DELAY 800
#define DELAY 25000

#include <stdint.h>

int game[40];
int input =0;
/*
void init_game(){
    for(int i =0; i<40;i++){
        game[i] = rand()%4;
    }
}

void __interrupt() isr(void){
  
    if(BTN1_IF){
        TMR4 = 0;
        TMR2=0;
        PR2 = red_tone;
        CCPR1H = 0b00;              //MSB
        CCPR1L = duty_C_red;        //LSB
        T4CONbits.ON = 1;           //set timer 4 on
        //INTCONbits.INTE = 0;     //Disable external interrupt
        INTCONbits.IOCIE = 0;
        IOCAN2 = ~IOCAN2;
        IOCAP2 = ~IOCAP2;    
        RED_LED = ~RED_LED;
        if(RED_LED == 0){
            CCPR1H = 0b00;              //MSB
            CCPR1L = tone_off;        //LSB
            input = RED;
        }
            
        BTN1_IF = 0;
    }   
    else if(BTN2_IF){
        TMR4 = 0;
        TMR2=0;
        PR2 = blue_tone;
        CCPR1H = 0b00;              //MSB
        CCPR1L = duty_C_blue;        //LSB
        T4CONbits.ON = 1;           //set timer 4 on
        //INTCONbits.INTE = 0;     //Disable external interrupt
        INTCONbits.IOCIE = 0;
        IOCAN5 = ~IOCAN5;  //Falling edge IOCxN =1| Rising edge IOCxP =1
        IOCAP5 = ~IOCAP5;
        BLUE_LED = ~BLUE_LED;
        if(BLUE_LED == 0){
            CCPR1H = 0b00;              //MSB
            CCPR1L = tone_off;        //LSB
            input = BLUE;
        }
        BTN2_IF = 0;
    }
    else if(BTN3_IF){
        TMR4 = 0;
        TMR2=0;
        PR2 = yellow_tone;
        CCPR1H = 0b00;              //MSB
        CCPR1L = duty_C_yellow;        //LSB
        T4CONbits.ON = 1;           //set timer 4 on
        //INTCONbits.INTE = 0;     //Disable external interrupt
        INTCONbits.IOCIE = 0;
        IOCCN3 = ~IOCCN3;
        IOCCP3 = ~IOCCP3;
        YELLOW_LED = ~YELLOW_LED;
        if(YELLOW_LED == 0){
            CCPR1H = 0b00;              //MSB
            CCPR1L = tone_off;        //LSB
            input = YELLOW;
        }
        BTN3_IF = 0;
    }
    else if(BTN4_IF){
        TMR4 = 0;
        TMR2=0;
        PR2 = green_tone;
        CCPR1H = 0b00;              //MSB
        CCPR1L = duty_C_green;        //LSB
        T4CONbits.ON = 1;           //set timer 4 on
        //INTCONbits.INTE = 0;     //Disable external interrupt
        INTCONbits.IOCIE = 0;
        IOCCN4 = ~IOCCN4;
        IOCCP4 = ~IOCCP4;
        GREEN_LED = ~GREEN_LED;
        if(GREEN_LED ==0){
            CCPR1H = 0b00;              //MSB
            CCPR1L = tone_off;        //LSB
            input = GREEN;
            
        }
        BTN4_IF = 0;
    }
    else if(PIR2bits.TMR4IF){
        T4CONbits.ON = 0;           //set timer 4 off
        //INTCONbits.INTE = 1;     //Enable external interrupt
        INTCONbits.IOCIE = 1;
        PIR2bits.TMR4IF = 0;        //clear timer 4 interrupt
    }
     if(CLC1IF){
        TMR1 = 0;
        T1CONbits.TMR1ON = 1;        //TURN ON THE TIMER
        //PR2 = test_tone;
        //CCPR1H = 0b00;              //MSB
        //CCPR1L = duty_C_test;        //LSB
        //GREEN_LED = ~GREEN_LED;
        INTCONbits.IOCIE = 1;
        while(TMR1 < DELAY){
            
        }
        T1CONbits.TMR1ON = 0;        //TURN OFF THE TIMER
        //CCPR1H = 0b00;              //MSB
        //CCPR1L = tone_off;        //LSB
        CLC1IF =0;
    }
}

void init_peripheral(void){
    //Set LEDs as outputs 
    RED_LED_TRIS = 0;
    BLUE_LED_TRIS = 0;
    YELLOW_LED_TRIS = 0;
    GREEN_LED_TRIS = 0;
    
    RED_LED = 0;
    BLUE_LED = 0;
    YELLOW_LED = 0;
    GREEN_LED = 0;
    
    ANSELA = 0x00;
    ANSELC = 0x00;
    
    //Set Input buttons
    BTN1_TRIS = 1;
    BTN2_TRIS = 1;
    BTN3_TRIS = 1;
    BTN4_TRIS = 1;
    
    //Pull-up resistors
    nWPUEN = 0; //Cleared to enable individual pull-up enable
    
    WPUAbits.WPUA2 = 1;
    WPUAbits.WPUA4 = 1;
    WPUCbits.WPUC3 = 1;
    WPUCbits.WPUC4 = 1;
}

void init_debounce_TMR4(void){
    PIE2bits.TMR4IE = 1;    //Enable timer 4 interrupt when TMR4==PR4
    PIR2bits.TMR4IF = 0;    //Clear interrupt flag for timer 4
    T4CLKCONbits.CS = 0b0000;   // Select FOSC/4 as clock
    T4CONbits.CKPS = 0b111;     //Prescaler of 128
    T4CONbits.ON = 0;           //set timer 4 off
    T4HLTbits.PSYNC = 1;
    T4HLTbits.T4CKSYNC =1;   
    T4HLTbits.MODE = 0b0000;

    PR4 = 38;              //GIVES DELAY OF 10ms
    
    IOCAN2 =1;  //Falling edge IOCxN =1| Rising edge IOCxP =1
    IOCAP2 = 1;
    IOCAN5 =1;
    IOCAP5 = 1;
    IOCCN3 =1;
    IOCCP3 = 1;
    IOCCN4 =1;
    IOCCP4 = 1;
}

void init_delay_TMR1(void){
    //TIMER1 FOR DEBOUNCING*********************LATER ON, PERFECT
    T1CONbits.TMR1CS = 0b00;     //TIMER1 CLOCK SOURCE SELECT: FOSC/4
    T1CONbits.TMR1ON = 0;        //TURN OFF THE TIMER
    TMR1 = 0;
    T1CONbits.T1CKPS = 0b01;    //PRESCALAR: 2
}

void init_CLC1(void){
    //************************FROM MCC************************************
    CLC1CON = 0X92;
    CLC1GLS0 = 0X1;
    CLC1GLS1 = 0X4;
    CLC1GLS2 = 0X0;
    CLC1GLS3 = 0X0;
    CLC1POL = 0XC;
    CLC1SEL0 = 0X0;
    CLC1SEL1 = 0X1;
    CLC1SEL2 = 0X0;
    CLC1SEL3= 0X0;
    PIE3bits.CLC1IE = 1;
}
void doNothing(){
    //Do nothing
}
*/
void main(void) {
    OSCCONbits.IRCF = 0b1101;       //SET internal osc. frequency to 4MHz
    
    //Interrupt setup
    INTCONbits.GIE = 1;      //Global interrupt enable
    INTCONbits.IOCIE = 1;   //Interrupt on change enable: Allow individual ports to generate an interrupt 
    INTCONbits.PEIE = 1;   //Peripheral interrupt enable 
    INTCONbits.INTE = 0;     //DISABLE external interrupt     
    INTCONbits.INTF = 0;     //Reset interrupt flag
    Dio_Init(Dio_Config);
    
    /*init_peripheral();
    init_debounce_TMR4();
    init_PWM_TMR2();
    init_delay_TMR1();
    init_CLC1();*/

   //PWM OUT: DIFFERETN APPROACH 
    /*TRISCbits.TRISC5 =1; //setting C5 bit to disable 
    PWM3CON =0;
    RC5PPS = 0b01110;
    PR2 = 48;
   
    //PWM3DCHbits.DC = 0;
    //PWM3DCLbits.DC = 0;
    //PWM3DCHbits.DC = 0b00011000;
    //PWM3DCLbits.DC = 0b01;
    
    
    
    T2CONbits.ON = 1;
    T2CONbits.CKPS = 0b111;
    T2CONbits.OUTPS = 0x0;
    T2HLTbits.PSYNC = 1;
    T2HLTbits.T2CKSYNC =1;
    
    PWM3CONbits.EN =1;
    
    while(TMR2IF != 1){
        TMR2IF = 0;
    }
    
    TRISCbits.TRISC5 =0;
    
    PWM3CONbits.PWM3POL =1;
    PWM3DCHbits.DC = 0b00011000;
    PWM3DCLbits.DC = 0b01;*/

    //SETUP CLC FOR STARTING GAME
    /*
    CLC1CONbits.LC1EN = 0;  //CLEAR LCxEN BIT
    CLC1SEL0bits.LC1D1S = 0b000000; //select CLCIN0
    CLC1SEL1bits.LC1D2S = 0b000001; //SELECT CLCIN1
    CLC1SEL2bits.LC1D3S = 0x00;
    CLC1SEL3bits.LC1D4S = 0x00;
    //*****************GATE1**********************************************
    CLC1GLS0bits.LC1G1D1N = 1;  //SET CLC0IN INPUT AS INVERTED 
    CLC1GLS0bits.LC1G1D1T = 0;
    CLC1GLS0bits.LC1G1D2N = 0;  //set to zero for unconnected
    CLC1GLS0bits.LC1G1D2T = 0;
    CLC1GLS0bits.LC1G1D3N = 0;  //
    CLC1GLS0bits.LC1G1D3T = 0;
    CLC1GLS0bits.LC1G1D4N = 0;
    CLC1GLS0bits.LC1G1D4T = 0;
    CLC1POLbits.LC1G1POL= 0;     //output of the logic cell not inverted
    //*****************GATE2**********************************************
    CLC1GLS1bits.LC1G2D1N = 1;  //SET CLC1IN INPUT AS INVERTED
    CLC1GLS1bits.LC1G2D1T = 0;
    CLC1GLS1bits.LC1G2D2N = 0;  //set tp zero for unconnected
    CLC1GLS1bits.LC1G2D2T = 0;
    CLC1GLS1bits.LC1G2D3N = 0;  //set tp zero for unconnected
    CLC1GLS1bits.LC1G2D3T = 0;
    CLC1GLS1bits.LC1G2D4N = 0;  //set tp zero for unconnected
    CLC1GLS1bits.LC1G2D4T = 0;
    CLC1POLbits.LC1G2POL =0;   //output of the logic cell not inverted
    //***************GATE3**************************************************
    CLC1GLS2bits.LC1G3D1N = 0;
    CLC1GLS2bits.LC1G3D1T = 0;
    CLC1GLS2bits.LC1G3D2N = 0;
    CLC1GLS2bits.LC1G3D2T = 0;
    CLC1GLS2bits.LC1G3D3N = 0;
    CLC1GLS2bits.LC1G3D3T = 0;
    CLC1GLS2bits.LC1G3D4N = 0;
    CLC1GLS2bits.LC1G3D4T = 0;
    CLC1POLbits.LC1G3POL = 1;  //output of the logic inverted to create '1'
    //***************GATE4***************************************************
    CLC1GLS3bits.LC1G4D1N = 0;
    CLC1GLS3bits.LC1G4D1T = 0;
    CLC1GLS3bits.LC1G4D2N = 0;
    CLC1GLS3bits.LC1G4D2T = 0;
    CLC1GLS3bits.LC1G4D3N = 0;
    CLC1GLS3bits.LC1G4D3T = 0;
    CLC1GLS3bits.LC1G4D4N = 0;
    CLC1GLS3bits.LC1G4D4T = 0;
    CLC1POLbits.LC1G4POL = 1;  //output of the logic inverted to create '1'
    
    CLC1CONbits.MODE = 0b010;   //AND-OR
    
    CLC1POLbits.LC1POL = 0;     //OUTPUT OF THE LOGIC CELL IS NOT INVERTED
    
    CLC1CONbits.LC1INTP = 1;    //CLC1IF will be set on rising edge 
    PIE3bits.CLC1IE = 1;        //CLC 1 interrupt enable 
    CLC1CONbits.LC1EN = 1;         //ENABLE CLC1
    */
    
    while(1){
        
        
        //SLEEP();
        //YELLOW_LED = ~YELLOW_LED;
        
    }
    
}




