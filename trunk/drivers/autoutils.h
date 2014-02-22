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
	int stopRightEnc,dir1, dir2, dir3, dir4, dir5, lowThresh2 = 0, lowThresh = 0, peak = -1000, peak2 = -1000;
	for(int i=0;i<15;i++){
		HTIRS2readAllACStrength(sensorIR, dir1, dir2, dir3, dir4, dir5);
		lowThresh += dir3;
		lowThresh2 += dir2;
		wait1Msec(10);
	}lowThresh /= 15; lowThresh2 /= 15;
	clearEncoders();
	ClearTimer(DRV_TIMER);
	peak = dir3-lowThresh;
	peak2 = dir2-lowThresh2;
	do {
		if(peak<dir3-lowThresh)peak = dir3-lowThresh;
		if(peak2<dir2-lowThresh)peak2 = dir2-lowThresh;
		HTIRS2readAllACStrength(sensorIR, dir1, dir2, dir3, dir4, dir5);
		stopRightEnc = rightEncoder;
		if(dir3 <= dir2*(0.3) || peak <= 85) {setLeftMotors(20); setRightMotors(20);}
		if(time1[DRV_TIMER] > timeout) lockdownRobot();
		nxtDisplayTextLine(1, "DIR1: %d", dir1);
		nxtDisplayTextLine(2, "DIR2: %d", dir2);
		nxtDisplayTextLine(3, "DIR3: %d", dir3-lowThresh);
		nxtDisplayTextLine(4, "DIR4: %d", dir4);
		nxtDisplayTextLine(5, "DIR5: %d", dir5);
		nxtDisplayTextLine(6, "Peak: %d", peak);
		nxtDisplayTextLine(7, "Peak2: %d", peak2);
	}while(dir3 <= dir2*(0.3) || peak <= 85);//&& rightEncoder < max);
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
