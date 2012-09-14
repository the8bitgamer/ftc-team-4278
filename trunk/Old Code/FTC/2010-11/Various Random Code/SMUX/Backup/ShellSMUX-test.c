

#include "JoystickDriver.c"
#include "drivers/common.h"
#include "drivers/HTCS-driver.h"
#include "drivers/HTGYRO-driver.h"

#define wheelRadius 2
#define distBtwnWheels 18
#define Pie 3.14195
#define colorBottomLineColorName SensorValue[colorPort]
#define nil 999999
#define rgbStopOnRollingGoal 200
#define gyroThreshold 2
#define leftEncVal nMotorEncoder[motorsLeft]
#define rightEncVal nMotorEncoder[motorsRight]
#define safeVerticalAngle 12
#define safeGyroTurnChange 4
#define wheelRotEncValThresh 7
#define gyroTurningTimer T1
#define gyroVerticalTimer T2
//float checkIfLeftWheelsFrozen(float lastEncoderValueLeft);
//float checkIfRightWheelsFrozen(float lastEncoderValueRight);
void armUp();
void armDown();
void initializeRobot();
//void clearEncoders();
//float forward(float dist);
void freezeRobot();
//float gyroTurnIntegrate();
//float gyroVertIntegrate();
//bool checkColorSensors(bool colorTargetIsRed, bool colorTargetIsBlue, bool colorTargetIsWhite, bool colorTargetSumVal);
//bool checkGyroTurn(float gyroValue, float gyroTargetVal);
//bool checkEncVal(float targetDist);
//void resetHeading(float gyroTargetVal, float gyroValue);
//void makeRobotLevel(bool freezeAtEnd, float gyroVert);
void moveRobot(float targetDist, float gyroTargetVal, float leftWheelPower, float rightRatioVal, bool colorTargetIsRed, bool colorTargetIsBlue, bool colorTargetIsWhite, bool colorTargetSumVal, int encoderExitByDefault);

float gyroTurnIntegrate()
{
	//wait1Msec(4);
	//return HTGYROreadRot(msensor_S4_1)/250;
	float now = HTGYROreadRot(msensor_S4_1);
	now = now/(1000/time1[gyroTurningTimer]);
	return now; /*return modded gyro rotation value*/
	ClearTimer(gyroTurningTimer);
}

float gyroVertIntegrate()
{
	float now = HTGYROreadRot(msensor_S4_2);
	now = now/(1000/time1[gyroVerticalTimer]);
	//Wait has been removed, so the time between readings remains 4ms
	return now;
	ClearTimer(gyroVerticalTimer);
}

void makeRobotLevel(bool freezeAtEnd, float gyroVert)
{
	if(gyroVert < 0)
	{
		while(gyroVert < -safeVerticalAngle || gyroVert > safeVerticalAngle)
		{
			motor[motorsLeft] = -100;
			motor[motorsRight] = -100;
			gyroVert += gyroVertIntegrate();
		}
	}
	else
	{
		while(gyroVert < -safeVerticalAngle || gyroVert > safeVerticalAngle)
		{
			motor[motorsLeft] = 100;
			motor[motorsRight] = 100;
			gyroVert += gyroVertIntegrate();
		}
	}

	if(freezeAtEnd == true) {freezeRobot();}
}

float checkIfLeftWheelsFrozen(float lastEncoderValueLeft)
{
	float currentEncoderValueLeft = nMotorEncoder[motorsLeft];
	float minThreshold = lastEncoderValueLeft - wheelRotEncValThresh;
	float maxThreshold = lastEncoderValueLeft + wheelRotEncValThresh;
	if(currentEncoderValueLeft > minThreshold && currentEncoderValueLeft < maxThreshold) {freezeRobot();} else {return currentEncoderValueLeft;}
}

float checkIfRightWheelsFrozen(float lastEncoderValueRight)
{
	float currentEncoderValue = nMotorEncoder[motorsRight];
	float minThreshold = lastEncoderValueRight - wheelRotEncValThresh;
	float maxThreshold = lastEncoderValueRight + wheelRotEncValThresh;
	if(currentEncoderValue > minThreshold && currentEncoderValue < maxThreshold) {freezeRobot();} else {return currentEncoderValue;}
}

void armUp()
{
        motor[motorArm] = -50;
        wait1Msec(700);
        motor[motorArm] = 0;
}

void armDown()
{
	motor[motorArm] = 15;
        wait1Msec(650);
        motor[motorArm] = 0;
}

