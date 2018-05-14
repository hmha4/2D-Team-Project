#pragma once
#include "SingleTonBase.h"

enum LIGHTSET
{
	NULL_LIGHT,		//셋팅안함
	POINT_LIGHT,	//점광			:	중심으로 퍼져나감
	SPOT_LIGHT		//스포트라이트	:	일정방향으로 뻣어나감
};
class Light:public SingleTonBase<Light>
{
private:
	RECT LightRange;


public:
	Light();
	~Light();

	void Init();

	//라이트 초기화
	void LightInit();
	
	//라이트 쏘기

};

