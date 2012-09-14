#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Motor,  motorA,          motorArmTurn,  tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorRight,    tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorLeft,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorArm1,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorArm3,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorArm2,     tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     motorArmFlappyThingy, tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorNormal, openLoop)

task main()
{
  motor[motorArm1] = -20;
  wait1Msec(500);
}
