#ifndef __SHAREDUTILS__
#define __SHAREDUTILS__

#include "JoystickDriver4278.c"
#include "hitechnic-irseeker-v2.h"
#include "wiringnxt.h"

#define setLeftMotors(x)  {motor[mLeft1]  = x; motor[mLeft2]  =  x;}
#define setRightMotors(x) {motor[mRight1] = x; motor[mRight2] =  x;}

#define setArmLocked()   {servo[sLock] = 140;}
#define setArmUnlocked() {servo[sLock] = 080;}

bool shifterStateArm = true;
#define setShifterArm()  {servo[sShifter] = 100; shifterStateArm = true;}
#define setShifterFlag() {servo[sShifter] = 170; shifterStateArm = false;}
#define getShifterState() (shifterStateArm)
#define flipShifterState() {if(shifterStateArm) setShifterFlag(); else setShifterArm();}

#define leftEncoder     abs(nMotorEncoder[mLeft1])
#define rightEncoder    abs(nMotorEncoder[mRight1])
#define clearEncoders() {}

//Distance Macros
#define INCH   1.0
#define CM     0.3937
#define MM    39.370
#define YARD  36.0
#define FOOT  12.0
#define METER 39.370

#define WHEELCIRC 12.566
#define WHEELBASE 15.309
#define FLOORMAT  24.0

#define BTN_CENTER 3
#define BTN_LEFT   2
#define BTN_RIGHT  1
#define BTN_BACK   0

#define LEFT_POW_DIFF 1.0
#define RIGHT_POW_DIFF 1.0

void waitForStart() {
  while(true) {
    getJoystickSettings(joystick);
    if(!joystick.StopPgm) break;
  }
}

void extendArm()
{
	//58.5 is the maximum torque speed
	motor[mArm1] = 58.5;
	motor[mArm2] = 58.5;
}

float max(float a, float b) {return (a>b ? a : b);}

#endif //__SHAREDUTILS__
