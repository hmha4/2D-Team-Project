#include "stdafx.h"
#include "DataBase.h"


DataBase::DataBase()
{
}


DataBase::~DataBase()
{
}

void DataBase::Release()
{
	_mData.clear();
}

void DataBase::SaveData(string name, int num)
{
	mDataIter mIter = _mData.find(name);

	if (mIter != _mData.end())
	{
		_mData[name] = num;
		return;
	}

	_mData.insert(make_pair(name, num));
}

int DataBase::LoadData(string name)
{
	mDataIter mIter = _mData.find(name);

	if (mIter == _mData.end())
	{
		MessageBox(g_hWnd, "데이터를 찾을수 없습니다", "데이터 오류", MB_OK);
		return -1;
	}

	return _mData[name];
}

