#pragma once
#include "gameNode.h"
class interAction:public gameNode
{
private:
	image* _image;
	float _startX, _startY;
	float _endX, _endY;

	float _angle;
	float _travelRange;
	float _worldTimeCount;
	float _time;

	bool _isMoving;

public:
	interAction();
	~interAction();

	HRESULT init();
	void release();
	void update();
	void render();

	void moveTo(image* image, float endX, float endY, float time);

	void moving(void);

	bool getIsMoving() { return _isMoving; }
};

