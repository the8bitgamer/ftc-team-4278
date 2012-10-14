#include "drivers\hitechnic-accelerometer.h"
#include "drivers\hitechnic-gyro.h"

float xPos=0, yPos=0, zPos=0, xVel=0, yVel=0, zVel=0, xAcc=0, yAcc=0, zAcc=0;
float xOff=0, yOff=0, zOff=0, xScl=0, yScl=0, zScl=0; //Off = offset, Scl = scalar. For internal use ONLY
#define aToN 20
#define aThresh 0.1
#define posToMet 1
float xAccAvg[5] = {0,0,0,0,0}, yAccAvg[5] = {0,0,0,0,0}, zAccAvg[5] = {0,0,0,0,0};

float gVal=0, robotTh=0;
#define gyrThresh 1.0

int lastIterTime = 0;
tSensors snsGyr, snsAcc;
bool bDebugOutput = true;

void disableAccGyrDebugOutput() {bDebugOutput = false;}

void getAccVals() {
	int xA, yA, zA; HTACreadAllAxes(snsAcc, xA, yA, zA);
	xAcc = xA; yAcc = yA; zAcc = zA;
}
float getGyroVal() {return HTGYROreadRot(snsGyr);}

void integrateGyro() {
	gVal=getGyroVal();
	float dT = (nPgmTime - lastIterTime)/1000.0;
	robotTh += (gVal>gyrThresh ? gVal*dT : 0.0);
}

void integrateAccel() {
	getAccVals(); float dT = (nPgmTime - lastIterTime)/1000.0;

	for(int i = 0; i < 4; i++) {
		xAccAvg[i] = xAccAvg[i+1];
		yAccAvg[i] = yAccAvg[i+1];
		zAccAvg[i] = zAccAvg[i+1];
	}
	xAccAvg[4] = xAcc;
	yAccAvg[4] = yAcc;
	zAccAvg[4] = zAcc;
	xAcc=0; yAcc=0; zAcc=0;
	for(int i=0; i<5; i++) {xAcc += (xAccAvg[i]+xOff)/xScl; yAcc += (yAccAvg[i]+yOff)/yScl; zAcc += (zAccAvg[i]+zOff)/zScl;}
	xAcc = ((xAcc) / 5)/aToN; yAcc = ((yAcc) / 5)/aToN; zAcc = ((zAcc) / 5)/aToN;

	xVel += (xAcc>aThresh?xAcc:0)*dT; yVel += (yAcc>aThresh?yAcc:0)*dT; zVel += (zAcc>aThresh?zAcc:0)*dT;
	xPos += xVel*dT*posToMet; yPos += yVel*dT*posToMet; zPos += zVel*dT*posToMet;
}

void resetPositions() {xPos=0; yPos=0; zPos=0; xVel = 0; yVel = 0; zVel = 0;}

void setupSensors(tSensors snsAccz, tSensors snsGyrz) {
	snsGyr = snsGyrz;
	snsAcc = snsAccz;
	HTGYROstartCal(snsGyr);
}

task BackgroundIntegration()
{
	disableAccGyrDebugOutput(); bDebugOutput = true;
	while(true) {
		integrateGyro();
		integrateAccel();
		lastIterTime = nPgmTime;
		if(bDebugOutput) {
			nxtDisplayTextLine(2, "xPos: ", xPos);
			nxtDisplayTextLine(3, "yPos: ", yPos);
			nxtDisplayTextLine(4, "rRot: ", robotTh);
		}
		EndTimeSlice();
	}
}
