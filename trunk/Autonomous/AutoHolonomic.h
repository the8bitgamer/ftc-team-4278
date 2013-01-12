#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-colour-v2.h"

#define mBackLeft motor[motorBL]
#define mBackRight motor[motorBR]
#define mFrontLeft motor[motorFL]
#define mFrontRight motor[motorFR]

void stopMotors() {
	mBackLeft = 0;
	mBackRight = 0;
	mFrontLeft = 0;
	mFrontRight = 0;
}

void holonomicComputation(float th, float v, float rot) {
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

bool moveToPos(float x, float y, float mag) {
	holonomicComputation(atan2(y,(x + .25*y/2.0)),mag,(-1.0 * robotTh / 25.0));
	float popeye=abs(robotX);
	float pumpkinskin=abs(robotY);
	float newb = abs(x);
	float nicStoneIsDead = abs(y);
	if(abs(popeye - newb) < 0.1 && abs(pumpkinskin - nicStoneIsDead) < 0.1) return true;
	return false;
}

const tMUXSensor colorSnsLine = msensor_S1_3;

bool moveToWhite(float x, float y, float mag)
{
	int _r, _g, _b;
	holonomicComputation(atan2(y,(x + .25*y/2.0)),mag,(-1.0 * robotTh / 25.0));
	HTCS2readRGB(colorSnsLine, _r, _g, _b);
	if(_r + _g + _b > 425 && _r + _g + _b != 255*3) return true;
	return false;
}

bool moveToRot(float rot) {
	holonomicComputation(0,0,(rot>0?.5:-.5));
	if(abs(robotTh - rot) < 3) return true;
	if(abs(robotTh) > 360) {PlaySound(soundBeepBeep); while(bSoundActive); StopAllTasks();}
	return false;
}
