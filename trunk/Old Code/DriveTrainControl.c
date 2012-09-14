#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
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

//#include "JoystickDriver.c"

#define threshold 10
float sensetivity = 1;

bool rotationLock = false;
bool crateRotationLock = false;

static void controlArmTilt()
{
  if(abs(joystick.joy1_y2) > threshold) {mArm3 = -joystick.joy1_y2*3;} else {mArm3 = 0;}
  switch(joystick.joy1_TopHat)
  {
    case 7:
    case 1:
    case 0:
      mArm2 = 100; break;
    case 3:
    case 4:
    case 5:
      mArm2 = -100; break;
    default:
      mArm2 = -4; break;
  }
}

bool enableControlSwitch = false;

void switchControls()
{
  int tmpX1 = joystick.joy1_x1;
  joystick.joy1_x1 = joystick.joy1_x2;
  joystick.joy1_x2 = tmpX1;

  int tmpY1 = joystick.joy1_y1;
  joystick.joy1_y1 = joystick.joy1_y2;
  joystick.joy1_y2 = tmpY1;
}

void driveTrainControl()
{
  getJoystickSettings(joystick);
  if(enableControlSwitch) switchControls();

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

  controlArmTilt();
  //nxtDisplayTextLine(2, ""+joystick.joy1_x1);
  //nxtDisplayTextLine(3, ""+joystick.joy1_y1);
  //nxtDisplayTextLine(4, ""+joystick.joy1_y2);
  EndTimeSlice();
}
