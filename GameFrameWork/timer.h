#pragma once
class timer
{
private:
	bool _isHardware;		// �ϵ��� ��´��ΰ�
	float _timeScale;			//FPS �� 
	float _timeElapsed;		//FPS �ð��������

	__int64 _curTime;					//���� �����ð�
	__int64 _lastTime;				//������ �����ð�
	__int64 _periodFrequency;	//�ü������ �޴� �޽�����

	unsigned long _frameRate;			//�ʴ������Ӽ�
	unsigned long _FPSFrameRate;	//������

	float _FPSTimeElapsed;				//FPS�� ����ð�(������̸� ���س�����)
	float _worldTime;							//���� �帣�� �ð�(�ʴ����γ���)
public:
	timer();
	~timer();

	HRESULT init();
	void tick(float lockFPS = 0.0f);	// 1�ʴ� �����Ӱ� ���� �帥�ð�, �׸��� �����Ӱ� �����ӻ��� �ð�
	
	unsigned long getFrameRate(char* str = NULL) const;
	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }
};

