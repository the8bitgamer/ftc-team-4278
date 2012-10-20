#define gyrThresh 0.0

#include "drivers\hitechnic-accelerometer.h"
#include "drivers\hitechnic-gyro.h"

float robotTh=0;

int lastIterTime=0;
float xOff=0, yOff=0, zOff=0, xScl=0, yScl=0, zScl=0; //Off = offset, Scl = scalar. For internal use ONLY
#define aToN 20
#define aThresh 0.1
#define posToMet 1
float xAccAvg[5] = {0,0,0,0,0}, yAccAvg[5] = {0,0,0,0,0}, zAccAvg[5] = {0,0,0,0,0};

void GyroIntegrate()
{
	robotTh += HTGYROreadRot(sGyr) * (float)(nPgmTime - lastItertime) / 1000.0;
	//nxtDisplayTextLine(5, "%f", robotTh);
	lastIterTime = nPgmTime;
	wait1Msec(5);
	EndTimeSlice();
}

task AccelIntegrate()
{
int xAxis, yAxis, zAxis, xThresh, yThresh, zThresh;
  float xAcc, yAcc, zAcc, xVel, yVel, zVel, xDist, yDist, zDist, lXAcc, lYAcc, lZAcc, lLastTime, lXVel, ldXPos, xPos;
  HTACreadAllAxes(sAcc, xThresh, yThresh, zThresh);
  float lastTime;
  xAcc = 0; yAcc = 0; zAcc = 0; xVel = 0; yVel = 0; zVel = 0; xDist = 0; yDist = 0; zDist = 0; lXAcc = 0; lXVel = 0; ldXPos = 0;
  lastTime = nPgmTime;
  while(true)
  {
    HTACreadAllAxes(sAcc, xAxis, yAxis, zAxis); xAxis = xAxis - xThresh; yAxis = yAxis - yThresh; zAxis = zAxis - zThresh;
    xAcc = xAxis/20.0; yAcc = yAxis/20.0; zAcc = zAxis/20.0;
    lXVel = ((lLastTime)/1000.0) * lXAcc;
    if(abs(xAcc) > .1) xVel += (((((float)nPgmTime - lastTime)/1000.0) * xAcc)+lXVel)/2;
    ldXPos = ((lLastTime)/1000.0) * lXVel;
    if(abs(xVel) > .1) xPos += (((((float)nPgmTime -lastTime)/1000.0) * xVel));
    if(nNxtButtonPressed != -1) break;

    nxtDisplayTextLine(5, "xP: %f",xPos);
    nxtDisplayTextLine(4, "xA: %f",xAcc);
    nxtDisplayTextLine(3, "xV: %f",xVel);
    nxtDisplayTextLine(6, "t: %f",(nPgmTime - lastTime)/1000.0);
    lastTime = nPgmTime;
    lXAcc = xAcc;
    lLastTime = (float)nPgmTime - lastTime;
  }
}

void BackgroundIntegration()
{
	//GyroIntegrate();
	StartTask(AccelIntegrate);
}
