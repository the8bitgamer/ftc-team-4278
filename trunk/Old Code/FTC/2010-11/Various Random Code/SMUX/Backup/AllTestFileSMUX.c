#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S3,     colorHitechnicRollingGoal,                sensorLowSpeed)
#pragma config(Sensor, S4,     colorPort,           sensorCOLORFULL)
#pragma config(Motor,  motorA,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorC,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorsLeft,    tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorArm,      tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorNormal, openLoop)
#pragma config(Sensor, S2, turningGyro, sensorLowSpeed)

#include "ShellSMUX.c"
/*
1: FLOAT Target distance in squares
2: FLOAT Target gyroscope (turning) value +/- 5 degrees
3: FLOAT Left whetel power from -100 to 100
4: FLOAT Right wheel power as percentage (in decimal format) of left wheel power. -1 to turn.
5: BOOL True if stop on color red
6: BOOL True if stop on color blue
7: BOOL True if stop on color white
8: BOOL True if stop on rolling goal (adjust sensetivity from within Shell)
9: FLOAT Number of squares to stop at if the conditions aren't fulfilled.
*/

task main()
{
	initializeRobot(); //Shell handles multiplexor and gyros
	PlaySound(soundFastUpwardTones);
	wait1Msec(1500);
	moveRobot(nil, -80, -15, -1, false, false, false, false, 2);
  PlaySound(soundLowBuzz);
  wait1Msec(1000);
}
