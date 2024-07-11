/*
 * gipo.c
 *
 *  Created on: 4 oct. 2023 r.
 *      Author: vadym
 */

 #include "gipo.h"

void gpio_vInitGpio(void){

    //SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;

    EALLOW;

    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;

    // Pin output
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; // output ePWM1A

    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1; // output ePWM1B

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1; // pin output

    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1; // pin output

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;  // pin output

    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;  // pin output

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;  // pin output

    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;  // pin output

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;  // pin output

    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;  // pin output

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;  // pin output

    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;  // pin output

    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;  // enable pull-up
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;  // pin input


    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;  // enable pull-up
    GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;  // pin input

    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;  // enable pull-up
    GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;  // pin input



    EDIS;

    GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
    GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;

}


void r16baragraph(float voltage, float koff, int invert){

       Uint16 i =2;
       Uint16 b =0;
       Uint16 p =0;
       float buffVoltage = voltage;


       if(invert > 0){
       while (buffVoltage>0){
           buffVoltage = buffVoltage - ((12+(-1)*koff))/10.0;
           //if(buffVoltage > 0)
               p++;

       }
       }

       else if (invert<0){

           while(buffVoltage<0){
               buffVoltage += ((12+(-1)*koff))/10.0;
              // if (buffVoltage<0)
                   p++;
           }
       }


       while(p>0){
           GpioDataRegs.GPASET.all |= (0x0001<<i);
           p--;
           i++;
       }

       for(b=i; b<12; b++){
           GpioDataRegs.GPACLEAR.all |= (0x0001<<b);
       }

}

