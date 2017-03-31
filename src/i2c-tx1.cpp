//============================================================================
// Name        : i2c-tx1.cpp
// Author      : Christian Aguilar
// Version     :
// Copyright   : @2017
// Description : Motor Test Script
//============================================================================

#include <iostream>
#include "drv2605.h"
using namespace std;

drv2605 drv;

int main() {
    drv.begin();
    drv.selectLibrary(1);
    drv.setMode(DRV2605_MODE_INTTRIG);
    
    
    while(1){
        drv.setWaveform(0, 47); //selects specified waveform
        drv.setWaveform(1,0);   //ends waveform
        drv.go();               //starts effect
        
        usleep(500);     //milliseconds
        
        
    }//while
    
	return 0;
}
