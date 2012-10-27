#define lowEnc 5100.0
#define midEnc 13000.0
#define hiEnc 19900.0

#define armThresh 200.0
#define mArm motor[motorArms]

task armLow() {
	float mMinSpeed = 20.0;
	float mMaxSpeed = 60.0;
	while(abs(nMotorEncoder[motorArms]-lowEnc) > armThresh) {
		float encoderOffset = (nMotorEncoder[motorArms] - lowEnc);
		int j = (int)((sgn(encoderOffset) * mMinSpeed) + (((mMaxSpeed-mMinSpeed)/lowEnc) * encoderOffset));
		mArm = j;
		EndTimeSlice();
	}
	mArm = 0;
}

task armMid() {
	while(abs(nMotorEncoder[motorArms]-midEnc) > armThresh) {
		float encoderOffset = (nMotorEncoder[motorArms] - midEnc);
		float xz = sgn(encoderOffset) * 50;
		mArm = xz;
		nxtDisplayTextLine(3, "%f", abs(encoderOffset));
		nxtDisplayTextLine(4, "%i", nMotorEncoder[motorArms]);
		nxtDisplayTextLine(5, "%f", xz);
		nxtDisplayTextLine(6, "%i", motor[motorArms]);
		EndTimeSlice();
	}
	mArm = 0;
	nxtDisplayTextLine(7, "Done.");
}

task armHi() {
	float mMinSpeed = 30.0;
	float mMaxSpeed = 90.0;
	while(abs(nMotorEncoder[motorArms]-hiEnc) > armThresh) {
		float encoderOffset = (-1.0)*nMotorEncoder[motorArms] - hiEnc;
		int j = (int)((sgn(encoderOffset) * mMinSpeed) + (((mMaxSpeed-mMinSpeed)/hiEnc) * encoderOffset));
		mArm = j;
		EndTimeSlice();
	}
	mArm = 0;
}