void initializeRobot()
{
	HTSMUXinit();
	HTSMUXscanPorts(HTSMUX);
	//HTGYROstartCal(msensor_S4_1);
	//HTGYROstartCal(msensor_S4_2);
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
	float gyroVert = 0;

	motor[motorsLeft] = 0;
	motor[motorsRight] = 0;

	while(true)
	{
		makeRobotLevel(false, gyroVert);
		gyroVert += gyroVertIntegrate();
	}
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
	//if(rightEncVal > encTarget) {return true;}
	return false;
}

void resetHeading(float gyroTargetVal, float gyroValue)
{
	if(!checkGyroTurn(gyroValue, gyroTargetVal))
	{
		int change = gyroValue - gyroTargetVal;
		//positive change means the robot turns left; negative = right

		if(change < 0) {change = -1;} else {change = 1;}
		motor[motorsLeft] = 15*change;
		motor[motorsRight] = -15*change;
		while(!checkGyroTurn(gyroValue, gyroTargetVal)) {gyroValue += gyroTurnIntegrate();}

		gyroValue += gyroTurnIntegrate();
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

  //HTGYROsetCal(msensor_S4_1, 605);
	ClearTimer(gyroTurningTimer);
	ClearTimer(gyroVerticalTimer);

	float gyroTurn = 0;
	float gyroVert = 0;
	bool exitMove = false;
	bool gyroTargetValPriority = true; //If we are turning in an arc, ignore gyroscopic reading until we have finished the arc.
	float lastEncoderValueLeft = 0; //gets passed to checkIfWheelsFrozen
	float lastEncoderValueRight = 0;
	float gyroTurnChange = 0;

	clearEncoders();

	if(targetDist == nil && gyroTargetVal == nil && colorTargetIsRed == false && colorTargetIsBlue == false && colorTargetIsWhite == false && colorTargetSumVal == false) {PlaySound(soundLowBuzz); PlaySound(soundLowBuzz); freezeRobot();}
	// ^If no exit conditions are set, produce error.

	if(rightRatioVal != 1 && rightRatioVal != -1) {gyroTargetValPriority = false;} //If we aren't turning (e.g. moving in an arc), lower the gyro target priority. Gyro will be oriented after exit conditions.

	if(encoderExitByDefault == nil) {PlaySound(soundLowBuzz); PlaySound(soundLowBuzz); freezeRobot();} //Produce an error if exitByDefault is nil

	while(exitMove == false)
	{

		if(targetDist != nil) {exitMove = checkEncVal(targetDist);} //Check !target distance reached

		motor[motorsLeft] = leftWheelPower; //Set wheel power
		motor[motorsRight] = leftWheelPower*rightRatioVal;

		if(forward(24*encoderExitByDefault) < nMotorEncoder[motorsLeft]) {freezeRobot();} //Exit if past default point
		if(forward(24*encoderExitByDefault) < nMotorEncoder[motorsRight]) {freezeRobot();}

//		gyroTurnChange = gyroTurn/250; //For later use

		gyroTurn += gyroTurnIntegrate(); //Integrate the gyroscope values

//		gyroVert += gyroVertIntegrate();

//		gyroTurnChange = gyroTurn - gyroTurnChange; //Set gyroTurnChange to the change over the last 4 milliseconds

		//lastEncoderValueLeft = checkIfLeftWheelsFrozen(lastEncoderValueLeft); //Check to see if the left or right wheels are frozen
		//lastEncoderValueRight = checkIfRightWheelsFrozen(lastEncoderValueRight);

//		if(abs(gyroVert) > safeVerticalAngle) {makeRobotLevel(true, gyroVert);} //If the vertical gyro is beyond the save vertical angle range, flatline the robot and stop
//		if(abs(gyroTurnChange) > safeGyroTurnChange) {makeRobotLevel(true, gyroVert);} //If we are knocked out of the safe range for turning, stop.

//		exitMove = checkColorSensors(colorTargetIsRed, colorTargetIsBlue, colorTargetIsWhite, colorTargetSumVal); //Checks the color sensors for exit conditions

		if(gyroTargetVal != nil && gyroTargetValPriority == true) //Check if turning is complete, so long as we aren't arc turning
		{
			exitMove = checkGyroTurn(gyroTurn, gyroTargetVal);
		}
	}
	if(gyroTargetVal != nil) {resetHeading(gyroTargetVal, gyroTurn);} //Realign robot to exit angle
	motor[motorsLeft] = 0;
	motor[motorsRight] = 0;
}
