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

void makeFD(float dist, int rPower, int lPower, float wR, float dBW)
{
  //int powerCompensation = power - (power / 25);
  dist = dist * 24;
  nMotorEncoder[motorsLeft] = 0;
  nMotorEncoder[motorsRight] = 0;

 // nMotorEncoderTarget[motorsLeft] = forward(dist, wR);
 // nMotorEncoderTarget[motorsRight] = forward(dist, wR);

  motor[motorsRight] = rPower;
  motor[motorsLeft] = lPower;

  while(nMotorEncoder[motorsLeft] < forward(dist, wR)) {}

  motor[motorsLeft] = 0;
  motor[motorsRight] = 0;

  PlayTone(695, 60); while(bSoundActive);
}

task main()
{
	eraseDisplay();
  //nxtDisplayTextLine(2, "Text chk %d", 100);
	float wR = 2;
	float dBW = 17.5;
	int max = 100;
	int min = 0;
	int leftPower = 100;
	int conf2 = 0;
	int rightPower = 100;
	//nxtDisplayTextLine(3, "Right: %d", rightPower);

	/*
	MODIFYING LEFT WHEELS

	Start at 100 power
	Drop by 10 until a minimum is established
n
	Take average of max and min; go forward at that power
	User input: left or right drift
		If left drift, assign new value to minimum
		If right drift, assign new value to maximum
	Repeat until UI says okay, then display value.

	syntax variation: makeFD(tiles, right wheel power, left wheel power, wR, dBW);
	MAXIMUM WORST CASE SCENARIO: 6.64 (7) ITERATIONS
	*/


	int confirm = 0;
	while(confirm == 0)
	{
		makeFD(5, rightPower, leftPower, wR, dBW);
		conf2 = 0;
		while(conf2 == 0)
		{
			getJoystickSettings(joystick);
			if(joy1Btn(2)) {conf2 = 1; leftPower = leftPower - 10;} //REDUCE POWER
			if(joy1Btn(4)) {conf2 = 1; confirm = 1; min = leftPower;} //POWER IS FINE; SET TO MINIMUM
		}
		conf2 = 0;
	}
	confirm = 0;
	//MAX AND MIN ESTABLISHED

	while(confirm == 0)
	{
		leftPower = (max + min) / 2;
		makeFD(5, rightPower, leftPower, wR, dBW);
		while(conf2 == 0)
		{
			getJoystickSettings(joystick);
			if(joy1Btn(1)) {min = leftPower; conf2 = 1;}  //DRIFTS LEFT
			if(joy1Btn(3)) {max = leftPower; conf2 = 1;} //DRIFTS RIGHT
			if(joy1Btn(4)) {conf2 = 1; confirm = 1;} //TEST CHECKS OUT
			if(joy1Btn(2)) {conf2 = 1;}            //RETRY TEST
		}
		conf2 = 0;
	}
	confirm = 0;


  nxtDisplayString(2, "Left: %d", leftPower);

	while(true) {}

}
