#include "stdafx.h"
#include "SkillFire.h"


SkillFire::SkillFire()
	:_x(0), _y(0), _start(0)
{
	_fire = IMAGEMANAGER.addFrameImage("SKILL_FIRE", PathFile("image\\Skill", "SKILL_FIRE").c_str(), 2030, 180, 29, 1, true, RGB(255, 0, 255));

	_fireAni = new animation;
	_fireAni->init(2030, 180, 70, 180);
	_fireAni->setDefPlayFrame(false, false);
	_fireAni->setFPS(20.0);
}


SkillFire::~SkillFire()
{
}

HRESULT SkillFire::Init()
{
	return S_OK;
}

void SkillFire::Release()
{
}

void SkillFire::Update()
{
	_fireAni->frameUpdate(TIMEMANAGER.getElapsedTime());

	if (_start)	StartAni();
}

void SkillFire::Render()
{
	if (_fireAni->isPlay()) 
	{
		_fire->aniRender(getMemDC()
			, (_zRC.left + _zRC.right) / 2 - _fire->GetFrameWidth() / 2
			, _zRC.top - _fire->GetFreamHeight(),
			_fireAni);
		Rectangle(getMemDC(), _zRC.left, _zRC.top, _zRC.right, _zRC.bottom);
	}
}

void SkillFire::StartAni()
{
	_fireAni->start();
	_start = false;
}

void SkillFire::StartSkill(float x, float y)
{
	_start = true;

	_x = x;
	_y = y;

	_zRC = RectMake(_x, _y, 70, 10);
}
