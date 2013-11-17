#ifndef __SHAREDUTILS__
#define __SHAREDUTILS__

#define setLeftMotors(x)  {motor[mLeft1]  = x; motor[mLeft2]  = x;}
#define setRightMotors(x) {motor[mRight1] = x; motor[mRight2] = x;}
#define setArmMotors(x) {motor[mArm1] = x; motor[mArm2] = -x;}
#define setSpinMotor(x) {motor[mSpin] = x;}
#define lockArmMotors() {servo[servoL1] = 155; servo[servoL2] = 20;}
#define unlockArmMotors() {servo[servoL1] = 120; servo[servoL2] = 40;}

#define leftEncoder abs(nMotorEncoder[mLeft1])
#define rightEncoder abs(nMotorEncoder[mRight2])
#define clearEncoders() {nMotorEncoder[mLeft1] = 0; nMotorEncoder[mRight1] = 0;}

//Distance Macros
#define INCH 1.0
#define CM 0.3937
#define MM 39.370
#define YARD 36.0
#define FOOT 12.0
#define METER 39.370

#define WHEELCIRC 12.566
#define FLOORMAT 24.0

float linearScale(float x, float in_min, float in_max, float out_min, float out_max) {return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;}

void displayDiagnostics() {
	if(externalBatteryAvg < 0)
  	nxtDisplayTextLine(3, "Ext Batt: OFF");
 	else
  	nxtDisplayTextLine(3, "Ext Batt:%4.1f V", externalBatteryAvg / (float) 1000);//Why (float)? Does 1000.0 not work?
  nxtDisplayTextLine(4, "NXT Batt:%4.1f V", nAvgBatteryLevel / (float) 1000);
}

#endif //__SHAREDUTILS__
