#pragma once
#include "SingleTonBase.h"
#include <bitset>
#include <vector>
#define KEYMAX 256 // Ű�� 255���� ���
using namespace std;

class KeyManager:public SingleTonBase<KeyManager>
{
private:
	typedef bitset<KEYMAX>		BitKey;
	
	typedef vector<BitKey>::iterator	keyDownIter;
private:
	bitset<KEYMAX> keyUp; // Ű���������� ������ ����
	bitset<KEYMAX> keyDown; // Ű�� �������� ����

	vector<BitKey>	keyDownVec;	//	Ű�� ������ ���Ǹ� �ڵ����� �÷������
	vector<BitKey>	keyUpVec;
	
public:
	HRESULT init(); // Ű�� ���� �ʱ�ȭ
	void release();
	void keyInit(BitKey key);

	bool isOnceKeyDownOverlap(int key);
	bool isOnceKeyUpOverlap(int key);

	bool isOnceKeyDown(int key); // Ű�� �ѹ����ȴ���
	bool isOnceKeyUp(int key); // Ű�� �ѹ������� ��������
	bool isStayKeyDown(int key); // Ű�� ��� ��������
	bool isToggleKey(int key); // ���Ű�� ���ȴ���

	//Ű������ ������
	inline bitset<KEYMAX> GetKeyUp() { return keyUp; }
	inline bitset<KEYMAX> GetKeyDown() { return keyDown; }

	inline void setKeyDown(int key, bool state) { keyDown.set(key, state); }
	inline void setKeyUp(int key, bool state) { keyUp.set(key, state); }
	KeyManager();
	~KeyManager();
};

