#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{

  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;

  nMotorEncoderTarget[motorD] = (1440)*5;
  nMotorEncoderTarget[motorE] = (1440)*5;

  motor[motorD] = 100;
  motor[motorE] = 100;

  while (nMotorRunState[motorE] != runStateIdle)
  {

  }

  motor[motorE] = 0;
  motor[motorD] = 0;

  wait1Msec(3000);

}
