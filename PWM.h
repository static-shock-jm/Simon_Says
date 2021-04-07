/* 
 * File:   PWM.h
 * Author: Jaime
 *
 * Created on April 7, 2021, 9:48 AM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif
#include <stdint.h>
#define BUZZER_TRIS     TRISCbits.TRISC5
const uint8_t red_tone = 38;        //200Hz
const uint8_t blue_tone = 25;       //300Hz
const uint8_t yellow_tone = 18;     //400Hz
const uint8_t green_tone = 14;      //500Hz
const uint8_t test_tone = 6;        //1000Hz
const uint8_t duty_C_red = 78;      //duty cyle calculated for 50%
const uint8_t duty_C_blue = 52; 
const uint8_t duty_C_yellow = 39; 
const uint8_t duty_C_green = 31; 
const uint8_t duty_C_test = 15;
const uint8_t tone_off = 0;

const int led_Tone[4] = {red_tone, blue_tone, yellow_tone, green_tone};
const int d_Cycles[5] = {tone_off, duty_C_red, duty_C_blue, duty_C_yellow, duty_C_green};
void init_PWM_TMR2(void);

#endif	/* PWM_H */

