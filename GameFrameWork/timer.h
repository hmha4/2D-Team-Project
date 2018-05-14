#pragma once
class timer
{
private:
	bool _isHardware;		// 하드웨어가 고승능인가
	float _timeScale;			//FPS 빈도 
	float _timeElapsed;		//FPS 시간경과차이

	__int64 _curTime;					//현재 측정시간
	__int64 _lastTime;				//마지막 측정시간
	__int64 _periodFrequency;	//운영체제에서 받는 메시지빈도

	unsigned long _frameRate;			//초당프레임수
	unsigned long _FPSFrameRate;	//프레임

	float _FPSTimeElapsed;				//FPS의 경과시간(경과차이를 더해나간다)
	float _worldTime;							//실제 흐르는 시간(초단위로나옴)
public:
	timer();
	~timer();

	HRESULT init();
	void tick(float lockFPS = 0.0f);	// 1초당 프레임과 실제 흐른시간, 그리고 프레임과 프레임사이 시간
	
	unsigned long getFrameRate(char* str = NULL) const;
	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }
};

