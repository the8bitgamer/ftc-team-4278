
//place feedback table from GenFeedbackTable.c here


int powerToSpeedTable[101] = {
	0,	7,	0,	0,	0,	4,	41,	72,	7,	154,
	298,	812,	881,	972,	1092,	1240,	1374,	1439,	1584,	1676,
	1741,	1826,	1932,	1998,	2038,	2146,	2178,	2262,	2320,	2353,
	2427,	2429,	2489,	2526,	2564,	2575,	2548,	2637,	2669,	2711,
	2752,	2791,	2772,	2826,	2853,	2891,	2864,	2905,	2941,	2950,
	2935,	3006,	2949,	3026,	3025,	3001,	3049,	3058,	3048,	3082,
	3091,	3072,	3120,	3152,	3079,	3151,	3169,	3161,	3168,	3153,
	3200,	3175,	3236,	3233,	3200,	3248,	3256,	3271,	3238,	3296,
	3306,	3272,	3288,	3330,	3316,	3317,	3385,	3312,	3387,	3373,
	3330,	3384,	3340,	3393,	3364,	3396,	3400,	3368,	3425,	3438,
	3462};


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
		if(avg <= 1.02)
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
	nMotorEncoder[mLeft2] = 0;

	while(true)
	{
		Sleep(CHECK_INTERVAL_MILLIS);
		float rightValue = updateSide(mRight2, rollingQueueRight, &startOfRollingQueueRight, &previousEncoderValueRight);
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
