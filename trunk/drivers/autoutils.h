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
float getInchesByEncoder(float encode) {return ((float)encode/1440.0)*WHEELCIRC;}

void lockdownRobot() {
	PlaySound(soundException);
	setLeftMotors(0);
	setRightMotors(0);
	while(true) wait1Msec(5);
}

float getIRDir(tSensors link) {
    static float prevDir = 0.0; float currDir; int acS[5]; int idx;

    idx = HTIRS2readACDir(link); currDir = (float)idx;
    if (idx == 0) {
        currDir = 0;
    } else if (HTIRS2readAllACStrength(link, acS[0], acS[1], acS[2], acS[3], acS[4])) {
        idx = (idx - 1)/2;
        if ((idx < 4) && (acS[idx] != 0) && (acS[idx + 1] != 0)) {
            currDir += (float)(acS[idx + 1] - acS[idx]) / max(acS[idx], acS[idx + 1]);
        }
    }
    HTIRS2readAllACStrength(link, acS[0], acS[1], acS[2], acS[3], acS[4]);
    nxtDisplayTextLine(0, "Idx=%d,Dir=%5.1f", idx, currDir);
    nxtDisplayTextLine(2, "S1=%d,S2=%d", acS[0], acS[1]);
    nxtDisplayTextLine(3, "S3=%d,S4=%d", acS[2], acS[3]);
    nxtDisplayTextLine(4, "S5=%d", acS[4]);
    prevDir = currDir;
    return currDir;
}

//int rbtMoveToIR(int max, int timeout) {
//	int stopRightEnc,dir1, dir2, dir3, dir4, dir5, lowThresh2 = 0, lowThresh = 0, peak = -1000, peak2 = -1000;
//	for(int i=0;i<15;i++){
//		HTIRS2readAllACStrength(sensorIR, dir1, dir2, dir3, dir4, dir5);
//		lowThresh += dir3;
//		lowThresh2 += dir2;
//		wait1Msec(10);
//	}lowThresh /= 15; lowThresh2 /= 15;
//	//clearEncoders();
//	ClearTimer(DRV_TIMER);
//	peak = dir3-lowThresh;
//	peak2 = dir2-lowThresh2;
//	do {
//		if(peak<dir3-lowThresh)peak = dir3-lowThresh;
//		if(peak2<dir2-lowThresh)peak2 = dir2-lowThresh;
//		HTIRS2readAllACStrength(sensorIR, dir1, dir2, dir3, dir4, dir5);
//		stopRightEnc = rightEncoder;
//		if(dir3 <= dir2*(0.3) || peak <= 85) {setLeftMotors(20); setRightMotors(20);}
//		if(time1[DRV_TIMER] > timeout) lockdownRobot();
//		nxtDisplayTextLine(1, "DIR1: %d", dir1);
//		nxtDisplayTextLine(2, "DIR2: %d", dir2);
//		nxtDisplayTextLine(3, "DIR3: %d", dir3-lowThresh);
//		nxtDisplayTextLine(4, "DIR4: %d", dir4);
//		nxtDisplayTextLine(5, "DIR5: %d", dir5);
//		nxtDisplayTextLine(6, "Peak: %d", peak);
//		nxtDisplayTextLine(7, "Peak2: %d", peak2);
//	}while(dir3 <= dir2*(0.3) || peak <= 85);//&& rightEncoder < max);
//	setLeftMotors(0); setRightMotors(0); pause(3);
//	return rightEncoder;
//}

void rbtMoveFdDist(float inches, int msec) {
	clearEncoders();
	int enc = abs(getEncoderByInches(inches));
	int norm = 1.0*sgn(inches);
	ClearTimer(DRV_TIMER);

	while(leftEncoder < enc && rightEncoder < enc) {
		if(time1[DRV_TIMER] > msec) lockdownRobot();
		setLeftMotors (20.0*norm*LEFT_POW_DIFF);
		setRightMotors(20.0*norm*RIGHT_POW_DIFF);
	}
	setLeftMotors(0); setRightMotors(0); pause();
}

bool rbtMoveFdDistErr(float inches, int msec) {
	clearEncoders();
	int enc = abs(getEncoderByInches(inches));
	int norm = 1.0*sgn(inches);
	ClearTimer(DRV_TIMER);

	while(leftEncoder < enc && rightEncoder < enc) {
		if(time1[DRV_TIMER] > msec) return false;
		setLeftMotors (20.0*norm*LEFT_POW_DIFF);
		setRightMotors(20.0*norm*RIGHT_POW_DIFF);
	}
	setLeftMotors(0); setRightMotors(0); pause();

	return true;
}

void rbtMoveFdDist(float pw, float inches, int msec) {
	clearEncoders();
	int enc = abs(getEncoderByInches(inches));
	int norm = 1.0*sgn(inches);
	ClearTimer(DRV_TIMER);

	while(leftEncoder < enc && rightEncoder < enc) {
		if(time1[DRV_TIMER] > msec) lockdownRobot();
		setLeftMotors (pw*norm*LEFT_POW_DIFF);
		setRightMotors(pw*norm*RIGHT_POW_DIFF);
	}
	setLeftMotors(0); setRightMotors(0); pause();
}

void rbtMoveFdEnc(int enc, int msec) {rbtMoveFdDist(getInchesByEncoder(enc), msec);}

void rbtArcLeft(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(-1*sgn(degs)*60);
	ClearTimer(DRV_TIMER);
	while(leftEncoder < enc) if(time1[DRV_TIMER] > MAX_TURN_TIME) lockdownRobot();
	setLeftMotors(0); pause();
}

void rbtArcRight(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setRightMotors(sgn(degs)*40);
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

int rbtMoveToIR(int timeout) {
	float r0 = getIRDir(sensorIR)-8, r1; bool i = true;
	if(r0 > 0){ rbtArcRight(-7); rbtMoveFdDist(-10, 5000);}
	else 			{ rbtArcLeft(12);  rbtMoveFdDist(-10, 5000);}

	ClearTimer(T1);	while(time1[T1] < timeout) {
		if(i){r1 = getIRDir(sensorIR)-8;i=false; nxtDisplayBigTextLine(3, "%f", r1);} int acS[5]; HTIRS2readAllACStrength(sensorIR, acS[0], acS[1], acS[2], acS[3], acS[4]);

		if(r0 > 0) {setLeftMotors(acS[4] > acS[3] ? -10 : -50); setRightMotors(acS[4] > acS[3] ? -37 : -8);}
    else       {setLeftMotors(acS[4] > acS[3] ? -6 : -90); setRightMotors(acS[4] > acS[3] ? -30 :  0);}
	} setLeftMotors(0); setRightMotors(0);

	return (r0 > 0 ? (r1 > 0 ? 1 : 2) : (r1 > 0 ? 3 : 4));
}

#endif //__AUTODRIVER__
