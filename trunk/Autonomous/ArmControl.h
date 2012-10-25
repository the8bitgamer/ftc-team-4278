#define lowEnc 5600.0
#define midEnc 12600.0
#define hiEnc 19100.0

#define armThresh 25.0
#define mArm motor[motorArms]

task armLow() {
	float mMinSpeed = 20.0;
	float mMaxSpeed = 60.0;
	while(abs(nMotorEncoder[motorArms]-lowEnc) > armThresh) {
		float encoderOffset = (nMotorEncoder[motorArms] - lowEnc);
		mArm = (sgn(encoderOffset) * mMinSpeed) + (((mMaxSpeed-mMinSpeed)/lowEnc) * encoderOffset);
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
		mArm = (sgn(encoderOffset) * mMinSpeed) + (((mMaxSpeed-mMinSpeed)/hiEnc) * encoderOffset);
		EndTimeSlice();
	}
	mArm = 0;
}
