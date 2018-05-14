#pragma once
#include "SingleTonBase.h"
#include <vector>
#include <map>

class effect;

class effectManager : public SingleTonBase<effectManager>
{
private:
	//생산		=>		실제 이펙트객체가 담기는 벡터
	typedef vector<effect*>								arrEffects;
	typedef vector<effect*>::iterator					iterEffects;
	//가공		=>		이펙트를 담은 벡터를 키값으로 저장하는 맵
	typedef map<string, arrEffects>						arrEffect;
	typedef map<string, arrEffects>::iterator			iterEffect;
	//포장		=>		맵에 접근탐색을 간단히 하기위해 맵을 담는 벡터
	typedef vector<map<string, arrEffects>>				arrTotalEffect;
	typedef vector<map<string, arrEffects>>::iterator	iterTotalEffect;

private:
	arrTotalEffect _vTotalEffect;

public:
	effectManager();
	~effectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addEffect(string effectName, const char* imageName, 
		int imageWidth, int imageHeight, int effectWidth, 
		int effectHeight, int fps, float elapsedTime, int buffer);

	void play(string effectName, int x, int y);
};

