/* 
 * File:   Buttons.h
 * Author: Jaime
 *
 * Created on April 9, 2021, 5:00 PM
 */

#ifndef HW_GPIO_H
#define	HW_GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#define NUM_PORTS 2
#define NUM_PINS_PER_PORT 6
#define NUM_DIGITAL_PINS 4


typedef struct {
    uint8_t Channel;
    uint8_t PinType;
    uint8_t Direction;
    uint8_t Data;
    uint8_t Function;
}Dio_ConfigType;

typedef enum 
{
    PORTA_0, PORTA_1, LED_RED, PORTA_3, 
            LED_BLUE, LED_GREEN
}Dio_ChannelTypeA;

typedef enum 
{
    LED_YELLOW, PORTC_1, PORTC_2, PORTC_3, 
            PORTC_4, PORTC_5 
}Dio_ChannelTypeC;

typedef enum 
{
    ANALOG, DIGITAL
    
}Dio_PinType;

typedef enum 
{
    INPUT, OUTPUT
    
}Dio_Direction;

typedef enum
{
    LOW, HIGH
}Dio_Data;
typedef enum
{
    GPIO, SPI, I2C, PWM
    
}Dio_Function;

const Dio_ConfigType Dio_Config[] = 
{
    //Setup PORTA2, PORTA4, PORTA5
    {LED_RED, DIGITAL, OUTPUT, HIGH, GPIO},
    {LED_BLUE, DIGITAL, OUTPUT, HIGH, GPIO},
    {LED_GREEN, DIGITAL, OUTPUT, HIGH, GPIO},
    {LED_YELLOW, DIGITAL, OUTPUT, HIGH, GPIO}
};

uint16_t volatile * const portsin[NUM_PORTS] =  
{
    (uint16_t*)&PORTA, (uint16_t*)&PORTC
};

uint16_t volatile * const portddr[NUM_PORTS] = 
{
    (uint16_t*)&TRISA, (uint16_t*)&TRISC
};

uint16_t volatile * const ports[NUM_PORTS] = 
{
    (uint16_t*)&LATA, (uint16_t*)&LATC
};

const uint16_t pins[NUM_PINS_PER_PORT] =
{
    (1UL<<0),(1UL<<1),(1UL<<2),(1UL<<3),(1UL<<4),(1UL<<5)
};

void Dio_Init(const Dio_ConfigType * Config);
 


#endif	/* HW_GPIO_H */

