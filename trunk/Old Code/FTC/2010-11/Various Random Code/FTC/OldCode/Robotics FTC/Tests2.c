#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{
  while(1 == 1)
  {
    getJoystickSettings(joystick);
    if(joy1Btn(1)) {motor[motorE] = 100;}
    if(joy1Btn(2)) {motor[motorE] = 0;}
  }
}
