#pragma once
#include <time.h>
#include "SingleTonBase.h"
class RandomManager:public SingleTonBase<RandomManager>
{
public:
	RandomManager();
	~RandomManager();
	int GetInt(int num);
	int GetFromTo(int from, int to);
};

