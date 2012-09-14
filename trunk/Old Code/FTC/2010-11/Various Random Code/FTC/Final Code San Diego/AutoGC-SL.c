#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S3,     HTCS,                sensorLowSpeed)
#pragma config(Sensor, S2,     colorPort,           sensorCOLORFULL)
#pragma config(Motor,  motorA,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorC,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorsLeft,    tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorArm,      tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorNormal, openLoop)
#pragma config(Sensor, S4,     GyroSensor,          sensorRawValue)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "drivers/common.h"
#include "drivers/HTCS-driver.h"
#include "drivers/HTGYRO-driver.h"

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
  HTGYROstartCal(GyroSensor);
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

void specialBackward()
{
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;
  motor[motorsLeft] = -10;
  motor[motorsRight] = -10;
  while(nMotorEncoder[motorsLeft] > -((1440*12)/(2*3.14*2))) {}
}



void makeBKWD(float dist, int power, float wR, float dBW)
{
  //int powerCompensation = (power*27)/50;
  int powerCompensation = power;
  int gyroCompensationRight = 0;
  int gyroCompensationLeft = 0;
  float summationValue = 0;
  float gyroValue = 0;

  dist = dist * 24;
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  while(-nMotorEncoder[motorsLeft] < forward(dist, wR))
  {
    //gyroValue = HTGYROreadRot(GyroSensor);
    //summationValue += gyroValue;
    //gyroCompensationRight = -gyroValue;
    //gyroCompensationLeft = gyroValue;
    motor[motorsRight] = power + (gyroCompensationRight/2);
    motor[motorsLeft] = power + (gyroCompensationLeft/2);
    //if(summationValue > -1 && summationValue < 1) {gyroCompensationLeft = 0; gyroCompensationRight = 0;}
  }

  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;
  wait1Msec(500);

}

void makeFD(float dist, int power, float wR, float dBW)
{
  //int powerCompensation = (power*27)/50;
  int powerCompensation = power;
  int gyroCompensationRight = 0;
  int gyroCompensationLeft = 0;
  float summationValue = 0;
  float gyroValue = 0;

  dist = dist * 24;
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  while(nMotorEncoder[motorsLeft] < forward(dist, wR))
  {
    gyroValue = HTGYROreadRot(GyroSensor);
    summationValue += gyroValue;
    gyroCompensationRight = gyroValue;
    gyroCompensationLeft = -gyroValue;
    motor[motorsRight] = power + (gyroCompensationRight/2);
    motor[motorsLeft] = power + (gyroCompensationLeft/2);
    if(summationValue > -1 && summationValue < 1) {gyroCompensationLeft = 0; gyroCompensationRight = 0;}
  }

  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;
  wait1Msec(500);

}

void makeRight(int degrees)
{
  float summationValue = 0;
  float gyroValue = 0;
  bool movementValid = true;
  while(movementValid == true)
  {
    motor[motorsRight] = -15;
    motor[motorsLeft] = 15;
    gyroValue = HTGYROreadRot(GyroSensor);
    summationValue += gyroValue/250;
    if (summationValue > degrees)
    {
      movementValid = false;
    }
    wait1Msec(4);
  }

  motor[motorsRight] = 0;
  motor[motorsLeft] = 0;
  summationValue = 0;
}



void makeLeft(int degrees)
{
  float summationValue = 0;
  float gyroValue = 0;
  bool movementValid = true;
  while(movementValid == true)
  {
    motor[motorsRight] = 15;
    motor[motorsLeft] = -15;
    gyroValue = HTGYROreadRot(GyroSensor);
    summationValue += gyroValue/250;
    if (summationValue < -degrees)
    {
      movementValid = false;
    }
    wait1Msec(4);
  }
  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;
  summationValue = 0;
}

void oldAutonomousMod()
{
  float wR = 2;
  float dBW = 17.5;

  int bool1 = 0;
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

//  makeLeft(.5, 10, wR, dBW);

  motor[motorsLeft] = 40;
  motor[motorsRight] = 40;
  while(bool1 == 0)
  {

    if(nMotorEncoder[motorsLeft] < forward(36, 2)) {bool1 = 0;} else {while(true) {motor[motorsRight] = 0;motor[motorsLeft] = 0;}}
    //if(nMotorEncoder[motorsRight] < forward(36, 2)) {bool1 = 0;} else {while(true) {motor[motorsRight] = 0;motor[motorsLeft] = 0;}}

	  switch(SensorValue[colorPort])
	  {
	    case REDCOLOR: motor[motorsLeft] = 0; motor[motorsRight] = 0; bool1 = 1; break;
	    case BLUECOLOR: motor[motorsLeft] = 0; motor[motorsRight] = 0; bool1 = 1; break;
	  }
  }

  makeFD(.6, 15, wR, dBW);

  wait1Msec(10000); //TIME

  bool1 = 0;

  motor[motorsRight] = 15;
  motor[motorsLeft] = 15;

  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  while(bool1 == 0)
  {
    if(nMotorEncoder[motorsLeft] < forward(18, 2)) {bool1 = 0;} else {while(true) {motor[motorsRight] = 0;motor[motorsLeft] = 0;}}
    if(SensorValue[colorPort] == WHITECOLOR)
    {
      motor[motorsLeft] = 0;
      motor[motorsRight] = 0;
      bool1 = 1;
    }

  }

  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;

  makeFD(.05, 15, wR, dBW);
}

task main()
{

  initializeRobot();
  waitForStart();
//  wait1Msec(2000);

  float wR = 2;
  float dBW = 17.5;
  int red = 0;
  int green = 0;
  int blue = 0;
  int _color = 0;
  int _colorindex = 0;
  string _tmp;
  int val = 255;

  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  int bool2 = 0;

  makeFD(.92, 15, wR, dBW);
  makeLeft(40);

  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  HTCSreadRGB(HTCS, red, green, blue);
  motor[motorsLeft] = 12;
  motor[motorsRight] = 12;
  wait1Msec(100);
  while((red + green + blue) < 200)
  {
    HTCSreadRGB(HTCS, red, green, blue);
    motor[motorsLeft] = 8;
    motor[motorsRight] = 8;
  }

  wait1Msec(150);

  motor[motorsLeft] = 0; //Raise and lower arm
  motor[motorsRight] = 0;

  wait1Msec(1500);

  motor[motorArm] = -40;
  wait1Msec(700);
  motor[motorArm] = 0;

  wait1Msec(1000);

  motor[motorArm] = 15;
  wait1Msec(650);
  motor[motorArm] = 0;

  /*wait1Msec(2000);

  motor[motorsLeft] = -20;
  motor[motorsRight] = -20;

  while(nMotorEncoder[motorsLeft] > 0) {}
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  wait1Msec(2000);

  makeLeft(45); //Turn

  makeFD(.7, 30, wR, dBW);
  makeRight(90);
  nMotorEncoder[motorsLeft] = 0;
  makeFD(.5, 30, wR, dBW);

  specialBackward();

  makeLeft(90);*/

  //MOD ZONE
  /*
  makeRight(10);
  makeFD(0.9, 40, wR, dBW);
  wait1Msec(250);
  makeBKWD(1.2, -40, wR, dBW);
  makeLeft(55);

  oldAutonomousMod();*/
  //</modzone>

  //arcRotate();

  //oldAutonomousMod();

  makeBKWD(.5, -30, wR, dBW);
  makeLeft(45);
}
