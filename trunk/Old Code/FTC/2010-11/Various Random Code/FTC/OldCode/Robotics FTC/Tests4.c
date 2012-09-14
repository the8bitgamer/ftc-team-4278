#include "JoystickDriver.c"

task main()
{
  getJoystickSettings(joystick);
  while(1 == 1)
  {
    if(joy1Btn(1))
    {
       while(joy1Btn(1)
       {
         motor[motorB] = 75; //Threshold = 65 min 75 max
         motor[motorC] = 75;
         //wait1Msec(10);
       }
       motor[motorB] = 0;
       motor[motorC] = 0;
    }

    if(joy1Btn(2))
    {
       while(joy1Btn(2)
       {
         motor[motorB] = -25; //Threshold = 65 min 75 max
         motor[motorC] = -25;
         //wait1Msec(10);
       }
       motor[motorB] = 0;
       motor[motorC] = 0;
    }
  }
}
