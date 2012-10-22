#define lowEnc 5600.0
#define midEnc 12600.0
#define hiEnc 19100.0

#define armThresh 50.0
#define mArm motor[motorArms]

task armLow() {
	float mMinSpeed = 17.0;
	float mMaxSpeed = 60.0;
	while(abs(nMotorEncoder[motorArms]-lowEnc) > armThresh) {
		float encoderOffset = (-1.0)*nMotorEncoder[motorArms] - lowEnc;
		mArm = (sgn(encoderOffset) * mMinSpeed) + (((mMaxSpeed-mMinSpeed)/lowEnc) * encoderOffset);
		EndTimeSlice();
	}
	mArm = 0;
}

task armMid() {
	float mMinSpeed = 20.0;
	float mMaxSpeed = 70.0;
	while(abs(nMotorEncoder[motorArms]-midEnc) > armThresh) {
		float encoderOffset = (-1.0)*nMotorEncoder[motorArms] - midEnc;
		mArm = (sgn(encoderOffset) * mMinSpeed) + (((mMaxSpeed-mMinSpeed)/midEnc) * encoderOffset);
		EndTimeSlice();
	}
	mArm = 0;
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
