/*
 * adc.c
 *
 *  Created on:
 *      Author: vadym
 */


#include "adc.h"


void adc_vInitAdc(void){

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1; // zap. hod. clock pre ADC

    //ADC_cal(); // kalibracia

    SysCtrlRegs.HISPCP.bit.HSPCLK = 3; // delicka pre sysclkout 25MHz
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 0;
    AdcRegs.ADCTRL1.bit.CPS = 0;
    EDIS;

    AdcRegs.ADCTRL1.bit.ACQ_PS = 16; // Acquisition prescaler (3+1)*(1/25 000 000)
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 0; // Dual sequencer mode

    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1; // Povolenie startu od PWM SOCA

    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1; // Povolenie na prerusenie v konce konverzii SEQ1

    AdcRegs.ADCTRL3.bit.SMODE_SEL = 1; // Simultanne konverzie
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0; // 1 konveriza
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0; //ADCNIA0 - ADCNIB0
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
    AdcRegs.ADCTRL3.all |= 0x00E0; // turn ON ad prevodnik and reference voltage

}

float adc_vConvert(Uint16 chanel){
    if(chanel==1){
        float x = (3*AdcMirror.ADCRESULT0)/(4096.0);
        if (x<0.042) x = 0;
        return x;
    }
    else if(chanel==2) {
        return (3*AdcMirror.ADCRESULT1)/(4096.0);
    }
    return 0;
}

float adc_r32getVoltage(float adc_3vVoltage, float koff, float invert){
    float voltage =0;
    voltage = invert*(12 + (-1)*koff)*(2.836-adc_3vVoltage)/2.836;
    if(labs(voltage) < 0.01) voltage =0;
    return voltage;
}

void adc1_interrupt(void (*InterruptHandlerAdc)(void)){
    DINT;

    IFR = 0x0000; // clear flags on CPU level
    PieCtrlRegs.PIEACK.bit.ACK1 = 1; // clear flags

    EALLOW;
    PieVectTable.SEQ1INT = InterruptHandlerAdc;
    EDIS;


    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // enable interrupt by timer0
    //PieCtrlRegs.PIEIFR1.bit.INTx1 = 0;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1; // enable general interrupt
    IER|=0x01;

    EINT;
}
