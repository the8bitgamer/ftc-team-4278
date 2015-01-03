
//place feedback table from GenFeedbackTable.c here
int powerToSpeedTable[101] = {
	0,	17,	0,	1,	107,	235,	888,	869,	1271,	1506,
	1696,	1866,	1975,	2097,	2252,	2398,	2349,	2518,	2624,	2703,
	2711,	2792,	2862,	2843,	2950,	3002,	2997,	3002,	3068,	3039,
	3191,	3204,	3197,	3186,	3196,	3290,	3264,	3274,	3347,	3297,
	3327,	3351,	3402,	3398,	3390,	3413,	3471,	3480,	3368,	3493,
	3473,	3518,	3434,	3506,	3571,	3437,	3590,	3540,	3499,	3546,
	3656,	3487,	3652,	3574,	3559,	3625,	3642,	3616,	3666,	3530,
	3707,	3627,	3621,	3632,	3630,	3677,	3692,	3615,	3656,	3789,
	3641,	3648,	3679,	3730,	3734,	3584,	3812,	3711,	3695,	3721,
	3633,	3759,	3686,	3805,	3618,	3768,	3758,	3746,	3706,	3709,
	3803};


//#define FEEDBACKDEBUG

//must be less than 1000
#define CHECK_INTERVAL_MILLIS 200

float multiplierLeft = 1;
float multiplierRight = 1;

bool encodersWereCleared = false;

/*
This function returns the power correction value for the motor(s) whose stats are given.

Returns 0 on failure.

*/

float updateSide(tMotor motorNumber, float * queue, int * startOfQueue, int * previousEncoderValue)
{
	if(encodersWereCleared)
	{
		//someone reset a motor encoder, probably one of the auto routines
		//so, fail and try again when we have reliable data
		encodersWereCleared = false;
		return 0;
	}

	int encoderDist = nMotorEncoder[motorNumber] - *previousEncoderValue;
	*previousEncoderValue = nMotorEncoder[motorNumber];
#ifdef FEEDBACKDEBUG
	writeDebugStreamLine("encoder distance traveled: %d", encoderDist);
#endif

#ifdef FEEDBACKDEBUG
	writeDebugStreamLine("motor: %s", motorNumber == mRight1 ? "right" : "left");
#endif
	int desiredSpeedDegreesPerSecond = powerToSpeedTable[abs(motor[motorNumber])];

#ifdef FEEDBACKDEBUG
	writeDebugStreamLine("desired speed in dps: %d", desiredSpeedDegreesPerSecond);
#endif
	int actualSpeedDegreesPerSecond = abs(encoderDist) * (1000 / CHECK_INTERVAL_MILLIS);

#ifdef FEEDBACKDEBUG
	writeDebugStreamLine("actual speed in dps: %d", actualSpeedDegreesPerSecond);
#endif

	float ratio;
	if(actualSpeedDegreesPerSecond == 0)
	{
		ratio = 1;
	}
	else
	{
		 ratio = desiredSpeedDegreesPerSecond / (float)actualSpeedDegreesPerSecond;
	}

#ifdef FEEDBACKDEBUG
	writeDebugStreamLine("corrective ratio: %f", ratio);
#endif

	queue[(*startOfQueue)++] = ratio;

	if(*startOfQueue > 9)
	{
		*startOfQueue = 0;
  }


	//average numbers in queue
	int usefulNumbersInQueue = 0;
	int indexInQueue = *startOfQueue;

	float total = 0;

	for(int counter = 1; counter <= 10; ++counter)
	{
		if(indexInQueue >= 10)
		{
			indexInQueue = 0;
		}
		if(queue[indexInQueue] != 0)
		{
			++usefulNumbersInQueue;
			total += queue[indexInQueue];
		}

		++indexInQueue;
	}

	//avoid divide-by-0
	if(usefulNumbersInQueue == 0)
	{
		return 1;
	}
	else
	{
		float avg = total / usefulNumbersInQueue;
		if(avg <= 1.05)
		{
			avg = 1;
		}

#ifdef FEEDBACKDEBUG
		writeDebugStreamLine("average corrective ratio: %f", avg);
#endif

		return avg;
	}
}

task monitorFeedback()
{
	//for averageing
	float rollingQueueLeft[10];
	float rollingQueueRight[10];

	int startOfRollingQueueLeft = 0;
	int startOfRollingQueueRight = 0;

	int previousEncoderValueRight = 0;
	int previousEncoderValueLeft = 0;

	nMotorEncoder[mRight1] = 0;
	nMotorEncoder[mLeft1] = 0;

	while(true)
	{
		Sleep(CHECK_INTERVAL_MILLIS);
		float rightValue = updateSide(mRight1, rollingQueueRight, &startOfRollingQueueRight, &previousEncoderValueRight);
		if(rightValue != 0)
		{
			multiplierRight = rightValue;
		}

		float leftValue = updateSide(mLeft1, rollingQueueLeft, &startOfRollingQueueLeft, &previousEncoderValueLeft);
		if(leftValue != 0)
		{
			multiplierLeft = leftValue;
		}
	}


}
