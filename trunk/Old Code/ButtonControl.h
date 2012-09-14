#include "ButtonCommands.h"

void buttonControl()
{
  //Add: clamp open/close, sensitivity, link crate rotation
  /* X-1*/ if(btn(0)) {sensetivity = 3.5;}
  /* A-4*/ if(btn(1)) {rotateClamp180();}
  /* B-3*/ if(btn(2)) {sensetivity = 0.5;}
  /* Y-4*/ if(btn(3)) {rotateClamp90();}
  /* LB */ if(btn(4)) {mArmFlappyThing = -60;}
  /* RB */ if(btn(5)) {mArmFlappyThing = 60;}
  /*    */ if(!btn(4) && !btn(5)) {mArmFlappyThing = -10;} //Apply resistance while idle
  /*LTRT*/ if(btn(6) && btn(7)) {liftArm();}
  /*Back*/ //if(btn(8)) {}
  /*Strt*/ //if(btn(9)) {}
  /* L3 */ //if(btn(10)) {}
  /* R3 */ //if(btn(11)) {}
}
