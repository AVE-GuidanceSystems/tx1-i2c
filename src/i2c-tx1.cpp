//============================================================================
// Name        : i2c-tx1.cpp
// Author      : Christian Aguilar
// Version     :
// Copyright   : @2017
// Description : Motor Test Script
//============================================================================

#include <iostream>
#include "drv2605.h"
#include "jetsonGPIO.h"

using namespace std;

DRV2605 motor[2] = {DRV2605(gpio38, 0), DRV2605(gpio187, 0)};
int main() {
	cout << "Begin Motor Test" << endl;	
	unsigned char effect = 47;
	
	while(1){
		cout << "Effect #" << (int)effect << endl;
		for(int i = 0; i < 2; i++){
			cout << "Motor #" << i << " is active!" << endl;
			motor[i].setTrigger(on);
			motor[i].setWaveform(0,effect);	//Run Effect #47
			motor[i].setWaveform(1,0);	//End waveform
			
			motor[i].go(); //play effect
			usleep(3000); 
			
			//deactivate motor trigger..move on to next motor
			motor[i].setTrigger(off);
			usleep(3000); 
		}
	}
}
