/*
 * adc.h
 *
 *  Created on: 21 но€б. 2023 г.
 *      Author: vadym
 */

#ifndef ADC_H_
#define ADC_H_

#include <DSP2833x_Device.h>

void adc_vInitAdc(void);
float adc_vConvert(Uint16 chanel);
void adc1_interrupt(void (*InterruptHandlerAdc)(void));
float adc_r32getVoltage(float adc_3vVoltage, float koff, float invert);

#endif /* ADC_H_ */
