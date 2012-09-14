#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Sensor, S2,     ,                    sensorI2CMuxController)
#pragma config(Motor,  motorA,          motorArmTurn,  tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorF,        tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorArm1,     tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorArm3,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorArm2,     tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorArmFlappyThing, tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorK,        tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     motorRight,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_2,     motorLeft,     tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servoRot,             tServoStandard)
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

#define angleVal1 ((-nMotorEncoder[motorArm1]/4)/27)
#define angleVal2 ((-nMotorEncoder[motorArm2]/4)/9)
#define angleVal3 ((nMotorEncoder[motorArm3]/4)/9)
#define angleValTurn ((nMotorEncoder[motorArmTurn]/1)/3)
#define angleArmFlappyThingy ((nMotorEncoder[motorArmFlappyThing]/4)/1)

#define threshold 10

#define servoDegConv 255/180

float sensetivity = 1;

#include "JoystickDriver.c"
#include "JoystickReadWrite.c"

void driveTrainControl()
{
  //getJoystickSettings(joystick);
  //if(enableControlSwitch) switchControls();

  if(abs(joystick.joy1_y1) > threshold)   // If the right analog stick's Y-axis readings are either above or below the threshold:
  {
    motor[motorLeft] = joystick.joy1_y1 / (2*sensetivity);         // Motor B is assigned a power level equal to the right analog stick's Y-axis reading.
  }
  else                                    // Else if the readings are within the threshold:
  {
    motor[motorLeft] = 0;                        // Motor B is stopped with a power level of 0.
  }

  EndTimeSlice();
  if(abs(joystick.joy1_y1) > threshold)   // If the left analog stick's Y-axis readings are either above or below the threshold:
  {
    motor[motorRight] = joystick.joy1_y1 / (2*sensetivity);         // Motor C is assigned a power level equal to the left analog stick's Y-axis reading.
  }
  else                                    // Else if the readings are within the threshold:
  {
    motor[motorRight] = 0;                        // Motor C is stopped with a power level of 0.
  }

  if(abs(joystick.joy1_x1) > threshold)
  {
    motor[motorRight] -= joystick.joy1_x1 / (2*sensetivity);
    motor[motorLeft] += joystick.joy1_x1 / (2*sensetivity);

    if(abs(joystick.joy1_y1) < 30)
    {
      if(joystick.joy1_x1 < 0)
      {
        motor[motorRight] = (100/sensetivity);
        motor[motorLeft] = (-100/sensetivity);
      }
      else
      {
        motor[motorRight] = (-100/sensetivity);
        motor[motorLeft] = (100/sensetivity);
      }
    }
  }

  if(abs(joystick.joy1_y2) > threshold) {mArm3 = -joystick.joy1_y2*3;} else {mArm3 = 0;}
  switch(joystick.joy1_TopHat)
  {
    case 7:
    case 1:
    case 0:
      mArm2 = -100; break;
    case 3:
    case 4:
    case 5:
      mArm2 = 100; break;
    default:
      mArm2 = 0; break;
  }
  //nxtDisplayTextLine(2, ""+joystick.joy1_x1);
  //nxtDisplayTextLine(3, ""+joystick.joy1_y1);
  //nxtDisplayTextLine(4, ""+joystick.joy1_y2);
  EndTimeSlice();
}

int lastPressed45 = -1;

int btn(int btn)
  {return ((joystick.joy1_Buttons >> btn)%2 > 0);}

