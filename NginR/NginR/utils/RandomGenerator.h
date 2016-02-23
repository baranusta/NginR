#ifndef _RANDOMGENERATOR_H_
#define _RANDOMGENERATOR_H_

#include <stdlib.h>     
#include <time.h>     

class RandomGenerator
{
public:
	RandomGenerator(){
		srand(time(NULL));
	}
	int getInt();
	int getInt(int max);
	int getInt(int min, int max);
};

int RandomGenerator::getInt()
{
	return getInt(INT_MAX);
}

int RandomGenerator::getInt(int min, int max)
{
	if (max!=0)
		return rand() % max + min;
	return 0;
}

int RandomGenerator::getInt(int max)
{
	return getInt(0, max);
}

#endif