#include "ButtonCommands.c"
#include "ManualCodeNewIsh.c"

#define mArmTurnq motor[motorArmTurn]

int lastPressed45 = -1;

void buttonControl()
{
  //Add: clamp open/close, sensitivity, link crate rotation
  /* X-1*/ if(btn(0)) {sensetivity = 0.5;}
  /* A-4*/ if(btn(1) && btn(3)) {liftArm();}
  /* B-3*/ if(btn(2)) {sensetivity = 3;}
  /* Y-4*/ if(btn(3)) {}
  /* LB */ if(btn(4)) {mArmFlappyThing = -50; lastPressed45 = 4;}
  /* RB */ if(btn(5)) {mArmFlappyThing = 45; lastPressed45 = 5;}
  /*    */ if(!btn(4) && !btn(5))
              {
                if(lastPressed45 == 5) {mArmFlappyThing = 50;}
                else {mArmFlappyThing = -15;}
              } //Apply resistance while idle
           int i = 0.1;
  /*LTRT*/ if(btn(6)) {i--;}
           if(btn(7)) {i++;}
           nxtDisplayTextLine(7, ""+i);
           mArmTurnq = i*100;

  /*Back*/ //if(btn(8)) {}
  /*Strt*/ if(btn(9)) {enableControlSwitch = !enableControlSwitch; while(btn(9)) {getJoystickSettings(joystick);}}
  /* L3 */ //if(btn(10)) {}
  /* R3 */ //if(btn(11)) {}
  //EndTimeSlice();
}
