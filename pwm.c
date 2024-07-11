/*
 * pwm.c
 *
 *
 */

#include "pwm.h"

void pwm_vInitPwm(Uint32 u32Frequency_hz, float u32percente_1, float u32percente_2){

   EALLOW;
   SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1; // input clock enable ePWM1

   EDIS;

   float percente = 0;
   // Time base
   EPwm1Regs.TBPRD = 150000000/(1*1*2*u32Frequency_hz);
   EPwm1Regs.TBCTL.bit.CTRMODE = 2; // up down count mode
   EPwm1Regs.TBCTL.bit.CLKDIV = 0; //
   EPwm1Regs.TBCTL.bit.HSPCLKDIV =0;//
   EPwm1Regs.TBCTL.bit.FREE_SOFT = 3; // free run

   // Action qualifier
   EPwm1Regs.AQCTLA.bit.CAU = 1;// Action when TBCTR = CMPA and increment
   EPwm1Regs.AQCTLA.bit.CAD = 2;

   // Event trigger
   EPwm1Regs.ETSEL.bit.SOCASEL = 1; // when CTR = 0
   EPwm1Regs.ETSEL.bit.SOCAEN = 1;  // enable
   EPwm1Regs.ETPS.bit.SOCAPRD = 1; // generuje pulz pri prvej udalosti

   // Counter Compare
   percente = (u32percente_1/100)*(150000000/(1*1*2*u32Frequency_hz));

   EPwm1Regs.CMPA.half.CMPA = (int)percente;

   EALLOW;
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1; // synch. ePWM
   EDIS;
}



void dead_band(Uint16 mode, Uint32 v32delay){
    EPwm1Regs.DBCTL.bit.IN_MODE = 0;
    EPwm1Regs.DBCTL.bit.POLSEL = mode;
    EPwm1Regs.DBCTL.bit.OUT_MODE = 3;
    EPwm1Regs.DBFED = v32delay;
    EPwm1Regs.DBRED = v32delay;
}
