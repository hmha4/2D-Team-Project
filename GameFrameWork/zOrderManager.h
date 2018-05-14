#pragma once
#include <vector>
#include "SingleTonBase.h"

class gameNode;

class zOrderManager :public SingleTonBase<zOrderManager>
{
private:
	vector<gameNode*>		zVec;
	vector<gameNode*>		zIter;

	bool useShadowRect; // 그림자렉트를 사용하는지 여부
						// 사용안하면 플레이어 렉트의 중점으로 판단
public:
	zOrderManager();
	~zOrderManager();

	//그림자렉트를 사용(비교)하는지 여부=>이건 게임노드init함수에서
	//설정해야 함 설정안하면 자동false
	void init(bool _useShadowRc = false);

	//객체를 z오더 벡터에 삽입하는 함수
	void InputObj(gameNode*obj);

	// 벡터에 있는 객체들의 랜더
	void Render();

	//실제 객체들의 y의 범위를 비교하여 벡터정렬
	//그러기 위해선 gameNode에 getRc같은 함수가 필요하다.
	//함수 오버라이딩 이용하자
	void Update();
	void Release();
};

