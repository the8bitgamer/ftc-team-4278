#include "JoystickDriver.c"
#include "drivers/common.h"
#include "drivers/HTCS-driver.h"
#include "drivers/HTGYRO-driver.h"

#define Pie 3.14159
#define wheelRadius 2
#define distanceBetweenWheels 18

void initializeRobot(bool onLeftSide);
void armUp();
void armDown();
void moveRobot(float numberOfTilesToMove, float wheelPower); //For forward
void moveRobot(float degrees);
void moveRobot(bool colorIsRed, bool colorIsBlue, bool colorIsWhite, bool colorIsRollingGoal, int wheelPower); //for color sensor

float robotHeadingEachRun = 0;
float robotOverallHeading = 0;
float robotX = 0;
float robotY = 0;

float encoderLastValue = 0;

void initializeRobot(bool onLeftSide)
{
  if(onLeftSide) {robotOverallHeading = 90;} else {robotOverallHeading = -90; robotX = 6;}
  HTGYROstartCal(turningGyro);
}

void armUp()
{
  motor[motorArm] = -50;
  wait1Msec(700);
  motor[motorArm] = 0;
  wait1Msec(250);
}

void armDown()
{
	motor[motorArm] = 15;
  wait1Msec(650);
  motor[motorArm] = 0;
}

void clearEncoders()
{
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;
}

void enterMoveFunction()
{
  encoderLastValue = 0;
  robotHeadingEachRun = 0;
  clearEncoders();
}

void exitMoveFunction()
{
  robotHeadingEachRun = 0;
  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;
  wait1Msec(100);
}

void integrateTurningGyro()
{
  float stupidRobotCDoesntWork = HTGYROreadRot(turningGyro);
  stupidRobotCDoesntWork = stupidRobotCDoesntWork/250;
  robotHeadingEachRun += stupidRobotCDoesntWork;
  wait1Msec(4);
}

float returnEncoderForwardValue(float tilesToMove)
{
	return (1440*tilesToMove)/(2*Pie*wheelRadius);
}
//**********************************************************************************************
void moveRobot(float numberOfTilesToMove, float wheelPower) //go forward
{
  enterMoveFunction();

  float encoderValueToMove = (24*returnEncoderForwardValue(numberOfTilesToMove));
  long j = 0;

  while(abs(nMotorEncoder[motorsLeft]) < abs(encoderValueToMove))
  {
    motor[motorsLeft] = wheelPower;
    motor[motorsRight] = wheelPower;
  }

  exitMoveFunction();
}
//**********************************************************************************************
void moveRobot(float degrees) //turn
{
  enterMoveFunction();
  int leftWheels;
  int rightWheels;

  if(degrees < 0) {leftWheels = -1; rightWheels = 1;} else {leftWheels = 1; rightWheels = -1;}

  while(abs(robotHeadingEachRun) < abs(degrees))
  {
    motor[motorsLeft] = 15*leftWheels;
    motor[motorsRight] = 15*rightWheels;
    integrateTurningGyro();
  }

  exitMoveFunction();
}
//**********************************************************************************************
void moveRobot(bool colorIsRed, bool colorIsBlue, bool colorIsWhite, bool colorIsRollingGoal, int wheelPower) //color sensors
{
  enterMoveFunction();
  bool colorHasBeenDetected = false;
  int _red; //For readcolorsensor
  int _green;
  int _blue;
  int minimumThreshold = 256; //For color sensor sum

  motor[motorsLeft] = wheelPower;
  motor[motorsRight] = wheelPower;

  int j = 0;

  while(!colorHasBeenDetected)
  {
	  if(colorIsRed == true)
	  {
	    if(SensorValue[colorLineDetector] == REDCOLOR) {colorHasBeenDetected = true;}
	  }

	  if(colorIsBlue == true)
	  {
	    if(SensorValue[colorLineDetector] == BLUECOLOR) {colorHasBeenDetected = true;}
	  }

	  if(colorIsWhite == true)
	  {
	    if(SensorValue[colorLineDetector] == WHITECOLOR) {colorHasBeenDetected = true;}
	  }

	  if(colorIsRollingGoal == true)
	  {
		HTCSreadRGB(colorHitechnicRollingGoal, _red, _green, _blue);
		int rgb = _red + _green + _blue;
		if(rgb > minimumThreshold) {colorHasBeenDetected = true;}
	  }
  }
  exitMoveFunction();
}
