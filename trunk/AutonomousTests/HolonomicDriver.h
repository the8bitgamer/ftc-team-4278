
float targetRobotTh=0, targetMoveTh=0, targetMoveMag=0;
tMotor mBL, mFR, mBR, mFL;

#define mBackLeft motor[mBL]
#define mFrontRight motor[mFR]
#define mBackRight motor[mBR]
#define mFrontLeft motor[mFL]

void setupMotors(tMotor mBLz, tMotor mFRz, tMotor mBRz, tMotor mFLz) {
	mBL = mBLz;
	mFR = mFRz;
	mBR = mBRz;
	mFL = mFLz;
}

task HolonomicControl()
{
	while(true) {
		float th = targetMoveTh;
		float v = targetMoveMag;
		float rot = 0.5*((robotTh+targetRobotTh)/abs(robotTh+targetRobotTh));
		float gyr = degreesToRadians(robotTh);

		float mBackLeftTmp = (cos(th+(PI/4)-gyr)*v) - rot/1.5;
		float mFrontRightTmp = (cos(th+(PI/4)-gyr)*v) + rot/1.5;
		float mBackRightTmp = -1 * (sin(th+(PI/4)-gyr)*v) - rot/1.5;
		float mFrontLeftTmp = -1 * (sin(th+(PI/4)-gyr)*v) + rot/1.5;

		float max = 1;
		if(abs(mBackLeftTmp) > abs(max)) max = mBackLeftTmp;
		if(abs(mFrontRightTmp) > abs(max)) max = mFrontRightTmp;
		if(abs(mBackRightTmp) > abs(max)) max = mBackRightTmp;
		if(abs(mFrontLeftTmp) > abs(max)) max = mFrontLeftTmp;
		max = abs(max);

		mBackLeft = 100 * mBackLeftTmp / max;
		mFrontRight = 100 * mFrontRightTmp / max;
		mBackRight = 100 * mBackRightTmp / max;
		mFrontLeft = 100 * mFrontLeftTmp / max;
		EndTimeSlice();
	}
}

void stopMotors()
{
  mBackLeft = 0;
  mBackRight = 0;
  mFrontLeft = 0;
  mFrontRight = 0;
}

float getTheta(float x, float y) {return atan2(x,y);}
