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

	//���ڿ����Ϳ��� ���ĵ� ���ڿ��� ���ο� ���ڿ��� ����
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

	//NULL���ڿ� ,���ڿ� ���๮�ڶ����� 
	strncpy_s(temp,128 ,vectorArrayCombine(vStr), 126);

	fputs(temp, fp);
	fclose(fp);
}

char * txtData::vectorArrayCombine(vector<string> vArray)
{
	//���۴� ���߿� �������� �Ӽ��� ���¸�ŭ ���� ���ְ�
	//������ �ϸ� �˴ϴ� �켱�� 128���� ��ƵѲ��� 
	
	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		//, ���ϰ����� �ǵڿ�NULL�� �ٱ⶧��
		strncat_s(str, 128, vArray[i].c_str(), 126);
		
		//�ڸ� ���ڿ��ڿ� �ٽ�','�� �ٿ��ش�
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

//����� �����͸� �ҷ��ö� "," ������ ���ڿ��� �߶� ����
vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	char* separator = separator;
	char* token;

	token = strtok(charArray, separator);//�Էµ� �迭�� ,������ �ڸ���
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
	
	FILE*fp = fopen("�ɸ��ͻ���.txt", "wt");
	
	fputs(allData.c_str(), fp);
	fclose(fp);
	object->dataIntVec.clear();
	object->dataStringVec.clear();
	
}

//Data & txtData::FromData(string data)
//{
//	Data d;
//
//	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
//	return d;
//}
