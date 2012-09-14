#include "JoystickDriver.c"

task main()
{
  while(true)
  {
    getJoystickSettings(joystick);
    motor[motorA] = joystick.joy1_y1;
  }
}
