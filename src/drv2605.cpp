/*
 * drv2605.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: christian
 */

#include "drv2605.h"

using namespace std;

DRV2605::DRV2605(void){
	DRV2605::I2CBus = 1;
	//DRV2605::error = 0;
}
bool DRV2605::begin(){
  //Wire.begin(); //find suitable replacement
  unsigned char id = DRV2605::readRegister8(DRV2605_REG_STATUS);
  //cout << "Status 0x" << "id %h" << endl;  // Print Id to commandline

  DRV2605::writeRegister8(DRV2605_REG_MODE, 0x00); // out of standby

  DRV2605::writeRegister8(DRV2605_REG_RTPIN, 0x00); // no real-time-playback

  DRV2605::writeRegister8(DRV2605_REG_WAVESEQ1, 1); // strong click
  DRV2605::writeRegister8(DRV2605_REG_WAVESEQ2, 0);

  DRV2605::writeRegister8(DRV2605_REG_OVERDRIVE, 0); // no overdrive

  DRV2605::writeRegister8(DRV2605_REG_SUSTAINPOS, 0);
  DRV2605::writeRegister8(DRV2605_REG_SUSTAINNEG, 0);
  DRV2605::writeRegister8(DRV2605_REG_BREAK, 0);
  DRV2605::writeRegister8(DRV2605_REG_AUDIOMAX, 0x64);

  // Set as ERM Open Loop type. Adjust in main to make of type LRA

  // turn off N_ERM_LRA
  DRV2605::writeRegister8(DRV2605_REG_FEEDBACK, readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
  // turn on ERM_OPEN_LOOP
  DRV2605::writeRegister8(DRV2605_REG_CONTROL3, readRegister8(DRV2605_REG_CONTROL3) | 0x20);

  return true;
}

bool DRV2605::activateI2C(){
    char fileNameBuffer[32];
    sprintf(fileNameBuffer,"/dev/i2c-1");
    kI2CFileDescriptor = open(fileNameBuffer, O_RDWR);
    if (kI2CFileDescriptor < 0) {
        // Could not open the file
        error = errno ;
        return false ;
    }
    if (ioctl(kI2CFileDescriptor, I2C_SLAVE, DRV2605_ADDR) < 0) {
        // Could not open the device on the bus
        error = errno ;
        return false ;
    }
    return true ;
}

void DRV2605::deactivateI2C(){
	if (kI2CFileDescriptor > 0) {
		close(kI2CFileDescriptor);
		// WARNING - This is not quite right, need to check for error first
		kI2CFileDescriptor = -1 ;
	}
}

//Write and Read are only ones needing translation
void DRV2605::writeRegister8(char reg, char val){
	/*
		// use i2c
		Wire.beginTransmission(DRV2605_ADDR);
		Wire.write((byte)reg);
		Wire.write((byte)val);
		Wire.endTransmission();
	}


	// Allow users to use ERM motor or LRA motors
	 *
	 */
	 
	//Check Status of Bus
	int file;
	char filename[40];
    const gchar *buffer;
    
	sprintf(filename,"/dev/i2c-%d",I2CBus);
	if ((file = open(filename, O_RDWR)) < 0) {
		/* ERROR HANDLING: you can check errno to see what went wrong */
		perror("Failed to open the i2c bus");
		exit(1);
	}
	
	//Initiate Communication / Check for Errors
	if (ioctl(file, I2C_SLAVE, DRV2605_ADDR) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		/* ERROR HANDLING; you can check errno to see what went wrong */
		exit(1);
	}
	
	//Write Byte / Check for Errors
	if (write(file, &reg, 1) != 1) {
    /* ERROR HANDLING: i2c transaction failed */
    printf("Failed to write to the i2c bus.\n");
    buffer = g_strerror(errno);
    printf(buffer);
    printf("\n\n");
	}
	
	if (write(file, &val,1 ) != 1) {
    /* ERROR HANDLING: i2c transaction failed */
    printf("Failed to write to the i2c bus.\n");
    buffer = g_strerror(errno);
    printf(buffer);
    printf("\n\n");
	}

}
unsigned char DRV2605::readRegister8(unsigned char reg){
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
	int file;
	char filename[40];
    const gchar *buffer;
    
	//Check Status of Bus    
	sprintf(filename,"/dev/i2c-%d",I2CBus);
	if ((file = open(filename, O_RDWR)) < 0) {
		/* ERROR HANDLING: you can check errno to see what went wrong */
		perror("Failed to open the i2c bus");
		exit(1);
	}
	
	//Initiate Communication / Check for Errors
	if (ioctl(file, I2C_SLAVE, DRV2605_ADDR) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		/* ERROR HANDLING; you can check errno to see what went wrong */
		exit(1);
	}
	
	//Write Byte / Check for Errors
	if (write(file,&reg,1) != 1) {
    /* ERROR HANDLING: i2c transaction failed */
    printf("Failed to write to the i2c bus.\n");
    buffer = g_strerror(errno);
    printf(buffer);
    printf("\n\n");
	}		
    
    char buf = {0};
	char data;
	// Using I2C Read
	if (read(file,&buf,1) != 1) {	/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to read from the i2c bus.\n");
		buffer = g_strerror(errno);
		printf(buffer);
		printf("\n\n");
	} else {
		data = (char) buf;
		//~ data = data/4096*5;
		//~ channel = ((buf[0] & 0b00110000)>>4);
		//~ printf("Data:  %#02x\n",data);
	}
	return data;
}
void DRV2605::setWaveform(unsigned char slot, unsigned char w){

}

void DRV2605::selectLibrary(unsigned char lib){
	writeRegister8(DRV2605_REG_LIBRARY, lib);
}
void DRV2605::go(){
	writeRegister8(DRV2605_REG_GO, 1);
}
void DRV2605::stop(){
	writeRegister8(DRV2605_REG_GO, 0);
}

void DRV2605::setMode(unsigned char mode){
	writeRegister8(DRV2605_REG_MODE, mode);
}

void DRV2605::setRealtimeValue(unsigned char rtp){
	writeRegister8(DRV2605_REG_RTPIN, rtp);
}
// Select ERM (Eccentric Rotating Mass) or LRA (Linear Resonant Actuator) vibration motor
// The default is ERM, which is more common
void DRV2605::useERM(){
	writeRegister8(DRV2605_REG_FEEDBACK, readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
}
void DRV2605::useLRA(){
	writeRegister8(DRV2605_REG_FEEDBACK, readRegister8(DRV2605_REG_FEEDBACK) | 0x80);
}





