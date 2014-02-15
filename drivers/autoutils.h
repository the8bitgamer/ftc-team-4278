#ifndef __AUTODRIVER__
#define __AUTODRIVER__

#include "sharedutils.h"

#define DRV_TIMER T3
#define MAX_TURN_TIME 3000
#define PAUSE_TIME 160

void pause() {wait1Msec(PAUSE_TIME);}
void pause(int n) {for(int i = 0; i < n; i++) pause();}
void estop() {StopAllTasks();}

int getEncoderByInches(float inches) {return floor((1440)*(inches)/WHEELCIRC);}
float getInchesByEncoder(int encode) {return (((float)encode)/1440.0)*WHEELCIRC;}

void dumpArm() {
	//PlaySound(soundBlip);
	setArmMotors(50);
	wait1Msec(1550);

	//PlaySound(soundBlip);
	setArmMotors(0);
	wait1Msec(400);

	//PlaySound(soundBlip);
	setArmMotors(-50);
	wait1Msec(1100);

	//PlaySound(soundBeepBeep);
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

int rbtMoveToIR(int max, int timeout) {
	int dirIR, strIR; float stopRightEnc;
	HTIRS2readEnhanced(sensorIR, dirIR, strIR);
	clearEncoders();

	ClearTimer(DRV_TIMER);
	while(dirIR != 5 && rightEncoder < max) {
		HTIRS2readEnhanced(sensorIR, dirIR, strIR);
		stopRightEnc = rightEncoder;
		if(dirIR != 5) {setLeftMotors(40); setRightMotors(40);}
		if(time1[DRV_TIMER] > timeout) lockdownRobot();
	}
	setLeftMotors(0); setRightMotors(0); pause(3);
	return rightEncoder;
}

void rbtMoveFdDist(float inches, int msec) {
	clearEncoders();
	int enc = abs(getEncoderByInches(inches));
	int norm = 1.0*sgn(inches);
	ClearTimer(DRV_TIMER);
	int lEnc = leftEncoder; int rEnc = rightEncoder;
	while(abs(lEnc) < enc && abs(rEnc) < enc) {
		if(time1[DRV_TIMER] > msec) lockdownRobot();
		lEnc = leftEncoder; rEnc = rightEncoder;
		setLeftMotors (100.0*norm*LEFT_POW_DIFF);
		setRightMotors(100.0*norm*RIGHT_POW_DIFF);
	}
	if(time1[DRV_TIMER] > msec) lockdownRobot();
	setLeftMotors(0); setRightMotors(0); pause();
}
void rbtMoveFdEnc(int enc, int msec) {rbtMoveFdDist(getInchesByEncoder(enc), msec);}

void rbtArcLeft(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(-1*sgn(degs)*90);
	ClearTimer(DRV_TIMER);
	while(leftEncoder < enc) if(time1[DRV_TIMER] > MAX_TURN_TIME) lockdownRobot();
	setLeftMotors(0); pause();
}

void rbtArcRight(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setRightMotors(sgn(degs)*60);
	ClearTimer(DRV_TIMER);
	while(rightEncoder < enc) if(time1[DRV_TIMER] > MAX_TURN_TIME) lockdownRobot();
	setRightMotors(0); pause();
}

void rbtTurnRight(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors( -1*sgn(degs)*40);
	setRightMotors(sgn(degs)*30);
	ClearTimer(DRV_TIMER);
	while(rightEncoder < enc) if(time1[DRV_TIMER] > MAX_TURN_TIME) lockdownRobot();
	setLeftMotors(0); setRightMotors(0); pause();
}

void rbtTurnLeft(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(sgn(degs)*60);
	setRightMotors(-1*sgn(degs)*60);
	ClearTimer(DRV_TIMER);
	while(leftEncoder < enc) if(time1[DRV_TIMER] > MAX_TURN_TIME) lockdownRobot();
	setLeftMotors(0); setRightMotors(0); pause();
}

#endif //__AUTODRIVER__
