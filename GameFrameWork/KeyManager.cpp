#include "stdafx.h"
#include "KeyManager.h"


HRESULT KeyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		keyUp.set(i, false); // Ű�� ���¸� ���� false��
		keyDown.set(i, false); // Ű�� ���¸� ���� false��
	}
	keyDownVec.push_back(keyDown);
	keyUpVec.push_back(keyUp);
	return S_OK;
}

void KeyManager::release()
{
	ReleaseSingleton();
}

void KeyManager::keyInit(BitKey key)
{
	for (int i = 0; i < KEYMAX; i++)
	{
		key.set(i, false); // Ű�� ���¸� ���� false��
	}
}

bool KeyManager::isOnceKeyDownOverlap(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)//Ű�� ��������
	{
		for (int i = 0; i < keyDownVec.size(); i++)
		{
			if (!keyDownVec[i][key])
			{
				keyDownVec[i].set(key, true);
				
				if(keyDownVec.size()==1)
					return true;
				else
				{
					keyDownIter kIter = keyDownVec.begin() + 1;

					for (; kIter != keyDownVec.end();)
					{
						if (*kIter != NULL)
						{
							kIter = keyDownVec.erase(kIter);
						}
						else
							kIter++;
					}
					for (int i = 0; i<keyDownVec.size(); i++)
						keyDownVec[i].set(key, false);
					return true;
				}
			}
			else
			{
				keyInit(keyDown);
				keyDownVec.push_back(keyDown);
				continue;
			}
		}
	}
	else
	{
		keyDownIter kIter = keyDownVec.begin() + 1;
		
		for (; kIter != keyDownVec.end();)
		{
			if (*kIter != NULL)
			{
				kIter = keyDownVec.erase(kIter);
			}
			else
				kIter++;
		}
		for(int i=0; i<keyDownVec.size(); i++)
			keyDownVec[i].set(key, false);
	}
	return false;
}

bool KeyManager::isOnceKeyUpOverlap(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)//Ű�������� 
	{
		if (keyUpVec.size() <= 1)	//	�����Ͱ� �ϳ��϶� �׳ɺ����ش�
		{
			keyUpVec[0].set(key, true);
		}
		else // ������ �������϶� �Ѱ��� �������� �Ѵ�
		{
			keyDownIter kIter = keyUpVec.begin() + 1;

			for (; kIter != keyUpVec.end();)
			{
				if (*kIter != NULL)
				{
					kIter = keyUpVec.erase(kIter);
				}
				else
					kIter++;
			}
			for (int i = 0; i<keyUpVec.size(); i++)
				keyUpVec[i].set(key, true);
		}
	}
	else//������
	{
		for (int i = 0; i < keyUpVec.size(); i++)
		{
			if (keyUpVec[i][key])//Ű�� �����־��ٸ�
			{
				keyUpVec[i].set(key, false);//�ȴ��ȴٰ��ϰ�
				return true;
			}
			else
			{
				keyInit(keyUp);
				keyUp.set(key, true);
				keyUpVec.push_back(keyUp);
				continue;
			}
		}
	}
	return false;
}

bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)//Ű�� ��������
	{
		if (!keyDown[key])
		{
			keyDown.set(key, true);
			return true;
		}
	}
	else
	{
		keyDown.set(key, false);
	}
	return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)//Ű�������� 
	{
		keyUp.set(key, true);//���ȴٰ����ְ�
	}
	else//������
	{
		if (keyUp[key])//Ű�� �����־��ٸ�
		{
			keyUp.set(key, false);//�ȴ��ȴٰ��ϰ�
			return true;
		}
	}
	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}

KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
}
