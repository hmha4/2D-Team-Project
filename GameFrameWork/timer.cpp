#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>	//timeGetTime() �� ����� �� �ִ�
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
	//��ǻ�� ������ ������ �Ϸ� ���´�
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true; // ���� üũ
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}
	else//��ǻ�� ������ ���������� �Ϸ� ���´�
	{
		_isHardware = false;
		_lastTime = timeGetTime();	//	������ �и��������� �����
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
	if (_isHardware)//�����̸�
	{
		//������ ī��Ʈ�� �޴´�
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else//���� �ƴϸ�
	{
		//�и����������� �ʸ��޴´�
		_curTime = timeGetTime();
	}

	//�ð�������� �̴´�
	_timeElapsed = (_curTime - _lastTime)*_timeScale;

	//FPS�� ���س��Ҵٸ�
	if (lockFPS > 0)
	{
		//���� ������������ 60�̸� timeScale�� ����ؼ� ������
		//1/60���� Ŀ���� ����ð��� 1/60�ʸ��� ���ŵȴ�
		while (_timeElapsed < (1.0f) / lockFPS)
		{
			if (_isHardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else
				_curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}
	
	//�������ð��� ����ð����� �ٽ� ����
	_lastTime = _curTime;

	//�������� ����
	//������ �������� 60���� ������������ 1/60�ʸ��� 1������
	_FPSFrameRate++;
	_FPSTimeElapsed += _timeElapsed; // �����Ӱ� �����ӻ��� �ð��� 
															//(1/60)�� ����ؼ� ������

	_worldTime += _timeElapsed;
	
	if (_FPSTimeElapsed > 1.0f) //1�ʴ� ������
	{
		_frameRate = _FPSFrameRate; // 1�ʿ� ��������60�� ����
		_FPSFrameRate = 0;				 //���������� �ٽ� �����ϹǷ� 0���� �ʱ�ȭ
		_FPSTimeElapsed = 0.0f;			 //������ ����ð��� 0���� �ʱ�ȭ
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
