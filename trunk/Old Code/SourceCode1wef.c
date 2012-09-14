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

task main()
{
  mArmFlappyThing = -100;
  motor[motorK] = 100;
  wait10Msec(300);
}
