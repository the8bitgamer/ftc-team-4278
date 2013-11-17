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

void rbtMoveFd(float inches) {
	int enc = getEncoderByInches(inches);
	clearEncoders();
	setLeftMotors(sgn(inches)*75);
	setRightMotors(sgn(inches)*75);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0); setRightMotors(0);
}

void rbtArcRight(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(sgn(degs)*55);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0);
}

void rbtArcLeft(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setRightMotors(sgn(degs)*55);
	while(rightEncoder < enc) wait1Msec(10);
	setRightMotors(0);
}

void rbtTurnRight(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(sgn(degs)*55);
	setRightMotors(-1*sgn(degs)*55);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0); setRightMotors(0);
}

void rbtTurnLeft(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(-1*sgn(degs)*55);
	setRightMotors(sgn(degs)*55);
	while(leftEncoder < enc) wait1Msec(10);
	setLeftMotors(0); setRightMotors(0);
}

#endif //__AUTODRIVER__
