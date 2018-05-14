#include "stdafx.h"
#include "KeyManager.h"


HRESULT KeyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		keyUp.set(i, false); // 키의 상태를 전부 false로
		keyDown.set(i, false); // 키의 상태를 전부 false로
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
		key.set(i, false); // 키의 상태를 전부 false로
	}
}

bool KeyManager::isOnceKeyDownOverlap(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)//키를 눌렀을때
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
	if (GetAsyncKeyState(key) & 0x8000)//키눌렀을때 
	{
		if (keyUpVec.size() <= 1)	//	데이터가 하나일때 그냥보내준다
		{
			keyUpVec[0].set(key, true);
		}
		else // 데이터 여러개일때 한개로 만들어줘야 한다
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
	else//땠을때
	{
		for (int i = 0; i < keyUpVec.size(); i++)
		{
			if (keyUpVec[i][key])//키가 눌려있었다면
			{
				keyUpVec[i].set(key, false);//안눌렸다고하고
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
	if (GetAsyncKeyState(key) & 0x8000)//키를 눌렀을때
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
	if (GetAsyncKeyState(key) & 0x8000)//키눌렀을때 
	{
		keyUp.set(key, true);//눌렸다고해주고
	}
	else//땠을때
	{
		if (keyUp[key])//키가 눌려있었다면
		{
			keyUp.set(key, false);//안눌렸다고하고
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
