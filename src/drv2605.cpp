/*
 * drv2605.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: christian
 */

#include "drv2605.h"

using namespace drv2605;

drv2605::drv2605(){
	drv2605::kI2CBus = 1;
	drv2605::error = 0;
}
bool drv2605::begin(){
  //Wire.begin(); //find suitable replacement
  unsigned char id = readRegister8(DRV2605_REG_STATUS);
  //cout << "Status 0x" << "id %h" << endl;  // Print Id to commandline

  writeRegister8(DRV2605_REG_MODE, 0x00); // out of standby

  writeRegister8(DRV2605_REG_RTPIN, 0x00); // no real-time-playback

  writeRegister8(DRV2605_REG_WAVESEQ1, 1); // strong click
  writeRegister8(DRV2605_REG_WAVESEQ2, 0);

  writeRegister8(DRV2605_REG_OVERDRIVE, 0); // no overdrive

  writeRegister8(DRV2605_REG_SUSTAINPOS, 0);
  writeRegister8(DRV2605_REG_SUSTAINNEG, 0);
  writeRegister8(DRV2605_REG_BREAK, 0);
  writeRegister8(DRV2605_REG_AUDIOMAX, 0x64);

  // Set as ERM Open Loop type. Adjust in main to make of type LRA

  // turn off N_ERM_LRA
  writeRegister8(DRV2605_REG_FEEDBACK, readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
  // turn on ERM_OPEN_LOOP
  writeRegister8(DRV2605_REG_CONTROL3, readRegister8(DRV2605_REG_CONTROL3) | 0x20);

  return true;
}

//Write and Read are only ones needing translation
void drv2605::writeRegistar8(unsigned char reg, unsigned char val){
	/*
		// use i2c
		Wire.beginTransmission(DRV2605_ADDR);
		Wire.write((byte)reg);
		Wire.write((byte)val);
		Wire.endTransmission();
	}

	/****************/


	// Allow users to use ERM motor or LRA motors

}
unsigned char drv2605::readRegister(unsigned char reg){
	/*
	 *  uint8_t x ;
   // use i2c
    Wire.beginTransmission(DRV2605_ADDR);
    Wire.write((byte)reg);
    Wire.endTransmission();
    Wire.requestFrom((byte)DRV2605_ADDR, (byte)1);
    x = Wire.read();

  //  Serial.print("$"); Serial.print(reg, HEX);
  //  Serial.print(": 0x"); Serial.println(x, HEX);

  return x;
}
	 */

}
void drv2605::setWaveform(unsigned char slot, unsigned char w){
	writeRegister8(DRV2605_REG_LIBRARY, lib);
}

void sdrv2605::selectLibrary(unsigned char lib){

}
void drv2605::go(){
	writeRegister8(DRV2605_REG_GO, 1);
}
void drv2605::stop(){
	writeRegister8(DRV2605_REG_GO, 0);
}

void drv2605::setMode(unsigned char mode){
	writeRegister8(DRV2605_REG_MODE, mode);
}

void drv2605::setRealtimeValue(unsigned char rtp){
	writeRegister8(DRV2605_REG_RTPIN, rtp);
}
// Select ERM (Eccentric Rotating Mass) or LRA (Linear Resonant Actuator) vibration motor
// The default is ERM, which is more common
void drv2605::useERM(){
	writeRegister8(DRV2605_REG_FEEDBACK, readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
}
void drv2605::useLRA(){
	writeRegister8(DRV2605_REG_FEEDBACK, readRegister8(DRV2605_REG_FEEDBACK) | 0x80);
}





