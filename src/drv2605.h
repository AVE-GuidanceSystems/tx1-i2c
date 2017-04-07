/*
 * drv2605.h
 *
 *  Created on: Mar 21, 2017
 *      Author: christian
 */

#ifndef DRV2605_H_
#define DRV2605_H_

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/types.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include "jetsonGPIO.h"


#define DRV2605_ADDR 0x5A

#define DRV2605_REG_STATUS 			0x00
#define DRV2605_REG_MODE 			0x01
#define DRV2605_MODE_INTTRIG  		0x00
#define DRV2605_MODE_EXTTRIGEDGE  	0x01
#define DRV2605_MODE_EXTTRIGLVL  	0x02
#define DRV2605_MODE_PWMANALOG  	0x03
#define DRV2605_MODE_AUDIOVIBE  	0x04
#define DRV2605_MODE_REALTIME  		0x05
#define DRV2605_MODE_DIAGNOS  		0x06
#define DRV2605_MODE_AUTOCAL  		0x07


#define DRV2605_REG_RTPIN 			0x02
#define DRV2605_REG_LIBRARY 		0x03
#define DRV2605_REG_WAVESEQ1 		0x04
#define DRV2605_REG_WAVESEQ2 		0x05
#define DRV2605_REG_WAVESEQ3 		0x06
#define DRV2605_REG_WAVESEQ4 		0x07
#define DRV2605_REG_WAVESEQ5 		0x08
#define DRV2605_REG_WAVESEQ6 		0x09
#define DRV2605_REG_WAVESEQ7 		0x0A
#define DRV2605_REG_WAVESEQ8 		0x0B

#define DRV2605_REG_GO 				0x0C
#define DRV2605_REG_OVERDRIVE 		0x0D
#define DRV2605_REG_SUSTAINPOS 		0x0E
#define DRV2605_REG_SUSTAINNEG 		0x0F
#define DRV2605_REG_BREAK 			0x10
#define DRV2605_REG_AUDIOCTRL 		0x11
#define DRV2605_REG_AUDIOLVL 		0x12
#define DRV2605_REG_AUDIOMAX 		0x13
#define DRV2605_REG_RATEDV 			0x16
#define DRV2605_REG_CLAMPV 			0x17
#define DRV2605_REG_AUTOCALCOMP 	0x18
#define DRV2605_REG_AUTOCALEMP	 	0x19
#define DRV2605_REG_FEEDBACK 		0x1A
#define DRV2605_REG_CONTROL1 		0x1B
#define DRV2605_REG_CONTROL2 		0x1C
#define DRV2605_REG_CONTROL3 		0x1D
#define DRV2605_REG_CONTROL4 		0x1E
#define DRV2605_REG_VBAT 			0x21
#define DRV2605_REG_LRARESON 		0x22

class DRV2605 {
public:
	unsigned char I2CBus;         // I2C bus of the Lidar-Lite
	int I2CFileDescriptor;        // File Descriptor
	int error;
	jetsonGPIO trigger;

	DRV2605(jetsonGPIO, int);
	bool begin(void);
	bool activateI2C(void);
	void deactivateI2C(void);

	char readRegister8(__u8 reg);
	void writeRegister8(__u8 reg, __u8 val);

	void setWaveform(unsigned char slot, unsigned char w);
	void selectLibrary(unsigned char lib);
	void go(void);
	void stop(void);
	void setMode(unsigned char mode);
	void setRealtimeValue(unsigned char rtp);
	void setTrigger(pinValue);

	void useERM();
	void useLRA();

};

#endif /* DRV2605_H_ */
