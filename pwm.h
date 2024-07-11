/*
 * pwm.h
 *
 *
 *      Author: vadym
 */

#ifndef PWM_H_
#define PWM_H_

#include <DSP2833x_Device.h>

void pwm_vInitPwm(Uint32 u32Frequency_hz, float u32percente_1, float u32precente_2);

void dead_band(Uint16 mode, Uint32 v32delay);

#endif /* PWM_H_ */
