#pragma once
#include "SingleTonBase.h"

enum LIGHTSET
{
	NULL_LIGHT,		//���þ���
	POINT_LIGHT,	//����			:	�߽����� ��������
	SPOT_LIGHT		//����Ʈ����Ʈ	:	������������ �����
};
class Light:public SingleTonBase<Light>
{
private:
	RECT LightRange;


public:
	Light();
	~Light();

	void Init();

	//����Ʈ �ʱ�ȭ
	void LightInit();
	
	//����Ʈ ���

};

