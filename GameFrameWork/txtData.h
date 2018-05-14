#pragma once
#include "singletonBase.h"
#include "Data.h"
#include <comutil.h>
#include <vector>
#include <string>

class data;
class txtData:public SingleTonBase<txtData>
{
public:
	txtData();
	~txtData();
	
	HRESULT init();
	void release();

	//Save
	void txtSave(const char*saveFileName, vector<string> vStr);
	void CstyleSave(const char*saveFileName, vector<string> vStr);
	//�Ѿ�� ���͸� ','������ �߶� ���ο� ���ڿ��� �����ϴ� �Լ�
	char*vectorArrayCombine(vector<string> vArray);

	//Load
	vector<string> txtLoad(const char*loadFileName);
	vector<string> CstyleLoad(const char*loadFileName);
	//�ҷ����� ���ڿ��� ','������ �߶� ���Ϳ� �ִ� �Լ�
	vector<string> charArraySeparation(char charArray[]);

	void ToData(Data*object);

	//Data&FromData(string data);

	template<typename T>
	T&FromData(const char*loadFileName);
};

template<typename T>
inline T & txtData::FromData(const char*loadFileName)
{
	T t;
	
	//���Ϻҷ�����
	//

	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
}
