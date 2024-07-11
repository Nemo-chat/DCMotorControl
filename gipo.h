/*
 * gipo.h
 *
 *  Created on: 4 окт. 2023 г.
 *      Author: vadym
 */

#ifndef GIPO_H_
#define GIPO_H_

#include <DSP2833x_Device.h>

#define GPIO31_OFF GpioDataRegs.GPASET.bit.GPIO31 = 1
#define GPIO31_ON GpioDataRegs.GPACLEAR.bit.GPIO31 = 1
#define GPIO31_TOGGLE GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1
#define GPIO34_OFF GpioDataRegs.GPBSET.bit.GPIO34 = 1
#define GPIO34_ON GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1

#define SB1_PRESSED (GpioDataRegs.GPADAT.bit.GPIO12==0)
#define SB2_PRESSED (GpioDataRegs.GPADAT.bit.GPIO13==0)
#define SB3_PRESSED (GpioDataRegs.GPADAT.bit.GPIO14S==0)


void gpio_vInitGpio(void);
void r16baragraph(float voltage, float koff, int invert);

#endif /* GIPO_H_ */
