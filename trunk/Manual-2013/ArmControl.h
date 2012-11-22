#define lowEnc 8100.0
#define midEnc 14500.0
#define hiEnc 22050.0

#define armThresh 200.0
#define motArmR motor[motorAmrR]
#define motArmL motor[motorAmrL]

task armLow() {
	int l = 65*(nMotorEncoder[motorAmrR]<lowEnc?1:-1)+(nMotorEncoder[motorAmrR]<lowEnc?-10:10);
	int r = 65*(nMotorEncoder[motorAmrR]<lowEnc?1:-1);
	motArmL = l;
	motArmR = r;
	while(abs(nMotorEncoder[motorAmrR]-lowEnc) > 200) {nxtDisplayTextLine(3, "%i", nMotorEncoder[motorAmrR]); EndTimeSlice();}
	motArmL = 0;
	motArmR = 0;
}

task armMid() {
	int l = 65*(nMotorEncoder[motorAmrR]<midEnc?1:-1)+(nMotorEncoder[motorAmrR]<midEnc?-10:10);
	int r = 65*(nMotorEncoder[motorAmrR]<midEnc?1:-1);
	motArmL = l;
	motArmR = r;
	while(abs(nMotorEncoder[motorAmrR]-midEnc) > 200) {nxtDisplayTextLine(3, "%i", nMotorEncoder[motorAmrR]); EndTimeSlice();}
	motArmL = 0;
	motArmR = 0;
}

task armHi() {
	int l = 65*(nMotorEncoder[motorAmrR]<hiEnc?1:-1)+(nMotorEncoder[motorAmrR]<hiEnc?-10:10);
	int r = 65*(nMotorEncoder[motorAmrR]<hiEnc?1:-1);
	motArmL = l;
	motArmR = r;
	while(abs(nMotorEncoder[motorAmrR]-hiEnc) > 200) {nxtDisplayTextLine(3, "%i", nMotorEncoder[motorAmrR]); EndTimeSlice();}
	motArmL = 0;
	motArmR = 0;
}
