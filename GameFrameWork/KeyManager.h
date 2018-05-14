#pragma once
#include "SingleTonBase.h"
#include <bitset>
#include <vector>
#define KEYMAX 256 // 키값 255개를 사용
using namespace std;

class KeyManager:public SingleTonBase<KeyManager>
{
private:
	typedef bitset<KEYMAX>		BitKey;
	
	typedef vector<BitKey>::iterator	keyDownIter;
private:
	bitset<KEYMAX> keyUp; // 키가눌려지고 땠을때 상태
	bitset<KEYMAX> keyDown; // 키를 눌렀을때 상태

	vector<BitKey>	keyDownVec;	//	키가 여러개 사용되면 자동으로 늘려줘야함
	vector<BitKey>	keyUpVec;
	
public:
	HRESULT init(); // 키에 대한 초기화
	void release();
	void keyInit(BitKey key);

	bool isOnceKeyDownOverlap(int key);
	bool isOnceKeyUpOverlap(int key);

	bool isOnceKeyDown(int key); // 키가 한번눌렸는지
	bool isOnceKeyUp(int key); // 키가 한번눌리고 때졌는지
	bool isStayKeyDown(int key); // 키가 계속 눌리는지
	bool isToggleKey(int key); // 토글키가 눌렸는지

	//키에대한 접근자
	inline bitset<KEYMAX> GetKeyUp() { return keyUp; }
	inline bitset<KEYMAX> GetKeyDown() { return keyDown; }

	inline void setKeyDown(int key, bool state) { keyDown.set(key, state); }
	inline void setKeyUp(int key, bool state) { keyUp.set(key, state); }
	KeyManager();
	~KeyManager();
};

