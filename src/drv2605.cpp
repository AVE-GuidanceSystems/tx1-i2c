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

}

void drv2605::writeRegistar8(unsigned char reg, unsigned char val){

}
void setWaveform(unsigned char slot, unsigned char w){

}

void selectLibrary(unsigned char lib){

}
void go(){

}
void stop(){

}

void setMode(unsigned char mode){

}

void setRealtimeValue(unsigned char rtp){

}
// Select ERM (Eccentric Rotating Mass) or LRA (Linear Resonant Actuator) vibration motor
// The default is ERM, which is more common
void useERM(){

}
void useLRA(){

}





