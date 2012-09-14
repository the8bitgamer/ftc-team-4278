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
//void moveRobot(float xVal, float yVal, bool areCoordinates);
float robotHeadingEachRun = 0;
float robotHeadingLastRun = 0;
float robotOverallHeading = 0;
float robotX = 0;
float robotY = 0;

float encoderLastValue = 0;

/*Change log:
VERSION 3
--Added move-to-heading with 3rd quadrant glitch.
*/

void initializeRobot(bool onLeftSide)
{
  if(onLeftSide) {robotOverallHeading = 90;} else {robotOverallHeading = -90; robotX = 6;}
  HTGYROstartCal(turningGyro);
}

void gyroHighSpeedSafety()
{
  /*float sensetivity = .0001;
  if(abs(robotHeadingLastRun) - abs(robotHeadingEachRun) < -sensetivity || abs(robotHeadingLastRun) - abs(robotHeadingEachRun) > sensetivity)
  {
    while(true)
    {
      motor[motorsLeft] = 0;
      motor[motorsRight] = 0;
    }
  }
  */
}

void gyroLowSpeedSafety()
{
  //Not very safe
}

void checkSafeties(bool goingForward)
{
  if(goingForward) {gyroHighSpeedSafety();}
  if(!goingForward) {gyroLowSpeedSafety();}
}

float returnEncoderForwardValue(float tilesToMove)
{
	return (1440*tilesToMove)/(2*Pie*wheelRadius);
}

float returnSquaresTravelled(float tilesToMove)
{
  float tempVal = tilesToMove/1440;
  tempVal = tempVal*2*Pie*wheelRadius;
  return tempVal/24;
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

void exitMoveFunction() //Turning exit needs no values
{
  robotOverallHeading += robotHeadingEachRun;
  robotHeadingEachRun = 0;
  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;
  wait1Msec(100);

  roundRobotHeadingValues();
}

void roundRobotValues()
{
  robotX = robotX * 100;
  robotY = robotY * 100;
  robotOverallHeading = robotOverallHeading * 100;

  robotX = floor(robotX)/100;
  robotY = floor(robotY)/100;
  robotOverallHeading = floor(robotOverallHeading)/100;
}

void exitMoveFunction(float distanceTravelled)
{
  float squaresTravelled = returnSquaresTravelled(nMotorEncoder[motorsLeft]);

  robotOverallHeading += robotHeadingEachRun;

  float deltaY = sinDegrees(-robotOverallHeading+90)*squaresTravelled;
  float deltaX = cosDegrees(-robotOverallHeading+90)*squaresTravelled;
  robotX += deltaX;
  robotY += deltaY;

  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;
  wait1Msec(100);

  roundRobotValues();
}

void integrateTurningGyro()
{
  float stupidRobotCDoesntWork = HTGYROreadRot(turningGyro);
  stupidRobotCDoesntWork = stupidRobotCDoesntWork/250;
  robotHeadingEachRun += stupidRobotCDoesntWork;
  wait1Msec(4);
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

  robotHeadingLastRun = robotHeadingEachRun;
  integrateTurningGyro();
  checkSafeties(true);

  exitMoveFunction(numberOfTilesToMove);
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
    motor[motorsLeft] = 20*leftWheels;
    motor[motorsRight] = 20*rightWheels;
    integrateTurningGyro();
    checkSafeties(false);
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
	  integrateTurningGyro();
	  checkSafeties(true);
  }
  exitMoveFunction(90);
}
//**********************************************************************************************

void moveRobot(float xVal, float yVal, bool areCoordinates)
{
  enterMoveFunction();
  float deltaXVal = xVal - robotX;
  float deltaYVal = yVal - robotY;

  if(yVal > 1) {return;}

  float deltaAngle = atan(deltaYVal/deltaXVal);//Returns value in radians
  deltaAngle = (deltaAngle * 180)/Pie;

  if(deltaXVal < 0 && deltaYVal < 0) {deltaAngle = deltaAngle * -1; deltaAngle = deltaAngle - 90;} //Compensate for arcTrig domain restriction
  if(deltaXVal <= 0 && deltaYVal >= 0) {deltaAngle = deltaAngle * -1; deltaAngle = deltaAngle + 90;}

  deltaAngle -= 90;
  deltaAngle = deltaAngle * -1;

  moveRobot(deltaAngle - robotOverallHeading);
  moveRobot(sqrt((deltaXVal*deltaXVal)+(deltaYVal*deltaYVal)), 50);

  exitMoveFunction();
}
