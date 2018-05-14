#pragma once
#include "SingleTonBase.h"
#include "timer.h"

class TimeManager:public SingleTonBase<TimeManager>
{
private:
	timer*_timer;
public:
	TimeManager();
	~TimeManager();


	HRESULT init();
	void release();
	void update(float lock); // 고정프레임 설정하는곳
	void render(HDC hdc);

	inline float getElapsedTime(void) const { return _timer->getElapsedTime(); }
	inline float getWorldTime(void) const { return _timer->getWorldTime(); }
};

