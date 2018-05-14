#pragma once
#include "SingleTonBase.h"
#include <vector>
#include <map>

class effect;

class effectManager : public SingleTonBase<effectManager>
{
private:
	//����		=>		���� ����Ʈ��ü�� ���� ����
	typedef vector<effect*>								arrEffects;
	typedef vector<effect*>::iterator					iterEffects;
	//����		=>		����Ʈ�� ���� ���͸� Ű������ �����ϴ� ��
	typedef map<string, arrEffects>						arrEffect;
	typedef map<string, arrEffects>::iterator			iterEffect;
	//����		=>		�ʿ� ����Ž���� ������ �ϱ����� ���� ��� ����
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

