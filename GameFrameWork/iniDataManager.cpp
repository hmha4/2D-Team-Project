#include "stdafx.h"
#include "iniDataManager.h"


iniDataManager::iniDataManager()
{
}


iniDataManager::~iniDataManager()
{
}

HRESULT iniDataManager::init()
{
	return S_OK;
}

void iniDataManager::release()
{

}

void iniDataManager::addData(const char * subject, const char * title, const char * body)
{
	//구조체 선언

	tagIniData iniData;

	iniData.subject = subject;
	iniData.title = title;
	iniData.body = body;

	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);
}

void iniDataManager::iniSave(char * fileName)
{
	//디렉터리 경로가 들어감
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	//현재 디렉토리 경로를 받아오는 함수
	GetCurrentDirectory(256, str);

	//str에 디렉터리 경로가 들어갔으니 거기뒤에 파일이름이 붙여짐 \\은 경로의미
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); ++i)
	{
		arrIniData vData = _vIniData[i];

		//[제갈량] [] 만들어주는 함수 => 경로는 str에 들어있으니 상관없지?
		WritePrivateProfileString(vData[0].subject, vData[0].title, vData[0].body, str);

		vData.clear();
	}

	_vIniData.clear();
}

char * iniDataManager::loadDataString(const char * fileName, const char * subject, 
										const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	//현재 경로의 iniData파일로 접근
	GetCurrentDirectory(256, str);
	//경로이름 저장
	strncat_s(str, 256, dir, 254);

	//데이터 비어있는 상태
	char*data = new char[128];
	//char data[128] = { NULL };

	//섹션,키,디폴드값,값을 읽어올 버퍼, 버퍼크기,경로
	GetPrivateProfileString(subject, title, "", data, 128, str);

	//문자열로 저장된 데이터값 반환
	return data;
}

int iniDataManager::loadDataInterger(const char * fileName, const char * subject,
									const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	//현재 경로의 iniData파일로 접근
	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	return GetPrivateProfileInt(subject, title, 0, str);
}
