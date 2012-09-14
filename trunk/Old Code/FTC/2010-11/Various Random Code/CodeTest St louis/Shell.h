#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S3,     colorHitechnicRollingGoal,                sensorLowSpeed)
#pragma config(Sensor, S2,     colorPort,           sensorCOLORFULL)
#pragma config(Motor,  motorA,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorC,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorsLeft,    tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorArm,      tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorNormal, openLoop)
#pragma config(Sensor, S4,     GyroSensor,          sensorRawValue)

#include "JoystickDriver.c"
#include "drivers/common.h"
#include "drivers/HTCS-driver.h"
#include "drivers/HTGYRO-driver.h"

#define wheelRadius 2
#define distBtwnWheels 18
#define Pie 3.14195
#define turnGyroReading HTGYROreadRot(GyroSensor)
#define colorBottomLineColorName SensorValue[colorPort]
#define nil 999999
#define rgbStopOnRollingGoal 200
#define gyroThreshold 5
#define leftEncVal nMotorEncoder[motorsLeft]
#define rightEncVal nMotorEncoder[motorsRight]

void initializeRobot();
void clearEncoders();
float forward(float dist);
void freezeRobot();
float gyroTurningIntegrate();
bool checkColorSensors(bool colorTargetIsRed, bool colorTargetIsBlue, bool colorTargetIsWhite, bool colorTargetSumVal);
bool checkGyroTurn(float gyroValue, float gyroTargetVal);
bool checkEncVal(float targetDist);
void resetHeading(float gyroTargetVal, float gyroValue);
void moveRobot(float targetDist, float gyroTargetVal, float leftWheelPower, float rightRatioVal, bool colorTargetIsRed, bool colorTargetIsBlue, bool colorTargetIsWhite, bool colorTargetSumVal, int encoderExitByDefault);

void initializeRobot()
{
	HTGYROstartCal(GyroSensor);
}

void clearEncoders()
{
	nMotorEncoder[motorsLeft] = 0;
	nMotorEncoder[motorsRight] = 0;
}

float forward(float dist)
{
	return (1440*dist)/(2*Pie*wheelRadius);
}

void freezeRobot()
{
	  motor[motorsLeft] = 0;
	  motor[motorsRight] = 0;
	  while(true) {}
}

float gyroTurningIntegrate()
{
	  float now = turnGyroReading;
	  now = now / 250;
	  wait1Msec(4);
	  return now; /*return modded gyro rotation value*/
}

bool checkColorSensors(bool colorTargetIsRed, bool colorTargetIsBlue, bool colorTargetIsWhite, bool colorTargetSumVal)
{
	bool exitMove = false;
	if(colorTargetIsRed == true)
	{
		if(colorBottomLineColorName == REDCOLOR) {exitMove = true;}
	}

	if(colorTargetIsBlue == true)
	{
		if(colorBottomLineColorName == BLUECOLOR) {exitMove = true;}
	}

	if(colorTargetIsWhite == true)
	{
		if(colorBottomLineColorName == WHITECOLOR) {exitMove = true;}
	}

	if(colorTargetSumVal == true)
	{
		int red;
		int green;
		int blue;
		HTCSreadRGB(colorHitechnicRollingGoal, red, green, blue);
		int rgb = red + green + blue;
		if(rgb > rgbStopOnRollingGoal) {exitMove = true;}
	}
	return exitMove;
}

bool checkGyroTurn(float gyroValue, float gyroTargetVal)
{
	float gyroMinThreshold = gyroTargetVal - gyroThreshold;
	float gyroMaxThreshold = gyroTargetVal + gyroThreshold;
	if(gyroValue > gyroMinThreshold && gyroValue < gyroMaxThreshold) {return true;}
	return false; /*checks if turning is complete*/
}

bool checkEncVal(float targetDist)
{
	targetDist = targetDist * 24;
	float encTarget = forward(targetDist);
	if(leftEncVal > encTarget) {return true;}
	if(rightEncVal > encTarget) {return true;}
	return false;
}

void resetHeading(float gyroTargetVal, float gyroValue)
{
	if(!checkGyroTurn(gyroValue, gyroTargetVal))
	{
		int change = gyroValue - gyroTargetVal;
		//positive change means the robot turns left; negative = right

		if(abs(change) < 15)
		{
			motor[motorsLeft] = -change;
			motor[motorsRight] = change;
			while(!checkGyroTurn(gyroValue, gyroTargetVal)) {}
		}
		else
		{
			if(change < 0) {change = -1} else {change = 1}
			motor[motorsLeft] = 20*change;
			motor[motorsRight] = -20*change;
			while(!checkGyroTurn(gyroValue, gyroTargetVal)) {}
		}
	}
}

void moveRobot(float targetDist, float gyroTargetVal, float leftWheelPower, float rightRatioVal, bool colorTargetIsRed, bool colorTargetIsBlue, bool colorTargetIsWhite, bool colorTargetSumVal, int encoderExitByDefault)
{
	//targetDist is the target distance value in field squares
	//gyroTargetVal is the target gyroscope value (for turning)
	//leftWheelPower = power to the left wheel as %
	//rightRatioVal is the speed of the rigt wheel in relation to the left wheel
	//colorTargetIsRed = stop if sensor color is red
	//colorTargetIsBlue = stop if sensor color is blue
	//colorTargetIsWhite = stop if sensor color is white
	//colorTargetSumVal = stop if stop when see rolling goal [+]
	//encoderExitByDefault = stop if encoders have gone too far [+]

	/*
	Check if robot has gone too far
	Check priority exit conditions:
	Gyro turning
	Color sensor names (WHITECOLOR, REDCOLOR)
	*/

	float gyroTurn = 0;
	bool exitMove = false;
	bool runOnce = false;
	bool gyroTargetValPriority = true; //If we are turning in an arc, ignore gyroscopic reading until we have finished the arc.

	clearEncoders();

	if(targetDist == nil && gyroTargetVal == nil && colorTargetIsRed == false && colorTargetIsBlue == false && colorTargetIsWhite == false && colorTargetSumVal == false) {playSound(soundLowBuzz); playSound(soundLowBuzz); freezeRobot();}
	// ^If no exit conditions are set, produce error.

	if(rightRatioVal != 1 && rightRatioVal != -1) {gyroTargetValPriority = false;}

	while(exitMove == false)
	{

		if(targetDist != nil) //Check !target distance reached
		{
			exitMove = checkEncVal(targetDist);
		}

		motor[motorsLeft] = leftWheelPower; //Set wheel power
		motor[motorsRight] = leftWheelPower*rightRatioVal;

		if(targetDist != nil)
		{
			if(encoderExitByDefault == nil) {playSound(soundLowBuzz); playSound(soundLowBuzz); freezeRobot();} //Produce an error if exitByDefault is nil
			if(forward(24*encoderExitByDefault) < nMotorEncoder[motorsLeft]) {freezeRobot();} //Exit if past default point
			if(forward(24*encoderExitByDefault) < nMotorEncoder[motorsRight]) {freezeRobot();}
		}

		gyroTurn += gyroTurningIntegrate(); //Integrate the gyroscope value

		exitMove = checkColorSensors(colorTargetIsRed, colorTargetIsBlue, colorTargetIsWhite, colorTargetSumVal);

		if(gyroTargetVal != nil && gyroTargetValPriority == true) //Check if turning is complete
		{
			exitMove = checkGyroTurn(gyroTurn, gyroTargetVal);
		}

	  //Realignment
	}

	resetHeading(gyroTargetVal, gyroTurn);
}
