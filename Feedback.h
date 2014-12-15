
//place feedback table from GenFeedbackTable.c here
int powerToSpeedTable[101] = {
	2996,	3678,	3698,	3628,	3640,	3696,	3666,	3644,	3672,	3672,
	3614,	3636,	3664,	3668,	3584,	3612,	3636,	3626,	3614,	3640,
	3636,	3584,	3598,	3616,	3610,	3738,	3608,	3426,	3572,	3554,
	3624,	3608,	3508,	3722,	3400,	3572,	3662,	3528,	3546,	3356,
	3682,	3498,	3362,	3486,	3656,	3336,	3494,	3600,	3434,	3456,
	3440,	3398,	3416,	3420,	3398,	3330,	3370,	3372,	3298,	3320,
	3342,	3326,	3220,	3222,	3256,	3216,	3142,	3198,	3180,	3092,
	3086,	3048,	3048,	2954,	2928,	2902,	2856,	2800,	2774,	2720,
	2610,	2582,	2480,	2402,	2280,	2216,	2126,	1990,	1868,	1720,
	1530,	1382,	1204,	964,	930,	582,	142,	0,	0,	0, 0};

//#define FEEDBACKDEBUG

//must be less than 1000
#define CHECK_INTERVAL_MILLIS 200

float multiplierLeft = 1;
float multiplierRight = 1;

bool encodersWereCleared = true;

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
	nMotorEncoder[mLeft2] = 0;

	while(true)
	{
		Sleep(CHECK_INTERVAL_MILLIS);
		float rightValue = updateSide(mRight1, rollingQueueRight, &startOfRollingQueueRight, &previousEncoderValueRight);
		if(rightValue != 0)
		{
			multiplierRight = rightValue;
		}

		float leftValue = updateSide(mLeft2, rollingQueueLeft, &startOfRollingQueueLeft, &previousEncoderValueLeft);
		if(leftValue != 0)
		{
			multiplierLeft = leftValue;
		}
	}


}
