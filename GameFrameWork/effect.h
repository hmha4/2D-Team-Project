#pragma once
#include "gameNode.h"

class animation;

class effect :public gameNode
{
protected:
	int _x;
	int _y;

	image*			_effectImg;			//이펙트 이미지를 담는 변수
	animation*	_effectAnim;			//이펙트 에니메이션
	BOOL			_isRunning;			//이펙트가 돌고있는지 여부
	float				_elapsedTime;		//이펙트의 시간

public:
	effect();
	~effect();

	virtual HRESULT init(image* effectImage, int frameW, int frameH, 
		int fps, float elapsedTime);
	virtual void release();
	virtual void update();
	virtual void render();

	void startEffect(int x, int y);

	virtual void killEffect();

	BOOL getIsRunning() { return _isRunning; }
};

