#ifndef __AUTODRIVER__
#define __AUTODRIVER__

#include "sharedutils.h"

#define DRV_TIMER T3
#define MAX_TURN_TIME 5000
#define PAUSE_TIME 250

void pause() {wait1Msec(PAUSE_TIME);}
void pause(int n) {for(int i = 0; i < n; i++) pause();}
void estop() {StopAllTasks();}

int getEncoderByInches(float inches) {return floor((DEG_PER_REV)*(inches)/WHEELCIRC);}
float getInchesByEncoder(float encode) {return (encode/DEG_PER_REV)*WHEELCIRC;}

void lockdownRobot() {
	PlaySound(soundException);
	setLeftMotors(0);
	setRightMotors(0);
	while(true) wait1Msec(5);
}

float getIRDir(tSensors link) {
    static float prevDir = 0.0; float currDir; int acS[5]; int idx;

    idx = HTIRS2readACDir(link);
    currDir = (float)idx;
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

void rbtMoveFdDist(float inches, int msec) {
	clearEncoders();
	int enc = abs(getEncoderByInches(inches));
	int norm = 1.0*sgn(inches);
	ClearTimer(DRV_TIMER);

	while(leftEncoder < enc && rightEncoder < enc) {
		if(time1[DRV_TIMER] > msec) lockdownRobot();
		setLeftMotors (25*norm*LEFT_POW_DIFF);
		setRightMotors(25*norm*RIGHT_POW_DIFF);
	}
	setLeftMotors(0); setRightMotors(0); pause();
}

void extendArm()
{
	//58.5 is the maximum torque speed
	motor[mSlide1] = -54;
	motor[mSlide2] = 58.5;

	nMotorEncoder[mSlide1] = 0;
  nMotorEncoder[mSlide2] = 0;

	bool slideOneDone = false;
	bool slideTwoDone = false;

	ClearTimer(DRV_TIMER);

	while(!(slideOneDone && slideTwoDone))
	{
		if(time1[DRV_TIMER] > 1000 && (abs(nMotorEncoder[mSlide1]) < 100 || abs(nMotorEncoder[mSlide2]) < 100))
		{
			writeDebugStreamLine("Encoder not registering, emergency slide stop!");
			writeDebugStreamLine("Slide Motor Enc. 1: %d, Slide Motor Enc. 2: %d", nMotorEncoder[mSlide1], nMotorEncoder[mSlide2]);
			motor[mSlide1] = 0;
			motor[mSlide2] = 0;
			return;
		}


		if(nMotorEncoder[mSlide1] < -32000)
		{
			motor[mSlide1] = 0;
			slideOneDone = true;
		}
		if(nMotorEncoder[mSlide2] > 40000)
		{
			motor[mSlide2] = 0;
			slideTwoDone = true;
		}

		writeDebugStreamLine("Slide Motor 1: %d, Slide Motor 2: %d", nMotorEncoder[mSlide1], nMotorEncoder[mSlide2]);

	}

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


//arc to the right (set LEFT motors)
void rbtArcRight(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(sgn(degs)*40);
	ClearTimer(DRV_TIMER);
	while(leftEncoder < enc) if(time1[DRV_TIMER] > MAX_TURN_TIME) lockdownRobot();
	setLeftMotors(0); pause();
}

//arc to the left (set RIGHT motors)
void rbtArcLeft(float degs) {
	int enc = getEncoderByInches((2.0*PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	int sign = sgn(degs);
	setRightMotors(sign*40);
	ClearTimer(DRV_TIMER);
	while(rightEncoder < enc)
	{
		wait10Msec(1);
		if(time1[DRV_TIMER] > MAX_TURN_TIME)
			lockdownRobot();
	}
	setRightMotors(0); pause();
}

void rbtTurnRight(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors( -1*sgn(degs)*100);
	setRightMotors(sgn(degs)*100);
	ClearTimer(DRV_TIMER);
	while(rightEncoder < enc) if(time1[DRV_TIMER] > MAX_TURN_TIME) lockdownRobot();
	setLeftMotors(0); setRightMotors(0); pause();
}

void rbtTurnLeft(float degs) {
	int enc = getEncoderByInches((PI*WHEELBASE)*(abs(degs)/360.0));
	clearEncoders();
	setLeftMotors(sgn(degs)*100);
	setRightMotors(-1*sgn(degs)*100);
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
