#ifndef __AUTODRIVER__
#define __AUTODRIVER__
#include "sharedutils.h"

void lockdownRobot() {
	setLeftMotors(0);
	setRightMotors(0);
	setArmMotors(0);
	setSpinMotor(0);
	while(true) wait1Msec(5);
}

int getEncoderByInches(float inches) {return floor((1440)*(abs(inches))/WHEELCIRC);}
float getInchesByEncoder(int encode) {return (((float)abs(encode))/360.0)*WHEELCIRC;}

float lastLEnc = 0; float lastREnc = 0; float dt = 0;
float lastLEVel = 0; float lastREVel = 0;
float iLEVel = 0; float iREVel = 0;
float kPL = 0.5; float kPR = 0.5; float kDL = 0.0; float kDR = 0.0; float kIL = 0.0; float kIR = 0.0;
void resetPID() {lastLEnc = 0; lastREnc = 0; dt = 0; lastLEVel = 0; lastREVel = 0; iLEVel = 0; iREVel = 0; clearEncoders();}
void pidStep(float vLeft, float vRight) {

}

#endif //__AUTODRIVER__
