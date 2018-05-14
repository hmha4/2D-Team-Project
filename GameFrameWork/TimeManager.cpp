#include "stdafx.h"
#include "TimeManager.h"

TimeManager::TimeManager()
{
}
TimeManager::~TimeManager()
{
}
HRESULT TimeManager::init()
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}
void TimeManager::release()
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}
void TimeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}
void TimeManager::render(HDC hdc)
{
	char str[256];
	//폰트 배경색 지정
	//폰트 배경색 불투명 : OPAQUE
	//폰트 배경색 투명 : TRANSPARENT
	SetBkMode(hdc, TRANSPARENT);

#ifdef _DEBUG // 디버그 모드일때
	{
		wsprintf(str, "framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		sprintf(str, "worldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		sprintf(str, "elapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}
#else // 릴리즈 모드일때
	{
		wsprintf(str, "framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif
}
