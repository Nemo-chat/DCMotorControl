/*
 * qep.c
 *
 *  Created on:
 *      Author: vadym
 */

#include "qep.h"

void qep_vInitQep(Uint16 u16EncPPR,Uint16 u16Swap){

    EALLOW;
    SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1; // A
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1; // B
    EDIS;

    EQep1Regs.QDECCTL.bit.QSRC = 0; // quadrature mode

    if(u16Swap>=1)
        EQep1Regs.QDECCTL.bit.SWAP = 1;
        else
        EQep1Regs.QDECCTL.bit.SWAP = 0;


    EQep1Regs.QEPCTL.bit.FREE_SOFT=3;
    EQep1Regs.QEPCTL.bit.PCRM = 1; // reset on maximum
    EQep1Regs.QEPCTL.bit.QPEN =1; // enable counter
    EQep1Regs.QPOSMAX = u16EncPPR*4;

   // EQep1Regs.QEPCTL.bit.QCLM = 1
}

float qep_r32GetPosition(){
    float r32Position = 0;
    r32Position = (float) EQep1Regs.QPOSCNT / EQep1Regs.QPOSMAX*360;
    return r32Position;
}


