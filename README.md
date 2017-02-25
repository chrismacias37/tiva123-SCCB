##Tiva Serial Camera Control Bus (SCCB)
The library allows communication with any OmniVision camera from the Tiva123 (Currently on the tiva launchpad). SCCB is almost like i2c but it does not support the ackowledgment bit therfore we cannot use i2c for this device. This library uses bitbanging to generate the required signal. 
It is written for use in CodeComposer Studio but can be complied using the supplied makefile.

###Requirements:
* [Tivaware's driver library](http://www.ti.com/tool/SW-TM4C)
 *  If you're developing on linux, you can install it on windows and copy over the files to linux.
* Tiva
 * At least one timer, two available gpio pins, and a gpio interupt 
