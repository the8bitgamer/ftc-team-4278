#define gyrThresh 0.3
#define aToN 20.0
#define aThresh 0.05
#define vThresh 0.01
#define posToFeet 15

#include "drivers\hitechnic-accelerometer.h"
#include "drivers\hitechnic-gyro.h"

float robotTh, robotX, robotY;

int xAxis=0, yAxis=0, zAxis=0, xBias=0, yBias=0, zBias=0;
float xAcc=0, yAcc=0, xVel=0, yVel=0, xPos=0, yPos=0, xScl = 0.973236, yScl = 0.977995;
float xAccAvg[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, yAccAvg[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int lastAccelTime, lastGyroTime;

bool debugAccelGyro = true;

void accelIntegrator() {
	HTACreadAllAxes(sAcc, yAxis, xAxis, zAxis);
	lastAccelTime = nPgmTime;
	xAcc = (xAxis - xBias)*xScl/aToN; yAcc = (yAxis-yBias)*yScl/aToN;

	float xAccSum=0, yAccSum=0;
	for(int i = 0; i < 14; i++) {
		xAccAvg[i] = xAccAvg[i+1];
		yAccAvg[i] = yAccAvg[i+1];
		xAccSum += xAccAvg[i];
		yAccSum += yAccAvg[i];
	}

	xAccAvg[14] = xAcc; xAccSum += xAcc; xAccSum /= 15;
	yAccAvg[14] = yAcc; yAccSum += yAcc; yAccSum /= 15;
	float dT = (nPgmTime - lastAccelTime)/1000.0;

	xVel += xAccSum*dT*(abs(xAccSum) > aThresh ? 1.0 : 0.0); yVel += yAccSum*dT*(abs(yAccSum) > aThresh ? 1.0 : 0.0);
	xPos += xVel*dT*(posToFeet)*(abs(xVel) > vThresh ? 1.0 : 0.0); yPos += yVel*dT*(posToFeet)*(abs(yVel) > vThresh ? 1.0:0.0);

	/*if(debugAccelGyro) {
		nxtDisplayTextLine(1, "xA: %f",xAccSum);
		nxtDisplayTextLine(2, "yA: %f",yAccSum);
		nxtDisplayTextLine(3, "xV: %f",xVel);
		nxtDisplayTextLine(4, "yV: %f",yVel);
		nxtDisplayTextLine(5, "xP: %f",xPos);
		nxtDisplayTextLine(6, "yP: %f",-yPos);
	}*/
	robotX = robotX + xPos; robotY = robotY + (-1 * yPos);
}

void gyroIntegrator() {
	if(abs(HTGYROreadRot(S2)) > 0.7) {robotTh -= (nPgmTime - lastGyroTime) * HTGYROreadRot(S2) / (1000);}
	lastGyroTime = nPgmTime;
	nxtDisplayTextLine(0, "G: %f", robotTh);
	nxtDisplayTextLine(7, "G: %f", HTGYROreadRot(S2));
}

void accelCalibration() {
	float xSum = 0, ySum = 0, zSum = 0;
	for(int i = 0; i < 25; i++) {
		HTACreadAllAxes(sAcc, yBias, xBias, zBias);
		xSum += xBias; ySum += yBias; zSum += zBias;
		wait1Msec(20);
	}
	xBias = xSum / 25;
	yBias = ySum / 25;
	zBias = ySum / 25;
}

void resetAccelGyroData() {
	robotTh = 0;
	xAcc=0; yAcc=0; xVel=0; yVel=0; xPos=0; yPos=0; xScl = 0.973236; yScl = 0.977995;
	for(int i = 0; i < 15; i++) {
		xAccAvg[i] = 0;
		yAccAvg[i] = 0;
	}
}

void initializeAccelGyro() {
	HTGYROstartCal(sGyr);
	accelCalibration();
	lastAccelTime = nPgmTime;
	lastGyroTime = nPgmTime;
}

void BackgroundIntegrator() {
	accelIntegrator();
	gyroIntegrator();
}
