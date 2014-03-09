#ifndef __AUTODRIVER__
#define __AUTODRIVER__

#include "sharedutils.h"

#define DRV_TIMER T3
#define MAX_TURN_TIME 3000
#define PAUSE_TIME 250

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

float getIRDir(tSensors link) {
    static float prevDir = 0.0; float currDir; int acS[5]; int idx;

    idx = HTIRS2readACDir(link); currDir = (float)idx;
    if (idx == 0) {
        currDir = prevDir;
    } else if (HTIRS2readAllACStrength(link, acS[0], acS[1], acS[2], acS[3], acS[4])) {
        idx = (idx - 1)/2;
        if ((idx < 4) && (acS[idx] != 0) && (acS[idx + 1] != 0)) {
            currDir += (float)(acS[idx + 1] - acS[idx]) / max(acS[idx], acS[idx + 1]);
        }
        nxtDisplayTextLine(0, "Idx=%d,Dir=%5.1f", idx, currDir);
        nxtDisplayTextLine(2, "S1=%d,S2=%d", acS[0], acS[1]);
        nxtDisplayTextLine(3, "S3=%d,S4=%d", acS[2], acS[3]);
        nxtDisplayTextLine(4, "S5=%d", acS[4]);
    }
    prevDir = currDir;
    return currDir;
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
		setLeftMotors (80.0*norm);
		setRightMotors(80.0*norm);
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
