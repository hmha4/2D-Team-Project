#include "stdafx.h"
#include "RandomManager.h"


RandomManager::RandomManager()
{
	srand(GetTickCount());
}


RandomManager::~RandomManager()
{
}

int RandomManager::GetInt(int num)
{
	return rand() % num;
}

int RandomManager::GetFromTo(int from, int to)
{
	return rand() % (to - from) + from;
}
