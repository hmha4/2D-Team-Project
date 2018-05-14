#pragma once
#include <vector>
#include "SingleTonBase.h"

class gameNode;

class zOrderManager :public SingleTonBase<zOrderManager>
{
private:
	vector<gameNode*>		zVec;
	vector<gameNode*>		zIter;

	bool useShadowRect; // �׸��ڷ�Ʈ�� ����ϴ��� ����
						// �����ϸ� �÷��̾� ��Ʈ�� �������� �Ǵ�
public:
	zOrderManager();
	~zOrderManager();

	//�׸��ڷ�Ʈ�� ���(��)�ϴ��� ����=>�̰� ���ӳ��init�Լ�����
	//�����ؾ� �� �������ϸ� �ڵ�false
	void init(bool _useShadowRc = false);

	//��ü�� z���� ���Ϳ� �����ϴ� �Լ�
	void InputObj(gameNode*obj);

	// ���Ϳ� �ִ� ��ü���� ����
	void Render();

	//���� ��ü���� y�� ������ ���Ͽ� ��������
	//�׷��� ���ؼ� gameNode�� getRc���� �Լ��� �ʿ��ϴ�.
	//�Լ� �������̵� �̿�����
	void Update();
	void Release();
};

