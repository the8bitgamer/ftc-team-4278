]#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Sensor, S2,     ,                    sensorI2CMuxController)
#pragma config(Motor,  motorA,          motorArmTurn,  tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorF,        tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorArm1,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorArm3,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorArm2,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorArmFlappyThing, tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorK,        tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     motorRight,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     motorLeft,     tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servoRot,             tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define mArm1 motor[motorArm1]
#define mArm2 motor[motorArm2]
#define mArm3 motor[motorArm3]
#define mArmTurn motor[motorArmTurn]
#define mArmFlappyThing motor[motorArmFlappyThing]

#define angleVal1 ((nMotorEncoder[motorArm1]/4)/27)
#define angleVal2 ((nMotorEncoder[motorArm2]/4)/9)
#define angleVal3 ((nMotorEncoder[motorArm3]/4)/9)
#define angleValTurn ((nMotorEncoder[motorArmTurn]/3)/1)
#define angleArmFlappyThingy ((nMotorEncoder[motorArmFlappyThing]/4)/1)

#include "DriveTrainControl.c"

int btn(int btn)
  {return ((joystick.joy1_Buttons >> btn)%2 > 0);}

void liftArm()
{
  //mArmFlappyThing = 10;
  int targetAngle1 = 130;
  int targetAngle2 = 130;
  int targetAngle3 = 90;
  int targetAngleTurn = 130;
  bool stopArm1 = false;
  bool stopArm2 = false;
  bool stopArm3 = false;
  bool stopArmTurn = false;

  while(!stopArm1 || !stopArm2 || !stopArm3 || !stopArmTurn)
  {
    //Define arms as percent complete
    //Intended compatability with all angles
    //float pctComplete1 = abs((angleVal1 / targetAngle1));
    float pctComplete1 = angleVal1;
    pctComplete1 = pctComplete1 / targetAngle1;
    pctComplete1 = abs(pctComplete1);
    //float pctComplete2 = abs((angleVal2 / targetAngle2));
    float pctComplete2 = angleVal2;
    pctComplete2 = pctComplete2 / targetAngle2;
    pctComplete2 = abs(pctComplete2);
    //float pctComplete3 = abs((angleVal3 / targetAngle3));
    float pctComplete3 = angleVal3;
    pctComplete3 = pctComplete3 / targetAngle3;
    pctComplete3 = abs(pctComplete3);
    //float pctCompleteTurn = abs((angleValTurn / targetAngleTurn));
    float pctCompleteTurn = angleValTurn;
    pctCompleteTurn = pctCompleteTurn / targetAngleTurn;
    pctCompleteTurn = abs(pctCompleteTurn);

    nxtDisplayTextLine(2, ""+floor(pctComplete1*100)+", "+floor(pctComplete2*100)+", "+floor(pctComplete3*100));

    //Check for arm rotation complete, if true, stop arm seg
    if(pctComplete1 > 1) stopArm1 = true;
    if(pctComplete2 > 1) stopArm2 = true;
    if(pctComplete3 > 1) stopArm3 = true;
    if(pctCompleteTurn > 1) stopArmTurn = true;

    //Find slowest arm
    int slowArm = -1;
    if(pctComplete1 < pctComplete2 && pctComplete1 < pctComplete3 && pctComplete1 < pctCompleteTurn) slowArm = 1;
    if(pctComplete2 < pctComplete1 && pctComplete2 < pctComplete3 && pctComplete2 < pctCompleteTurn) slowArm = 2;
    if(pctComplete3 < pctComplete2 && pctComplete3 < pctComplete1 && pctComplete3 < pctCompleteTurn) slowArm = 3;
    if(pctCompleteTurn < pctComplete2 && pctCompleteTurn < pctComplete3 && pctCompleteTurn < pctComplete1) slowArm = 4;

    //Find fastest arm
    int fastArm = -1;
    if(pctComplete1 > pctComplete2 && pctComplete1 > pctComplete3 && pctComplete1 > pctCompleteTurn) slowArm = 1;
    if(pctComplete2 > pctComplete1 && pctComplete2 > pctComplete3 && pctComplete2 > pctCompleteTurn) slowArm = 2;
    if(pctComplete3 > pctComplete2 && pctComplete3 > pctComplete1 && pctComplete3 > pctCompleteTurn) slowArm = 3;
    if(pctCompleteTurn > pctComplete2 && pctCompleteTurn > pctComplete3 && pctCompleteTurn > pctComplete1) slowArm = 4;

    //Assign all to default medium speeds
    //Set to tmp for storage to reduce jitter
    int tmpArm1 = 90;
    int tmpArm2 = 20;
    int tmpArm3 = 20;
    int tmpArmTurn = 40;

    //Speed up slowest arm
    switch(slowArm)
    {
      case 1:
        tmpArm1 = 95; break;
      case 2:
        tmpArm2 = 50; break;
      case 3:
        tmpArm3 = 50; break;
      case 4:
        tmpArmTurn = 100; break;
      default:
        PlaySound(soundException); break;
    }
    nxtDisplayTextLine(6, "SA: "+slowArm);

    //Slow down fastest arm
    switch(fastArm)
    {
      case 1:
        tmpArm1 = 30; break;
      case 2:
        tmpArm2 = 10; break;
      case 3:
        tmpArm3 = 10; break;
      case 4:
        tmpArmTurn = 30; break;
      default:
        PlaySound(soundException); break;
    }
    nxtDisplayTextLine(7, "FA: "+fastArm);

    //Assign new values to motors
    //Also stops all motors before last exit
    if(!stopArm1) {mArm1 = -tmpArm1;} else {mArm1 = 0;}
    if(!stopArm2) {mArm2 = tmpArm2;} else {mArm2 = 0;}
    if(!stopArm3) {mArm3 = tmpArm3;} else {mArm3 = 0;}
    if(!stopArmTurn) {mArmTurn = tmpArmTurn;} else {mArmTurn = 0;}
    driveTrainControl();
  }
}

void rotateClamp180()
{
  nMotorEncoder[motorArmTurn] = 0;
  nMotorEncoder[motorArm2] = 0;
  nMotorEncoder[motorArm3] = 0;
  rotationLock = true;
  while(abs(angleValTurn) < 180)
  {
    mArmTurn = -40;
    getJoystickSettings(joystick);
    driveTrainControl();
  }
  mArmTurn = 0;
  rotationLock = false;
  nMotorEncoder[motorArmTurn] = 0;
  nMotorEncoder[motorArm2] = 0;
  nMotorEncoder[motorArm3] = 0;
}

void rotateClamp90()
{
  nMotorEncoder[motorArmTurn] = 0;
  nMotorEncoder[motorArm2] = 0;
  nMotorEncoder[motorArm3] = 0;
  rotationLock = true;
  while(abs(angleValTurn) < 90)
  {
    mArmTurn = -40;
    getJoystickSettings(joystick);
    driveTrainControl();
  }
  mArmTurn = 0;
  rotationLock = false;
  nMotorEncoder[motorArmTurn] = 0;
  nMotorEncoder[motorArm2] = 0;
  nMotorEncoder[motorArm3] = 0;
}
