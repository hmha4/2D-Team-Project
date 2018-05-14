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

//���������� �ʱ�ȭ ����=>�ݵ�� �ؾ���
template <typename T>
T*SingleTonBase<T>::instance = 0;

//��ü�� �����Ͽ� ��ȯ�ϴ� �Լ�.��, ��ü�� ������ ��ȯ����
template <typename T>
T&SingleTonBase<T>::GetInstance()
{
	if (instance == NULL)
		instance = new T;
	return *instance;
}

//��ü�� �޸�����
template <typename T>
void SingleTonBase<T>::ReleaseSingleton()
{
	if (instance != NULL)
		delete instance;
}

