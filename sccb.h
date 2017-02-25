/*
 * sccb.h
 *
 *  Created on: Feb 21, 2017
 *      Author: cdh
 */

#ifndef OV7670_SCCB_H_
#define OV7670_SCCB_H_

#include<stdint.h>
#include<inc/hw_memmap.h>


//Changeable parameters
#define SCCBCLOCKRATE 100000 //Hz

//TODO: Create clock signal for sccb
void initalizeSCCB(uint32_t gpioBaseClk, uint32_t gpioPinClk, uint32_t gpioBaseData, uint32_t gpioPinData);
void TimerAInterupt();

void sccbWrite(uint8_t information);
//void sccvRead();



typedef struct sccbCamContext
{
    uint32_t gpioClockPort;
    uint32_t gpioClockPin;
    uint32_t gpioDataPort;
    uint32_t gpioDataPin;
}sccbCamCtx;

#endif /* OV7670_SCCB_H_ */
