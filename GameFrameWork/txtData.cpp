#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{
}

void txtData::txtSave(const char * saveFileName, vector<string> vStr)
{
	HANDLE file;
	DWORD write;

	char temp[512];

	//문자열벡터에서 정렬된 문자열을 새로운 문자열에 복사
	strncpy_s(temp, 128,vectorArrayCombine(vStr),126);

	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	
	WriteFile(file, temp, 128, &write, NULL);

	CloseHandle(file);
}

void txtData::CstyleSave(const char * saveFileName, vector<string> vStr)
{
	FILE*fp = fopen(saveFileName, "wt");

	char temp[512];

	//NULL문자와 ,문자와 개행문자때문에 
	strncpy_s(temp,128 ,vectorArrayCombine(vStr), 126);

	fputs(temp, fp);
	fclose(fp);
}

char * txtData::vectorArrayCombine(vector<string> vArray)
{
	//버퍼는 나중에 여러분이 속성이 들어온만큼 담을 수있게
	//수정을 하면 됩니당 우선은 128개로 잡아둘께요 
	
	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		//, 붙일공간과 맨뒤에NULL이 붙기때문
		strncat_s(str, 128, vArray[i].c_str(), 126);
		
		//자른 문자열뒤에 다시','를 붙여준다
		if (i + 1 < vArray.size())
			strcat(str, ",");
	}
	
	return str;
}

vector<string> txtData::txtLoad(const char * loadFileName)
{
	HANDLE file;
	DWORD read;
	
	char str[512];

	file = CreateFile(loadFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);
	return charArraySeparation(str);
}

vector<string> txtData::CstyleLoad(const char * loadFileName)
{
	FILE*fp = fopen(loadFileName, "rt");
	
	char str[512];

	fgets(str, sizeof(str), fp);
	
	fclose(fp);
	return charArraySeparation(str);
}

//저장된 데이터를 불러올때 "," 단위로 문자열을 잘라 복사
vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	char* separator = separator;
	char* token;

	token = strtok(charArray, separator);//입력된 배열을 ,단위로 자른다
	vArray.push_back(token);

	//150NULL50NULL100NULL
	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}

void txtData::ToData(Data*object)
{
	char temp[256] = "";
	char textInt[256]="";
	char textString[256]="";
	
	for (int i = 0; i < object->dataIntVec.size(); i++)
	{
		if(i!= object->dataIntVec.size()-1)
			sprintf(temp, "%d|", object->dataIntVec[i]);
		else
			sprintf(temp, "%d", object->dataIntVec[i]);
		strcat(textInt, temp);
	}
	for (int i = 0; i < object->dataStringVec.size(); i++)
	{
		sprintf(temp, "|%s", object->dataStringVec[i]);
		strcat(textString, temp);
	}
	
	string allData;
	allData.append(textInt);
	allData.append(textString);
	
	FILE*fp = fopen("케릭터상태.txt", "wt");
	
	fputs(allData.c_str(), fp);
	fclose(fp);
	object->dataIntVec.clear();
	object->dataStringVec.clear();
	
}

//Data & txtData::FromData(string data)
//{
//	Data d;
//
//	// TODO: 여기에 반환 구문을 삽입합니다.
//	return d;
//}