void liftArm()
{
  nMotorEncoder[motorArm1] = 0;
  nMotorEncoder[motorArm2] = 0;
  nMotorEncoder[motorArm3] = 0;
  nMotorEncoder[motorArmTurn] = 0;
  mArm1 = 0;
  mArm2 = 0;
  mArm3 = 0;
  mArmTurn = 0;
  motor[motorLeft] = 0;
  motor[motorRight] = 0;

  bool arm1Stopped = false;
  bool arm2Stopped = false;
  int targetArm1 = 89;
  int targetArm2 = 135;
  float pctComplete1 = 0;
  float pctComplete2 = 0;
  float sumTheta = 0;

  int tmpMotorPower = 0;
  int tmpMotorPower2 = 0;

  while(abs(angleVal1) < 40)
  {
    mArm1 = -80;
    int theta = (-angleVal1+angleVal3) - (angleVal2+angleValTurn);
    nxtDisplayTextLine(4, ""+angleVal3);
    if(abs(theta) > 5)
    {
      mArmTurn = 100*theta/abs(theta);
    }
  }
  PlaySound(soundBeepBeep);
  mArm1 = 0;
  nMotorEncoder[motorArm1] = 0;

  while(!arm1Stopped && !arm2Stopped)
  {
    pctComplete1 = angleVal1;
    pctComplete1 = pctComplete1/targetArm1;
    pctComplete1 = abs(pctComplete1);
    pctComplete2 = angleVal2;
    pctComplete2 = pctComplete2/targetArm2;
    pctComplete2 = abs(pctComplete2);

    if(pctComplete1 > pctComplete2)
    {
      tmpMotorPower = 0;
      tmpMotorPower2 = -100;
    }
    else
    {
      tmpMotorPower2 = 0;
      tmpMotorPower = -100;
    }

    if(pctComplete1 > 1)
    {
      tmpMotorPower = 0;
      arm1Stopped = true;
    }
    if(pctComplete2 > 1)
    {
      tmpMotorPower2 = 0;
      arm2Stopped = true;
    }
    nxtDisplayTextLine(5, ""+pctComplete1);
    nxtDisplayTextLine(4, ""+pctComplete2);
    mArm1 = tmpMotorPower;
    mArm2 = tmpMotorPower2;

    sumTheta = angleVal1 - angleVal2;
    if(sumTheta > 5) mArmTurn = 60;
    if(sumTheta < -5) mArmTurn = -60;
    if(sumTheta < 5 && sumTheta > -5) mArmTurn = 0;

    int theta = (-angleVal1+angleVal3)/2 - (angleVal2+angleValTurn);
    nxtDisplayTextLine(4, ""+angleVal3);
    if(abs(theta) > 5)
    {
      mArmTurn = 100*theta/abs(theta);
    }
  }
  mArm1 = 0;
  mArm2 = 0;
}

void liftArmManual()
{
  PlaySound(soundBeepBeep);
  nMotorEncoder[motorArm1] = 0;
  nMotorEncoder[motorArm2] = 0;
  nMotorEncoder[motorArm3] = 0;
  nMotorEncoder[motorArmTurn] = 0;
  while(true)
  {
    getJoystickSettings(joystick);
    if(abs(joystick.joy1_y1) > threshold)
      {mArm1 = joystick.joy1_y1*128/100;}
    else {mArm1 = 0;}

    if(abs(joystick.joy1_y2) > threshold)
      {mArm2 = -joystick.joy1_y2*128/100;}
    else {mArm2 = 0;}
  }
}

void liftArmTest()
{
  nMotorEncoder[motorArm1] = 0;
  nMotorEncoder[motorArm2] = 0;
  nMotorEncoder[motorArm3] = 0;
  nMotorEncoder[motorArmTurn] = 0;
  mArmTurn = 0;
  eraseDisplay();
  //nxtDisplayTextLine(5, ""+angleVal2);
  while(abs(angleVal1) < 90) {mArm1 = -70; getJoystickSettings(joystick); mArmTurn = joystick.joy1_y1;} mArm1 = 0; //95

  wait1Msec(750);
  while(abs(angleVal2) < 060) {mArm2 = -100; getJoystickSettings(joystick); mArmTurn = joystick.joy1_y1;} mArm2 = 0; //60
  while(abs(angleVal2) < 085) {mArm2 = -60; getJoystickSettings(joystick); mArmTurn = joystick.joy1_y1;} mArm2 = 0; //85
  while(abs(angleVal2) < 100) {mArm2 = -20; getJoystickSettings(joystick); mArmTurn = joystick.joy1_y1;} mArm2 = 0; //100

  wait1Msec(500);
  while(abs(angleVal1) < 115) {mArm1 = -50; getJoystickSettings(joystick); mArmTurn = joystick.joy1_y1;} mArm1 = 0; //115

  wait1Msec(500);
  while(abs(angleVal2) < 125) {mArm2 = -30; getJoystickSettings(joystick); mArmTurn = joystick.joy1_y1;} mArm2 = 0; //120

  wait1Msec(500);
  while(abs(angleVal3) < 74) {mArm3 = 40; getJoystickSettings(joystick); mArmTurn = joystick.joy1_y1;} mArm3 = 0; //72
  //while(abs(angleValTurn) < 105) {mArmTurn = -100;} mArmTurn = 0;


  while(true);
}

