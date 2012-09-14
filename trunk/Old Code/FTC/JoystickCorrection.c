typedef struct {
  bool    UserMode;          // Autonomous or Telep-Operated mode
	bool    StopPgm;           // Stop program

	short   joy1_x1;           // -128 to +127
	short   joy1_y1;           // -128 to +127
	short   joy1_x2;           // -128 to +127
	short   joy1_y2;           // -128 to +127
	short   joy1_Buttons;      // Bit map for 12-buttons
	short   joy1_TopHat;       // value -1 = not pressed, otherwise 0 to 7 for selected "octant".

	short   joy2_x1;           // -128 to +127
	short   joy2_y1;           // -128 to +127
	short   joy2_x2;           // -128 to +127
	short   joy2_y2;           // -128 to +127
	short   joy2_Buttons;      // Bit map for 12-buttons
	short   joy2_TopHat;       // value -1 = not pressed, otherwise 0 to 7 for selected "octant".
} JoyMon;

#include "JoystickDriverX.c"

JoyMon firstUpdate;
JoyMon secondUpdate;
JoyMon thirdUpdate;
JoyMon fourthUpdate;
JoyMon accurateUpdate;

void updateJoyInfo(TJoystick joy)
{
  if(joy.joy1_x1 + firstUpdate.joy1_x1 + secondUpdate.joy1_x1 + thirdUpdate.joy1_x1 + fourthUpdate.joy1_x1 == 0)
  {accurateUpdate.joy1_x1 = 0;} else {if(joy.joy1_x1 != 0) accurateUpdate.joy1_x1 = joy.joy1_x1;}

  if(joy.joy1_y1 + firstUpdate.joy1_y1 + secondUpdate.joy1_y1 + thirdUpdate.joy1_y1 + fourthUpdate.joy1_y1 == 0)
  {accurateUpdate.joy1_y1 = 0;} else {if(joy.joy1_y1 != 0) accurateUpdate.joy1_y1 = joy.joy1_y1;}

  if(joy.joy1_x2 + firstUpdate.joy1_x2 + secondUpdate.joy1_x2 + thirdUpdate.joy1_x2 + fourthUpdate.joy1_x2 == 0)
  {accurateUpdate.joy1_x2 = 0;} else {if(joy.joy1_x2 != 0) accurateUpdate.joy1_x2 = joy.joy1_x2;}

  if(joy.joy1_y2 + firstUpdate.joy1_y2 + secondUpdate.joy1_y2 + thirdUpdate.joy1_y2 + fourthUpdate.joy1_y2 == 0)
  {accurateUpdate.joy1_y2 = 0;} else {if(joy.joy1_y2 != 0) accurateUpdate.joy1_y2 = joy.joy1_y2;}

  if(joy.joy1_Buttons + firstUpdate.joy1_Buttons + secondUpdate.joy1_Buttons + thirdUpdate.joy1_Buttons + fourthUpdate.joy1_Buttons == 0)
  {accurateUpdate.joy1_Buttons = 0;} else {if(joy.joy1_Buttons != 0) accurateUpdate.joy1_Buttons = joy.joy1_Buttons;}

  memcpy(fourthUpdate, thirdUpdate, sizeof(fourthUpdate));
  memcpy(thirdUpdate, secondUpdate, sizeof(thirdUpdate));
  memcpy(secondUpdate, firstUpdate, sizeof(secondUpdate));
  memcpy(firstUpdate, joy, sizeof(firstUpdate));

  nxtDisplayTextLine(2, ""+accurateUpdate.joy1_Buttons);
  nxtDisplayTextLine(3, ""+firstUpdate.joy1_Buttons);
  nxtDisplayTextLine(4, ""+secondUpdate.joy1_Buttons);
  nxtDisplayTextLine(5, ""+thirdUpdate.joy1_Buttons);
  nxtDisplayTextLine(6, ""+fourthUpdate.joy1_Buttons);
}

task main()
{
  while(true)
  {
    getJoystickSettings(joystick);
    updateJoyInfo(joystick);
  }
}
