#include "AccelGyroDriver.h"
#include "HolonomicDriver.h"

float xyAccuracy = 0.5;
float thAccuracy = 3;

void setDriveAccuracy(float xyAccuracyz, float thAccuracyz) {xyAccuracy = xyAccuracyz; thAccuracy = thAccuracyz;}

void moveToTh(float theta) {
	while(true) {
		targetRobotTh = theta;
		EndTimeSlice();

		if(abs(robotTh - theta) < thAccuracy) break;
	}
	stopMotors();
}

void moveToPos(float targetX, float targetY, float mag) {
	resetPositions();
	while(true) {
		targetMoveTh = getTheta(targetX-xPos, targetY-yPos);
		targetMoveMag = mag;
		EndTimeSlice();
		if(abs(targetX - xPos) < xyAccuracy && abs(targetY - yPos) < xyAccuracy) break;
	}

	targetMoveTh = 0;
	targetMoveMag = 0;
	stopMotors();
}
