#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-colour-v2.h"

#define xyAccuracy 0.15
#define rotAccuracy 1

#define mBackLeft motor[motorBL]
#define mBackRight motor[motorBR]
#define mFrontLeft motor[motorFL]
#define mFrontRight motor[motorFR]

float targetTh = 0, targetMag = 0, targetRot = 0;
float gRot = 0;

void stopAllDrive() {
	mBackLeft = 0;
	mBackRight = 0;
	mFrontLeft = 0;
	mFrontRight = 0;
	targetTh = 0;
	gRot = 0;
	targetMag = 0;
}

void moveToPos(float x, float y, float mag) {
	resetPositionData();
	targetMag = mag;
	while(true) {
		if(abs(sqrt(pow(robotX,2) + pow(robotY,2)) - sqrt(pow(x,2) + pow(y,2))) < xyAccuracy) break;
		targetTh = atan2(y,x);

		EndTimeSlice();
	}
	stopAllDrive(); ClearTimer(T1);
	while(time1[T1] < 500) EndTimeSlice();
	resetPositionData();
}

void moveToRot(float rot) {
	resetPositionData();
	targetRot = rot+(robotRot < rot?-3.3:3.3);
	while(true) {
		if(abs(robotRot-targetRot) < rotAccuracy) break;
		gRot = sgn(robotRot - targetRot) * -0.25;
		EndTimeSlice();
	}
	gRot = 0;
	stopAllDrive(); ClearTimer(T1);
	while(time1[T1] < 500) EndTimeSlice();
	resetPositionData(); targetRot = robotRot;
}

const tMUXSensor colorSns = msensor_S1_3;

void moveToWhite(float x, float y, float mag)
{
	targetMag = mag;
	while(true) {
		if(HTCS2readColor(colorSns) == 3) break;
		targetTh = atan2(y,x);

		EndTimeSlice();
	}
	stopAllDrive(); ClearTimer(T1);
	while(time1[T1] < 500) EndTimeSlice();
}

task HolonomicControl()
{
	while(true) {
		float th = targetTh;
		float v = targetMag;
		float rot = gRot;

		float mBackLeftTmp = (cos(th+(PI/4))*v - rot/(1.5));
		float mFrontRightTmp = (cos(th+(PI/4))*v + rot/1.5);
		float mBackRightTmp = -1 * (sin(th+(PI/4))*v - rot/1.5);
		float mFrontLeftTmp = -1 * (sin(th+(PI/4))*v + rot/1.5);

		float max = 1;
		if(abs(mBackLeftTmp) > abs(max)) max = mBackLeftTmp;
		if(abs(mFrontRightTmp) > abs(max)) max = mFrontRightTmp;
		if(abs(mBackRightTmp) > abs(max)) max = mBackRightTmp;
		if(abs(mFrontLeftTmp) > abs(max)) max = mFrontLeftTmp;
		max = abs(max);

		mBackLeft = 100 * mBackLeftTmp / max;
		mFrontRight = 100 * mFrontRightTmp / max;
		mBackRight = 100 * mBackRightTmp / max;
		mFrontLeft = 100 * mFrontLeftTmp / max;
	}
}
