/*
 * File:   Buttons.c
 * Author: Jaime
 * Description: 
 * Library for setting up buttons on an 8-bit PIC 
 * microcontroller.
 * 
 * Notes: 
 * PIC16F1614 only has PORTA and PORTC, care must taken when using
 * header to appropriately assign the buttons. 
 *
 * Created on April 9, 2021, 5:01 PM
 */

#include "HW_GPIO.h"
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>


void Dio_Init(const Dio_ConfigType * Config)
{
    uint8_t i = 0;
    uint8_t number = 0;
    uint8_t position = 0;
    
    for(i = 0; i < NUM_DIGITAL_PINS; i++ )
    {
        number = Config[i].Channel / NUM_PINS_PER_PORT;
        position = Config[i].Channel % NUM_PINS_PER_PORT;
        
        if(Config[i].PinType == ANALOG)
        {
            ANSELA |= pins[position];
        }
        else if(Config[i].PinType == DIGITAL)
        {
            ANSELA &= ~pins[position];
        }
        
        if (Config[i].Data == HIGH)
        {
            *ports[number] |= pins[position];
        }
        else
        {
            *ports[number] &= ~pins[position];
        }
        
        if (Config[i].Direction == OUTPUT)
        {
            *portddr[number] &= ~pins[position];
        }
        else 
        {
            *portddr[number] |= pins[position];
        }
        
    }
    
}