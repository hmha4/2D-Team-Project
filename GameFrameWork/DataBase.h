#pragma once
#include "SingleTonBase.h"
#include <map>

class DataBase : public SingleTonBase<DataBase>
{
private:
	typedef map<string, int>			mData;
	typedef map<string, int>::iterator	mDataIter;

	mData _mData;
public:
	DataBase();
	~DataBase();

	void Release();

	void SaveData(string name, int num);
	int LoadData(string name);
};