void buttonControl()
{
  //Add: clamp open/close, sensitivity, link crate rotation
  /* X-1*/ if(btn(0)) {sensetivity = 0.5;}
  /* A-4*/ if(btn(1) && btn(3)) {liftArmTest();}
  /* B-3*/ if(btn(2)) {sensetivity = 3;}
  /* Y-4*/ if(btn(3)) {}
  /* LB */ if(btn(4)) {mArmFlappyThing = -45; lastPressed45 = 4;}
  /* RB */ if(btn(5)) {mArmFlappyThing = 45; lastPressed45 = 5;}
  /*    */ if(!btn(4) && !btn(5))
              {
                if(lastPressed45 == 5) {mArmFlappyThing = 50;}
                else {mArmFlappyThing = -15;}
              } //Apply resistance while idle
           int i = 0;
  /*LTRT*/ if(btn(6)) {i--; nMotorEncoder[motorArm3] = 0; nMotorEncoder[motorArmTurn] = 0;}
           if(btn(7)) {i++; nMotorEncoder[motorArm3] = 0; nMotorEncoder[motorArmTurn] = 0;}
           //nxtDisplayTextLine(7, ""+i);
           mArmTurn = -i*100;

  /*Back*/ //if(btn(8)) {}
  /*Strt*/ //if(btn(9)) {enableControlSwitch = !enableControlSwitch; while(btn(9)) {getJoystickSettings(joystick);}}
  /* L3 */ //if(btn(10)) {}
  /* R3 */ //if(btn(11)) {}
  //EndTimeSlice();
}

int chooseFile()
{
  int choice = 1;
  bool choiceMade = false;
  while(!choiceMade)
  {
    switch(choice)
    {
      case 1:
        nxtDisplayTextLine(2, "AutoR1.txt");
        break;
      case 2:
        nxtDisplayTextLine(2, "AutoR2.txt");
        break;
      case 3:
        nxtDisplayTextLine(2, "AutoB1.txt");
        break;
      case 4:
        nxtDisplayTextLine(2, "AutoB2.txt");
        break;
      default:
        if(choice == 5) choice = 1;
        if(choice == 0) choice = 5;
        break;
    }
    if(nNxtButtonPressed == 3) return choice;
    if(nNxtButtonPressed == 1) {choice++; while(nNxtButtonPressed == 1);}
    if(nNxtButtonPressed == 2) {choice--; while(nNxtButtonPressed == 2);}
  }
  return -1;
}

task main()
{
  eraseDisplay();
  int t = chooseFile();
  if(t == 1) recordInit("AutoR1.txt");
  if(t == 2) recordInit("AutoR2.txt");
  if(t == 3) recordInit("AutoB1.txt");
  if(t == 4) recordInit("AutoB2.txt");
  //waitForStart();
  while(true)
  {
    servo[servoRot] = 165-servoDegConv*angleArmFlappyThingy;

    int theta = (-angleVal1+angleVal3) - (angleVal2+angleValTurn);
    nxtDisplayTextLine(4, ""+angleVal3);
    if(abs(theta) > 5)
    {
      if(!btn(6) && !btn(7)) mArmTurn = 100*theta/abs(theta);
    }
      nxtDisplayTextLine(6, ""+theta);
      getJoystickSettings(joystick);
		    recordJoystickValue((byte)joystick.joy1_y1);
		    recordJoystickValue((byte)joystick.joy1_x1);
		    recordJoystickValue((byte)joystick.joy1_y2);
		    recordJoystickValue((int)joystick.joy1_Buttons);
		    recordJoystickValue((byte)joystick.joy1_TopHat);
		    nxtDisplayTextLine(3, ""+joystick.joy1_y1);
		    nxtDisplayTextLine(4, ""+joystick.joy1_x1);
		    nxtDisplayTextLine(5, ""+joystick.joy1_y2);
		    nxtDisplayTextLine(6, ""+joystick.joy1_Buttons);
		    nxtDisplayTextLine(7, ""+joystick.joy1_TopHat);
		    if(nIoResult == ioRsltEofExpected)
		    {
		      motor[motorLeft] = 0;
		      motor[motorRight] = 0;
		      mArm1 = 0;
		      mArm2 = 0;
		      mArm3 = 0;
		      mArmTurn = 0;
		      mArmFlappyThing = 0;
		      while(true) PlaySound(soundBeepBeep);
		    } else {wait1Msec(10);}
		  //motor[motorB] = joystick.joy1_y1;
      driveTrainControl();
      buttonControl();
  }
}
