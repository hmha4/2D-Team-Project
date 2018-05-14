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
	//����ü ����

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
	//���͸� ��ΰ� ��
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	//���� ���丮 ��θ� �޾ƿ��� �Լ�
	GetCurrentDirectory(256, str);

	//str�� ���͸� ��ΰ� ������ �ű�ڿ� �����̸��� �ٿ��� \\�� ����ǹ�
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); ++i)
	{
		arrIniData vData = _vIniData[i];

		//[������] [] ������ִ� �Լ� => ��δ� str�� ��������� �������?
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

	//���� ����� iniData���Ϸ� ����
	GetCurrentDirectory(256, str);
	//����̸� ����
	strncat_s(str, 256, dir, 254);

	//������ ����ִ� ����
	char*data = new char[128];
	//char data[128] = { NULL };

	//����,Ű,�����尪,���� �о�� ����, ����ũ��,���
	GetPrivateProfileString(subject, title, "", data, 128, str);

	//���ڿ��� ����� �����Ͱ� ��ȯ
	return data;
}

int iniDataManager::loadDataInterger(const char * fileName, const char * subject,
									const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	//���� ����� iniData���Ϸ� ����
	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	return GetPrivateProfileInt(subject, title, 0, str);
}
