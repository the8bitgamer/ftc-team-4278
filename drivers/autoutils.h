#ifndef __AUTODRIVER__
#define __AUTODRIVER__

#include "sharedutils.h"

#define DrTimer T3
#define SeTimer T2
#define MAX_TURN_TIME 3000
#define PAUSE_TIME 160

void pause() {wait1Msec(PAUSE_TIME);}
void pause(int n) {for(int i = 0; i < n; i++) pause();}
void estop() {StopAllTasks();}

int getEncoderByInches(float inches) {return floor((1440)*(abs(inches))/WHEELCIRC);}
float getInchesByEncoder(int encode) {return (((float)abs(encode))/360.0)*WHEELCIRC;}

void dumpArm() {
	setArmMotors(50);
	wait1Msec(1550);
	setArmMotors(0);
	wait1Msec(400);
	setArmMotors(-50);
	wait1Msec(1100);
	setArmMotors(0);
}

void lockdownRobot() {
	setLeftMotors(0);
	setRightMotors(0);
	setArmMotors(0);
	setSpinMotor(0);
	unlockArmMotors();
	while(true) wait1Msec(5);
}

void rbtMoveFdTime(float inches, int msec) {
	int enc = getEncoderByInches(inches); clearEncoders();
	int norm = -1.0*sgn(inches);
	ClearTimer(DrTimer);
	while(leftEncoder < enc && rightEncoder < enc) {
		if(time1[DrTimer] > msec) lockdownRobot();
		setLeftMotors (100*norm);
		setRightMotors(093*norm);
	}
	if(time1[DrTimer] > msec) lockdownRobot();
	setLeftMotors(0); setRightMotors(0);
}

void rbtArcLeft(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(-1*sgn(degs)*90);
	ClearTimer(DrTimer);
	while(leftEncoder < enc) if(time1[DrTimer] > MAX_TURN_TIME) lockdownRobot();
	setLeftMotors(0);
}

void rbtArcRight(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setRightMotors(sgn(degs)*60);
	ClearTimer(DrTimer);
	while(rightEncoder < enc) if(time1[DrTimer] > MAX_TURN_TIME) lockdownRobot();
	setRightMotors(0);
}

void rbtTurnRight(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors( -1*sgn(degs)*40);
	setRightMotors(sgn(degs)*30);
	ClearTimer(DrTimer);
	while(rightEncoder < enc) if(time1[DrTimer] > MAX_TURN_TIME) lockdownRobot();
	setLeftMotors(0); setRightMotors(0);
}

void rbtTurnLeft(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(sgn(degs)*60);
	setRightMotors(-1*sgn(degs)*60);
	ClearTimer(DrTimer);
	while(leftEncoder < enc) if(time1[DrTimer] > MAX_TURN_TIME) lockdownRobot();
	setLeftMotors(0); setRightMotors(0);
}

#endif //__AUTODRIVER__
