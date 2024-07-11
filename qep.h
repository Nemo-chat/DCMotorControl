/*
 * qep.h
 *
 *  Created on:
 *      Author: vadym
 */

#ifndef QEP_H_
#define QEP_H_

#define QEP_ENC_PPR 16
#define RATIO 30

#include <DSP2833x_Device.h>

float qep_r32GetPosition(void);
void qep_vInitQep(Uint16 u16EncPPR,Uint16 u16Swap);

#endif /* QEP_H_ */
