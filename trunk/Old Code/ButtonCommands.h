#define mArm1 motor[motorArm1]
#define mArm2 motor[motorArm2]
#define mArm3 motor[motorArm3]
#define mArmTurn motor[motorArmTurn]
#define mArmFlappyThing motor[motorArmFlappyThingy]

#define angleVal1 ((nMotorEncoder[motorArm1]/4)/27)
#define angleVal2 ((nMotorEncoder[motorArm2]/4)/9)
#define angleVal3 ((nMotorEncoder[motorArm3]/4)/9)
#define angleValTurn ((nMotorEncoder[motorArmTurn]/4)/3)
#define angleArmFlappyThing ((nMotorEncoder[motorArmFlappyThing]/4)/1)

#include "DriveTrainControl.h"

int btn(int btn)
  {return ((joystick.joy1_Buttons >> btn)%2 > 0);}

void liftArm()
{
  mArmFlappyThing = 10;
  int targetAngle1 = 130;
  int targetAngle2 = 130;
  int targetAngle3 = 130;
  int targetAngleTurn = 130;
  bool stopArm1 = false;
  bool stopArm2 = false;
  bool stopArm3 = false;
  bool stopArmTurn = false;

  while(!stopArm1 || !stopArm2 || !stopArm3 || !stopArmTurn)
  {
    //Define arms as percent complete
    //Intended compatability with all angles
    float pctComplete1 = abs((angleVal1 / targetAngle1));
    float pctComplete2 = abs((angleVal2 / targetAngle2));
    float pctComplete3 = abs((angleVal3 / targetAngle3));
    float pctCompleteTurn = abs((angleValTurn / targetAngleTurn));

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
    int tmpArm1 = 70;
    int tmpArm2 = 70;
    int tmpArm3 = 70;
    int tmpArmTurn = 70;

    //Speed up slowest arm
    switch(slowArm)
    {
      case 1:
        tmpArm1 = 100; break;
      case 2:
        tmpArm2 = 100; break;
      case 3:
        tmpArm3 = 100; break;
      case 4:
        tmpArmTurn = 100; break;
      default:
        PlaySound(soundException); break;
    }

    //Slow down fastest arm
    switch(fastArm)
    {
      case 1:
        tmpArm1 = 30; break;
      case 2:
        tmpArm2 = 30; break;
      case 3:
        tmpArm3 = 30; break;
      case 4:
        tmpArmTurn = 30; break;
      default:
        PlaySound(soundException); break;
    }

    //Assign new values to motors
    //Also stops all motors before last exit
    if(!stopArm1) {mArm1 = tmpArm1;} else {mArm1 = 0;}
    if(!stopArm2) {mArm2 = tmpArm2;} else {mArm2 = 0;}
    if(!stopArm3) {mArm3 = tmpArm3;} else {mArm3 = 0;}
    if(!stopArmTurn) {mArmTurn = tmpArmTurn;} else {mArmTurn = 0;}
    driveTrainControl();
  }
}

void rotateClamp180()
{
  nMotorEncoder[motorArmTurn] = 0;
  int nTarget = 50;

  while(abs(nMotorEncoder[motorArmTurn]) < nTarget)
  {
    mArmTurn = -60;
    driveTrainControl();
  }
}

void rotateClamp90()
{
  nMotorEncoder[motorArmTurn] = 0;
  int nTarget = 50;

  while(abs(nMotorEncoder[motorArmTurn]) < nTarget)
  {
    mArmTurn = -60;
    driveTrainControl();
  }
}
