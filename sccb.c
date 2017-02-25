#include"sccb.h"

#include<stdlib.h>
#include<stdio.h>
#include<driverlib/timer.h>
#include<driverlib/gpio.h>
#include<inc/hw_sysctl.h>
#include<driverlib/sysctl.h>

struct sccbCamContext camera;

uint8_t data;
volatile int writting=0;
volatile int reading=0;

void saveCamera(uint32_t gpioBaseClk, uint32_t gpioPinClk, uint32_t gpioBaseData, uint32_t gpioPinData)
{
     camera.gpioClockPort = gpioBaseClk;
     camera.gpioClockPin = gpioPinClk;
     camera.gpioDataPort = gpioBaseData;
     camera.gpioDataPin = gpioPinData;
}

/*
 * initalizeSCCB(gpioBaseClk, gpioPinClk, gpioBaseData, gpioPinData)
 *  gpioBaseClk:   The base address of the gpio port to output the clock signal.
 *  gpioPinClk:    The pin MACRO for the selected gpio base clock signal.
 *  gpioBaseData:  The base address of the gpio port to output/input the data.
 *  gpioPinData:   The pin MACRO for the selected gpio base data signal.
 *
 * Description: Sets up the necessary gpio and starts the timers to clock the signal.
 */
void initalizeSCCB(uint32_t gpioBaseClk, uint32_t gpioPinClk, uint32_t gpioBaseData, uint32_t gpioPinData)
{
    saveCamera(gpioBaseClk, gpioPinClk, gpioBaseData, gpioPinData);
    if(gpioBaseClk==GPIO_PORTA_BASE) SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    else if(gpioBaseClk==GPIO_PORTB_BASE) SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    else if(gpioBaseClk==GPIO_PORTC_BASE) SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    else if(gpioBaseClk==GPIO_PORTD_BASE) SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    else if(gpioBaseClk==GPIO_PORTE_BASE) SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    else if(gpioBaseClk==GPIO_PORTF_BASE) SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    else
    {
        printf("Invalid GPIO port. Please specify correct GPIO port");
        return;
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, SysCtlClockGet()/(SCCBCLOCKRATE*2));
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

}

void sccbWrite(uint8_t information)
{
    writting=1;
    data=information;
    TimerEnable(TIMER1_BASE, TIMER_A);
    while(writting == 1);
}

void TimerAInterupt()
{
    static unsigned int bitCounter = 0;

    if((bitCounter%2) == 1)
    {
        //Toggle the clock signal
        if(bitCounter == 1) GPIOPinWrite(camera.gpioClockPort, camera.gpioClockPin, 1);
        else GPIOPinWrite(camera.gpioClockPort, camera.gpioClockPin, 0);
    }

    if((bitCounter % 4) == 0)
    {
        GPIOPinWrite(camera.gpioClockPort, camera.gpioClockPin, data & 0b1)
        data<<1;
    }

    if(writting==1 && bitCounter==27)
    {
        writting=0;

    }

}
