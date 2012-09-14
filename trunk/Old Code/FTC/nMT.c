#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorE,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorD,        tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     arm0,          tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     ballCup,       tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     arm2,          tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     arm1,          tmotorNormal, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C2_3,    crateBinding,         tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define mDriveRight motor[driveRight]
#define mDriveLeft motor[driveLeft]
#define mBallCup motor[ballCup]
#define mArm0 motor[arm0]
#define mArm1 motor[arm1]
#define mArm2 motor[arm2]
#define sCrateBinding servo[crateBinding]
#define sBallCatch servo[ballCatch]
#define aPow 75

#define servoForward 100
#define servoBackward -100
#define servoHalt 0

#define servoLocked 255
#define servoUnlocked 0

#include "UpdatedJoystickDriver.c"

//Version 1.3

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
  nMotorEncoder[arm1] = 0;
  return;
}
/*
void starwars()
{
PlayTone(695, 14); while(bSoundActive);
PlayTone(695, 14); while(bSoundActive);
PlayTone(695, 14); while(bSoundActive);
PlayTone(929, 83); while(bSoundActive);
PlayTone(1401, 83); while(bSoundActive);
PlayTone(1251, 14); while(bSoundActive);
PlayTone(1188, 14); while(bSoundActive);
PlayTone(1054, 14); while(bSoundActive);
PlayTone(1841, 83); while(bSoundActive);
PlayTone(1401, 41); while(bSoundActive);
PlayTone(1251, 14); while(bSoundActive);
PlayTone(1188, 14); while(bSoundActive);
PlayTone(1054, 14); while(bSoundActive);
PlayTone(1841, 83); while(bSoundActive);
PlayTone(1401, 41); while(bSoundActive);
PlayTone(1251, 14); while(bSoundActive);
PlayTone(1188, 14); while(bSoundActive);
PlayTone(1251, 14); while(bSoundActive);
PlayTone(1054, 55); while(bSoundActive);
wait1Msec(280);
PlayTone(695, 14); while(bSoundActive);
PlayTone(695, 14); while(bSoundActive);
PlayTone(695, 14); while(bSoundActive);
PlayTone(929, 83); while(bSoundActive);
PlayTone(1401, 83); while(bSoundActive);
PlayTone(1251, 14); while(bSoundActive);
PlayTone(1188, 14); while(bSoundActive);
PlayTone(1054, 14); while(bSoundActive);
PlayTone(1841, 83); while(bSoundActive);
PlayTone(1401, 41); while(bSoundActive);
PlayTone(1251, 14); while(bSoundActive);
PlayTone(1188, 14); while(bSoundActive);
PlayTone(1054, 14); while(bSoundActive);
PlayTone(1841, 83); while(bSoundActive);
PlayTone(1401, 41); while(bSoundActive);
PlayTone(1251, 14); while(bSoundActive);
PlayTone(1188, 14); while(bSoundActive);
PlayTone(1251, 14); while(bSoundActive);
PlayTone(1054, 55); while(bSoundActive);
}*/
task main()
{
  //motor[ballCup] = 100;
  //while(true);
  sCrateBinding = 0;
  int sVal = 2550;
  initializeRobot();
  //waitForStart();

  int threshold = 10;             /* Int 'threshold' will allow us to ignore low       */
  float sensetivity = 1;
  int ud = 1;
  int fix = 1;

  while(true)                            // Infinite loop:
  {
    //if(joy1Btn(1)) {sensetivity = .8; }
    //if(joy1Btn(3)) {sensetivity = 3.5; }

    getJoystickSettings(joystick);
    if(abs(joystick.joy1_y1) > threshold)   // If the left analog stick's Y-axis readings are either above or below the threshold:
    {
      motor[arm1] = joystick.joy1_y1 / (2*sensetivity);         // Motor C is assigned a power level equal to the left analog stick's Y-axis reading.
    }
    else                                    // Else if the readings are within the threshold:
    {
      motor[arm1] = 0;                        // Motor C is stopped with a power level of 0.
    }
    if(abs(joystick.joy1_y2) > threshold)   // If the left analog stick's Y-axis readings are either above or below the threshold:
    {
      motor[arm0] = aPow;         // Motor C is assigned a power level equal to the left analog stick's Y-axis reading.
    }
    else                                    // Else if the readings are within the threshold:
    {
      motor[arm0] = 0;                        // Motor C is stopped with a power level of 0.
    }
    int buttonTemp = joystick.joy1_Buttons;
    //nxtDisplayTextLine(3, ""+buttonTemp);
    nxtDisplayTextLine(4, ""+buttonTemp);
    nxtDisplayTextLine(2, ""+joystick.joy1_y1);
    nxtDisplayTextLine(3, ""+joystick.joy1_x1);
    bool rTPressed = false;
    if(buttonTemp >= 2048) /*R3*/ {buttonTemp -= 2048;}
    if(buttonTemp >= 1024) /*L3*/ {buttonTemp -= 1024;}
    if(buttonTemp >= 512) /*Start*/ {buttonTemp -= 512; sensetivity = 3.5;}
    if(buttonTemp >= 256) /*Back*/ {buttonTemp -= 256; sensetivity = .3;}
    if(buttonTemp >= 128) /*RT*/ {buttonTemp -= 128; rTPressed = true;} else {rTPressed = false;}
    if(buttonTemp >= 64) /*LT*/
    {
      buttonTemp -= 64;
    }
    if(buttonTemp >= 32) /*RB*/ {buttonTemp -= 32;}
    if(buttonTemp >= 16) /*LB*/ {buttonTemp -= 16;}
    if(buttonTemp >= 8) /*Y (4) (Top)*/ {buttonTemp -= 8;}
    if(buttonTemp >= 4) /*B (3) (Right)*/ {buttonTemp -= 4;}
    if(buttonTemp >= 2) /*A (2) (Bottom)*/
    {
      buttonTemp -= 2;
    }
    if(buttonTemp >= 1) /*X (1) (Left)*/ {buttonTemp -= 1;}
  }
  wait1Msec(100);
}
