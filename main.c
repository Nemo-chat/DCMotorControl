#include "mcu.h"
#include "gipo.h"
#include "pwm.h"
#include "adc.h"
#include "dcmot.h"
#include "qep.h"

#define FREQ 10000

interrupt void interrupt_adc1(void);

float r32PositionAct = 0;
float r32PositionOld = 0;
float r32Speed = 0;
float r32Voltage =0;
float r32bufferSpeed[1000];
float r32Analog = 0;
float invert = 1;
float koff = 0.000;


int main()
{

     mcu_vInitMcuClocks(MCU_PLL_MULTIPLIER, MCU_PLL_DIVIDER, MCU_HIGH_SPEED_PRESCALE, MCU_LOW_SPEED_PRESCALE);
     gpio_vInitGpio();
     pwm_vInitPwm(FREQ, 0, 0);
     dead_band(2,0);
     adc_vInitAdc();
     DELAY_US(5000);
     adc1_interrupt(&interrupt_adc1);
     qep_vInitQep(QEP_ENC_PPR*RATIO-1,0);


     while (1){

         while(SB1_PRESSED && !SB2_PRESSED && koff<=12){
             DELAY_US(100000);

             if(!SB1_PRESSED){
                 koff = koff + 1.200;
             }
             if(koff>12) koff = 12;

         }

         while(SB2_PRESSED && !SB1_PRESSED && koff>=0){
             DELAY_US(100000);

             if(!SB2_PRESSED) koff = koff - 1.200;

         }

         while(SB1_PRESSED && SB2_PRESSED){
             DELAY_US(100000);
             if(!SB1_PRESSED && !SB1_PRESSED){
             invert = (-1)*invert;
             }
         }

        r16baragraph(r32Voltage, koff, invert);

    }

}

  interrupt void interrupt_adc1(void){

         static Uint16 Interrupt_counter = 0;
         static Uint32 i = 0;
         if(Interrupt_counter > 99) Interrupt_counter = 0;
         float Temp = 0;

         r32Analog = adc_vConvert(1);
         r32Voltage = adc_r32getVoltage(adc_vConvert(1), koff, invert);

         dcmot_v32Voltage(r32Voltage, FREQ);


         if(Interrupt_counter==99){

             r32PositionAct = qep_r32GetPosition();
             Temp = r32PositionAct - r32PositionOld;

             if(Temp<0 && EQep1Regs.QEPSTS.bit.QDF == 1){
                 Temp = Temp + 360.0;
             }
             else if(Temp>0 && EQep1Regs.QEPSTS.bit.QDF == 0){
                 Temp =  Temp - 360.0;
             }


             r32Speed = (Temp/(100/(float)FREQ))*60/360;

             r32bufferSpeed[i] = r32Speed;

             if(i>999) i = 0;
             else i++;

             r32PositionOld = r32PositionAct;
         }

         Interrupt_counter++;

         AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
         AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
         PieCtrlRegs.PIEACK.bit.ACK1 = 1;
     }


