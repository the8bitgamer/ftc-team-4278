#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     colorPort,           sensorCOLORFULL)
#pragma config(Sensor, S1,     HTGYRO,              sensorRawValue)
#pragma config(Motor,  motorA,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorC,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorsLeft,    tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorNormal, openLoop, encoder)

#const tSensors GyroSensor = (tSensors) S3;

#include "JoystickDriver.c"
#include "drivers/HTGYRO-driver.h"

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}

float forward(float dist, float wheelRadius)
{
  float Pie = 3.14159;
  return (1440*dist)/(2*Pie*wheelRadius);
}

float turn(float wheelRadius, float distBtwnWheels, float degreesToTurn)
{
  return ((4*degreesToTurn*distBtwnWheels)/wheelRadius)/2;
}

void makeFD(float dist, int power, float wR, float dBW)
{
  //int powerCompensation = (power*27)/50;
  int powerCompensation = power;
  dist = dist * 24;
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  motor[motorsRight] = power;
  motor[motorsLeft] = powerCompensation;

  while(nMotorEncoder[motorsLeft] < forward(dist, wR)) {}

  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;
  wait1Msec(500);
}

void makeRight(float degrees, float power, float wR, float dBW)
{
  degrees = degrees * 90;
  power = power * 25;
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  motor[motorsLeft] = power;
  motor[motorsRight] = -power;

  while(nMotorEncoder[motorsLeft] < turn(wR, dBW, degrees)) {}

  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;

  wait1Msec(500);
}

void makeLeft(float degrees, float power, float wR, float dBW)
{
  degrees = degrees * 90;
  power = power * 25;
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  motor[motorsLeft] = -power;
  motor[motorsRight] = power;

  while(nMotorEncoder[motorsLeft] > -turn(wR, dBW, degrees)) {}

  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;

  wait1Msec(500);
}

void reorientGyro(int degrees)
{
  long gVal;
  gVal = SensorValue(GyroSensor);
}

task main()
{
  initializeRobot();
  //waitForStart();
  float wR = 2;
  float dBW = 17.5;
  int bool1 = 0;
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  makeFD(1, 80, wR, dBW);
  makeLeft(1, 15, wR, dBW);
  makeFD(.8, 100, wR, dBW);
  makeRight(1, 15, wR, dBW);

  motor[motorsLeft] = 15;
  motor[motorsRight] = 15;
  while(bool1 == 0)
  {
	  switch(SensorValue[colorPort])
	  {
	    case REDCOLOR: motor[motorsLeft] = 0; motor[motorsRight] = 0; bool1 = 1; break;
	    case BLUECOLOR: motor[motorsLeft] = 0; motor[motorsRight] = 0; bool1 = 1; break;
	  }
  }

  makeFD(.5, 15, wR, dBW);

  wait1Msec(5000);

  bool1 = 0;

  motor[motorsRight] = 15;
  motor[motorsLeft] = 15;


  while(bool1 == 0)
  {
    if(SensorValue[colorPort] == WHITECOLOR)
    {
      motor[motorsLeft] = 0;
      motor[motorsRight] = 0;
      bool1 = 1;
    }
  }
}
