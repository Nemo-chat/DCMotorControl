/*
 * dcmot.c
 *
 *  Created on: 22 но€б. 2023 г.
 *      Author: vadym
 */

#include "dcmot.h"


void dcmot_v32Voltage(float voltage, Uint32 u32Frequency_hz){


    float change = ((voltage + 12)/(2*12))*(150000000/(1*1*2*u32Frequency_hz));

    EPwm1Regs.CMPA.half.CMPA = (int)change;

}



