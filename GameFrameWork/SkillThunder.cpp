#include "stdafx.h"
#include "SkillThunder.h"


SkillThunder::SkillThunder()
	:_x(0), _y(0), _start(0)
{
	_thunder = IMAGEMANAGER.addFrameImage("SKILL_THUNDER2", PathFile("image\\Skill", "SKILL_THUNDER2").c_str(), 1320, 400, 6, 1, true, RGB(255, 0, 255));
	
	_thunderAni = new animation;
	_thunderAni->init(1320, 400, 220, 400);
	_thunderAni->setDefPlayFrame(false, false);
	_thunderAni->setFPS(6);
}


SkillThunder::~SkillThunder()
{
}

HRESULT SkillThunder::Init()
{
	return S_OK;
}

void SkillThunder::Release()
{
}

void SkillThunder::Update()
{
	_thunderAni->frameUpdate(TIMEMANAGER.getElapsedTime());

	if (_start)	StartAni();
}

void SkillThunder::Render()
{
	if (_thunderAni->isPlay()) _thunder->aniRender(getMemDC(), (_zRC.left + _zRC.right) / 2 - (_thunder->GetFrameWidth() / 2), _zRC.top - _thunder->GetFreamHeight(), _thunderAni);
}

void SkillThunder::StartAni()
{
	_thunderAni->start();
	_start = false;
}

void SkillThunder::StartSkill(float x, float y)
{
	_start = true;
	
	_x = x;
	_y = y;
	
	_zRC = RectMake(_x, _y, 70, 10);
}
