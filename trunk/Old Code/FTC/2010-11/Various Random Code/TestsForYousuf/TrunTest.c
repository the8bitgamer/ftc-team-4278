#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorsLeft,    tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorNormal, openLoop, encoder)
#pragma config(Sensor, S2, HTSMUX, sensorLowSpeed)

#include "drivers/HTGYRO-driver.h"
/*
Function Name- getGyroData();

Purpose - read data from a HiTechnic Gyroscopic Sensor

Notes:
When using, be sure to initalize the Gyroscopic sensor using HTGYROstartCal() (in initializeRobot())
Make sure to name gyroscopic sensor "HTGYRO" or "msensor_S2_1"
*/
float getGyroData()
{
  float heading = 0.0;
  long currTime;
  long prevTime = nPgmTime;

  currTime = nPgmTime;
  heading += ((float)HTGYROreadRot(msensor_S2_1))*(currTime - prevTime)/1000;      // Integrate values from the gyroscopid sensor
  prevTime = currTime;                                                             //
  return heading;
}

/*
Function Name- gyroTurn

Purpose - turn using a HiTechnic Gyroscopic Sensor

Arguments:
target = # of degrees to turn
buffer = # of degrees to buffer +- the target, prevents "wiggle"
power = motor power of the turn
leftMotor = name of the motor on the left
rightMotor = name of the motor on the right
HTGYRO = name of the Gyroscopic sensor to use

Notes:
When using, be sure to initalize the Gyroscopic sensor using HTGYROstartCal(HTGYRO)
Make sure to name gyroscopic sensor "HTGYRO"
*/
void gyroTurn(long target, long buffer, int power)
{
  while(true)
  {
    float heading = getGyroData();                                                   // Read Gyroscopic sensor

    if(heading < (target - buffer))                                                  // LOGIC- If to the right of target, turn left
    {                                                                                //
      motor[motorsLeft] = power;                                                      //
      motor[motorsRight] = -power;                                                    //
    }else if(heading > (target + buffer))                                            // LOGIC- If to the left of target, turn right
    {                                                                                //
      motor[motorsLeft] = -power;                                                     //
      motor[motorsRight] = power;                                                     //
    }else if(heading < (target + buffer) && heading > (target - buffer))             // LOGIC- If within the buffer zone, stop
    {                                                                                //
      motor[motorsLeft] = 0;                                                          //
      motor[motorsLeft] = 0;                                                         //
      return;                                                                        // Exit the function
    }
  }
}

task main()
{
  HTGYROstartCal(msensor_S2_1);
  gyroTurn(90, 1, 20);
}
