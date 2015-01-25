#ifndef __SHAREDUTILS__
#define __SHAREDUTILS__

#include "JoystickDriver4278.c"
#include "hitechnic-irseeker-v2.h"
#include "Feedback.h"

#define setLeftMotors(x)  {int pow = multiplierLeft*x; motor[mLeft1] = pow; motor[mLeft2] = pow;}
#define setRightMotors(x) {int powr = 1.4*multiplierRight*x; motor[mRight1] = powr; motor[mRight2] =  powr;}
#define getShifterState() (shifterStateArm)
#define flipShifterState() {if(shifterStateArm) setShifterFlag(); else setShifterArm();}

#define leftEncoder     abs(nMotorEncoder[mLeft2])
#define rightEncoder    abs(nMotorEncoder[mRight2])

#define clearEncoders() {nMotorEncoder[mLeft2] = 0; nMotorEncoder[mRight2] = 0; encodersWereCleared = true;}

//Distance Macros
#define INCH   1.0
#define CM     0.3937
#define MM    39.370
#define YARD  36.0
#define FOOT  12.0
#define METER 39.370

#define WHEELCIRC 9.42585

//horizontal distance between wheels
#define WHEELBASE 10.95
#define FLOORMAT  24.0

#define BTN_CENTER 3
#define BTN_LEFT   2
#define BTN_RIGHT  1
#define BTN_BACK   0

#define LEFT_POW_DIFF 1.0
#define RIGHT_POW_DIFF 1.0

//degrees per revolution
#define DEG_PER_REV 1440
//servo constants
#define HOOK1_HOOKDOWN 80
#define HOOK1_HOOKREST 240

//hook 2
#define HOOK2_HOOKDOWN 176
#define HOOK2_HOOKREST 16

#define CHAINSPEEDSCALAR .5
void waitForStart() {

	int poundIndex = 0;
  while(true)
  {
  	eraseDisplay();
		nxtDisplayTextLine(1, "Waiting for match...");
		nxtDisplayBigStringAt(++poundIndex, 35, "#");
		if(poundIndex == 100)
		{
			poundIndex = 0;
		}
		wait1Msec(6);
    getJoystickSettings(joystick);
    if(!joystick.StopPgm) break;
  }

  eraseDisplay();
}

//clamp an int inclusively between two other ints
int clamp_int(int toClamp, int min, int max)
{
	if(toClamp < min)
	{
		toClamp = min;
	}
	else if(toClamp > max)
	{
		toClamp = max;
	}
	return toClamp;
}

void retractHooks()
{
	servo[tubeHook1] = HOOK1_HOOKREST;
	servo[tubeHook2] = HOOK2_HOOKREST;
}

void extendHooks()
{
	servo[tubeHook1] = HOOK1_HOOKDOWN;
	servo[tubeHook2] = HOOK2_HOOKDOWN;
}

float max(float a, float b) {return (a>b ? a : b);}

#endif //__SHAREDUTILS__
