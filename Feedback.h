
//place feedback table from GenFeedbackTable.c here
int powerToSpeedTable[101] = {
	2796,
	3736,
	3706,
	3744,
	3688,
	3692,
	3880,
	3540,
	3704,
	3872,
	3664,
	3716,
	3498,
	3858,
	3716,
	3690,
	3668,
	3664,
	3518,
	3830,
	3650,
	3666,
	3492,
	3666,
	3824,
	3498,
	3634,
	3618,
	3626,
	3646,
	3610,
	3578,
	3618,
	3600,
	3586,
	3760,
	3582,
	3570,
	3556,
	3576,
	3404,
	3552,
	3514,
	3556,
	3518,
	3498,
	3660,
	3342,
	3648,
	3462,
	3310,
	3490,
	3440,
	3400,
	3436,
	3410,
	3396,
	3382,
	3384,
	3346,
	3324,
	3308,
	3300,
	3276,
	3222,
	3264,
	3216,
	3156,
	3132,
	3138,
	3100,
	3034,
	3020,
	2978,
	2922,
	2868,
	2860,
	2800,
	2726,
	2684,
	2626,
	2540,
	2462,
	2368,
	2284,
	2176,
	2048,
	1936,
	1786,
	1692,
	1452,
	1400,
	1076,
	940,
	862,
	398,
	104,
	0,
	0,
	0,
	0,
};

//#define FEEDBACKDEBUG

//must be less than 1000
#define CHECK_INTERVAL_MILLIS 100

float multiplierLeft = 1;
float multiplierRight = 1;


/*
This function returns the power correction value for the motor(s) whose stats are given.

Returns 0 on failure.

*/
float updateSide(tMotor motorNumber, float * queue, int * startOfQueue, int * previousEncoderValue)
{

	if(nMotorEncoder[motorNumber] < *previousEncoderValue)
	{
		//someone reset a motor encoder, probably one of the auto routines
		//fail and try again when we have reliable data
		*previousEncoderValue = nMotorEncoder[motorNumber];
		return 0;
	}

	int encoderDist = nMotorEncoder[motorNumber] - *previousEncoderValue;
	*previousEncoderValue = nMotorEncoder[motorNumber];

#ifdef FEEDBACKDEBUG
	writeDebugStreamLine("motor: %s", motorNumber == mRight1 ? "right" : "left");
#endif
	int desiredSpeedDegreesPerSecond = powerToSpeedTable[100 - abs(motor[motorNumber])];

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

	nMotorEncoder[mRight2] = 0;
	nMotorEncoder[mLeft1] = 0;

	while(true)
	{
		Sleep(CHECK_INTERVAL_MILLIS);
		float rightValue = updateSide(mRight2, rollingQueueRight, &startOfRollingQueueRight, &previousEncoderValueRight);
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
