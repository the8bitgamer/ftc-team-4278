#define gyrThresh 0.0
#define aToN 20.0
#define aThresh 0.1
#define posToMet 1.0

#include "drivers\hitechnic-accelerometer.h"
#include "drivers\hitechnic-gyro.h"

float robotTh=0;

int lastIterTime=0;

task GyroIntegrate()
{
	if(HTGYROreadRot(sGyr) > gyrThresh) robotTh += HTGYROreadRot(sGyr) * (float)(nPgmTime - lastItertime) / 1000.0;
	lastIterTime = nPgmTime;
	wait1Msec(5);
	EndTimeSlice();
}

task AccelIntegrate()
{
  int xAxis=0, yAxis=0, zAxis=0, xBias=0, yBias=0, zBias=0;
  float xAcc=0, yAcc=0, xVel=0, yVel=0, xPos=0, yPos=0, xScl = 1, yScl = 1;
  float xAccAvg[6] = {0,0,0,0,0,0}, yAccAvg[6] = {0,0,0,0,0,0};

  HTACreadAllAxes(sAcc, xBias, yBias, zBias);
  float lastTime;
  lastTime = nPgmTime;

  while(true)
  {
    HTACreadAllAxes(sAcc, xAxis, yAxis, zAxis);
    xAcc = (xAxis - xBias)*xScl/aToN; yAcc = (yAxis-yBias)*yScl/aToN;

    float xAccSum=0, yAccSum=0;
    for(int i = 0; i < 5; i++) {
    	xAccAvg[i] = xAccAvg[i+1];
    	yAccAvg[i] = yAccAvg[i+1];
    	xAccSum += xAccAvg[i];
    	yAccSum += yAccAvg[i];
  	}
    xAccAvg[5] = xAcc; xAccSum += xAcc; xAccSum /= 6;
    yAccAvg[5] = yAcc; yAccSum += yAcc; yAccSum /= 6;



    nxtDisplayTextLine(3, "xA: %f",xAccSum);
    nxtDisplayTextLine(4, "yA: %f",yAccSum);
    nxtDisplayTextLine(6, "t: %f",(nPgmTime - lastTime)/1000.0);
    lastTime = nPgmTime;
  }
}

void BackgroundIntegration()
{
	//StartTask(GyroIntegrate);
	StartTask(AccelIntegrate);
}
