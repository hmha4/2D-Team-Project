#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>	//timeGetTime() 을 사용할 수 있다
#pragma comment(lib, "winmm.lib")

timer::timer()
{
}


timer::~timer()
{
}

HRESULT timer::init()
{
	//IRC
	//컴퓨터 성능이 좋으면 일로 들어온다
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true; // 고성능 체크
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}
	else//컴퓨터 성능이 좋지않으면 일로 들어온다
	{
		_isHardware = false;
		_lastTime = timeGetTime();	//	강제로 밀리세컨으로 맞춘다
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameRate = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0;
	return S_OK;
}

void timer::tick(float lockFPS)
{
	if (_isHardware)//고성능이면
	{
		//쿼리로 카운트를 받는다
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else//고성능 아니면
	{
		//밀리세컨단위로 초를받는다
		_curTime = timeGetTime();
	}

	//시간경과율을 뽑는다
	_timeElapsed = (_curTime - _lastTime)*_timeScale;

	//FPS를 정해놓았다면
	if (lockFPS > 0)
	{
		//만약 고정프레임이 60이면 timeScale는 계속해서 오르다
		//1/60보다 커지면 경과시간은 1/60초마다 갱신된다
		while (_timeElapsed < (1.0f) / lockFPS)
		{
			if (_isHardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else
				_curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}
	
	//마지막시간을 현재시간으로 다시 갱신
	_lastTime = _curTime;

	//프레임율 증가
	//위에서 프레임을 60으로 고정시켰으니 1/60초마다 1씩오름
	_FPSFrameRate++;
	_FPSTimeElapsed += _timeElapsed; // 프레임과 프레임사이 시간을 
															//(1/60)을 계속해서 더해줌

	_worldTime += _timeElapsed;
	
	if (_FPSTimeElapsed > 1.0f) //1초당 프레임
	{
		_frameRate = _FPSFrameRate; // 1초에 프레임은60이 나옴
		_FPSFrameRate = 0;				 //프레임율은 다시 세야하므로 0으로 초기화
		_FPSTimeElapsed = 0.0f;			 //프레임 경과시간도 0으로 초기화
	}
}

unsigned long timer::getFrameRate(char * str) const
{
	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}
	return _frameRate;
}
