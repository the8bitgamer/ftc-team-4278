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

float forward(int dist)
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

bool checkGyroTurn(int gyroValue) {return false; /*checks if turning is complete*/}
bool checkEncVal(int targetDist) {return false;}

void moveRobot(float targetDist, float gyroTargetVal, float leftWheelPower, float rightRatioVal, bool colorTargetIsRed, bool colorTargetIsBlue, bool colorTargetIsWhite, bool colorTargetSumVal, int encoderExitByDefault)
{
  //targetDist is the target distance value
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

  while(exitMove == false)
  {

  if(targetDist != nil)
  {
    exitMove = checkEncVal(targetDist);
  }

  motor[motorsLeft] = leftWheelPower;
  motor[motorsRight] = leftWheelPower*rightRatioVal;

  if(forward(24*encoderExitByDefault) < nMotorEncoder[motorsLeft]) {freezeRobot();}
  if(forward(24*encoderExitByDefault) < nMotorEncoder[motorsRight]) {freezeRobot();}

  gyroTurn += gyroTurningIntegrate(); //Integrate the gyroscope value

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

  if(gyroTargetVal != nil) //Check if turning is complete
  {
    exitMove = checkGyroTurn(gyroTurn);
  }

  //Realignment
  }
}
