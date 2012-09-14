#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Motor,  motorA,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorC,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorsLeft,    tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorNormal, openLoop, encoder)

#include "JoystickDriver.c"

float forward(float dist, float wheelRadius)
{
  float Pie = 3.14159;
  return (1440*dist)/(2*Pie*wheelRadius);
}

float turn(float wheelRadius, float distBtwnWheels, float degreesToTurn)
{
  //return (((4*degreesToTurn*distBtwnWheels)/wheelRadius)/2 - 60);
  return ((4*degreesToTurn*distBtwnWheels)/wheelRadius)/2;
}

void makeFD(float dist, int power, float wR, float dBW)
{
  int powerCompensation = (power*27)/50;
  dist = dist * 24;
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

 // nMotorEncoderTarget[motorsLeft] = forward(dist, wR);
 // nMotorEncoderTarget[motorsRight] = forward(dist, wR);

  motor[motorsRight] = power;
  motor[motorsLeft] = powerCompensation;

  while(nMotorEncoder[motorsLeft] < forward(dist, wR)) {}

  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;

  PlayTone(695, 60); while(bSoundActive);
}

void makeRight(float degrees, float power, float wR, float dBW)
{
  degrees = degrees * 90;
  power = power * 25;
  //int powerCompensate = power - (power / 4);
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  //nMotorEncoderTarget[motorsLeft] = turn(wR, dBW, degrees);
  //nMotorEncoderTarget[motorsRight] = -turn(wR, dBW, degrees);

  motor[motorsLeft] = power;
  motor[motorsRight] = -power;

  while(nMotorEncoder[motorsLeft] < turn(wR, dBW, degrees)) {}

  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;

  PlayTone(695, 60); while(bSoundActive);
}

void makeLeft(float degrees, float power, float wR, float dBW)
{
  degrees = degrees * 90;
  power = power * 25;
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

  //nMotorEncoderTarget[motorsLeft] = -turn(wR, dBW, degrees);
  //nMotorEncoderTarget[motorsRight] = (turn(wR, dBW, degrees) + 30);

  motor[motorsLeft] = -power;
  motor[motorsRight] = power;

  while(nMotorEncoder[motorsLeft] > -turn(wR, dBW, degrees)) {}

  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;

  PlayTone(695, 60); while(bSoundActive);
}

task main()
{
 // waitForStart();
  float wR = 2;
  float dBW = 17.5;
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;
  while(true)
  {
    getJoystickSettings(joystick);
    if(joy1Btn(1))
    {
      makeLeft(1, 15, wR, dBW);
    }

    if(joy1Btn(2))
    {
      makeFD(5, 100, wR, dBW);
    }

    if(joy1Btn(3))
    {
      makeRight(1, 15, wR, dBW);
    }

    if(joy1Btn(4))
    {
      makeFD(1, 100, wR, dBW);
    }

    if(joy1Btn(5))
    {
      makeFD(1, 80, wR, dBW);
      makeLeft(1, 15, wR, dBW);
      makeFD(1, 80, wR, dBW);
      makeRight(1, 15, wR, dBW);
      makeFD(.6, 80, wR, dBW);
      wait1Msec(10000);
      makeFD(.7, 80, wR, dBW);
    }
  }
}
