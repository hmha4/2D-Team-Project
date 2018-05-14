#pragma once
template <typename T>
class SingleTonBase
{
protected:
	static T*instance;
	SingleTonBase() {}
	~SingleTonBase() {}
public:
	static T&GetInstance();
	void ReleaseSingleton();
};

//전역변수의 초기화 과정=>반드시 해야함
template <typename T>
T*SingleTonBase<T>::instance = 0;

//객체를 생성하여 반환하는 함수.단, 객체가 있으면 반환만함
template <typename T>
T&SingleTonBase<T>::GetInstance()
{
	if (instance == NULL)
		instance = new T;
	return *instance;
}

//객체의 메모리해제
template <typename T>
void SingleTonBase<T>::ReleaseSingleton()
{
	if (instance != NULL)
		delete instance;
}

