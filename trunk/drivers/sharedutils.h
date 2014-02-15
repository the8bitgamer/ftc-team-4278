#ifndef __SHAREDUTILS__
#define __SHAREDUTILS__

#include "JoystickDriver4278.c"
#include "hitechnic-irseeker-v2.h"
#include "wiringnxt.h"

#define setLeftMotors(x)  {motor[mLeft1]  = x; motor[mLeft2]  =  x;}
#define setRightMotors(x) {motor[mRight1] = x; motor[mRight2] =  x;}
#define setArmMotors(x)   {motor[mArm1]   = x; motor[mArm2]   = -x;}
#define setSpinMotor(x)   {motor[mSpin]   = x;}
#define lockArmMotors()   {servo[servoL1] = 155; servo[servoL2] = 20;}
#define unlockArmMotors() {servo[servoL1] = 120; servo[servoL2] = 70;}

#define leftEncoder     abs(nMotorEncoder[mArm2])
#define rightEncoder    abs(nMotorEncoder[mArm1])
#define clearEncoders() {nMotorEncoder[mArm1] = 0; nMotorEncoder[mArm2] = 0;}

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

#define LEFT_POW_DIFF 0.563
#define RIGHT_POW_DIFF 1.0

void waitForStart() {
  while(true) {
    getJoystickSettings(joystick);
    if(!joystick.StopPgm) break;
  }
}

#endif //__SHAREDUTILS__
