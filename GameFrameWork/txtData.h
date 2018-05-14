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
	//넘어온 벡터를 ','단위로 잘라서 새로운 문자열에 복사하는 함수
	char*vectorArrayCombine(vector<string> vArray);

	//Load
	vector<string> txtLoad(const char*loadFileName);
	vector<string> CstyleLoad(const char*loadFileName);
	//불러들어온 문자열을 ','단위로 잘라서 벡터에 넣는 함수
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
	
	//파일불러오고
	//

	// TODO: 여기에 반환 구문을 삽입합니다.
}
