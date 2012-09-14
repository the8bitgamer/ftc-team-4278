#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     turningGyro,         sensorLowSpeed)
#pragma config(Sensor, S3,     colorHitechnicRollingGoal, sensorLowSpeed)
#pragma config(Sensor, S4,     colorLineDetector,   sensorCOLORFULL)
#pragma config(Motor,  motorA,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorC,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorsLeft,    tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorArm,      tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorNone, openLoop)

#include "Shell.c"

#define leftSide true
#define rightSide false

task main()
{
  initializeRobot(leftSide);
  waitForStart();

  moveRobot(1.25, 20);
  moveRobot(-43.5);
  moveRobot(false, false, false, true, 10);
  armUp();
  wait1Msec(400);
  armDown();

  moveRobot(2.5, 0, true);
  armUp();
  wait1Msec(20000);
  armDown();
}
