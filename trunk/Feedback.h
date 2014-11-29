
//place feedback table from GenFeedbackTable.c here
int powerToSpeedTable[1] = {
	1
};

//must be less than 1000
#define CHECK_INTERVAL_MILLIS 200

//used to pass parameters to a task
int motorNumberParam;
float * multiplierParam;
bool paramsReceived = false;

task monitorFeedback()
{
	//read parameters from globals
	hogCPU();
	int motorNumber = motorNumberParam;
	float * multiplier = multiplierParam;
	paramsReceived = true;
	releaseCPU();

	//for averageing
	float rollingQueue[10];

	int startOfRollingQueue = 0;

	while(true)
	{
		nMotorEncoder[motorNumber] = 0;
		Sleep(CHECK_INTERVAL_MILLIS);

		int desiredSpeedDegreesPerSecond = powerToSpeedTable[motor[motorNumber]];

		int actualSpeedDegreesPerSecond = nMotorEncoder[motorNumber] / (1000 / CHECK_INTERVAL_MILLIS);

		float ratio = desiredSpeedDegreesPerSecond / actualSpeedDegreesPerSecond;

		rollingQueue[startOfRollingQueue] = ratio;

		//average numbers in queue
		int usefulNumbersInQueue = 0;
		int indexInQueue = startOfRollingQueue;

		float total = 0;

		for(int counter = 1; counter <= 10; ++counter)
		{
			if(indexInQueue >= 10)
			{
				indexInQueue = 0;
			}
			if(rollingQueue[indexInQueue] != 0)
			{
				++usefulNumbersInQueue;
				total += rollingQueue[indexInQueue];
			}

			++indexInQueue;
		}

		//avoid divide-by-0
		if(usefulNumbersInQueue == 0)
		{
			*multiplier = 1;
		}
		else
		{
			float avg = total / usefulNumbersInQueue;
			if(avg <= 1.05)
			{
				avg = 1;
			}

			*multiplier = avg;
		}


	}


}
