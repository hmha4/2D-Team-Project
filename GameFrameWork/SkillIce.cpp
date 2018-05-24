#include "stdafx.h"
#include "SkillIce.h"


SkillIce::SkillIce()
	:_x(0), _y(0), _start(0), _replayAni(0), _skillCount(0)
{
	_ice = IMAGEMANAGER.addFrameImage("SKILL_ICE", PathFile("image\\Skill", "SKILL_ICE").c_str(), 1280, 115, 8, 1, true, RGB(255, 0, 255));

	_iceAni = new animation;
	_iceAni->init(1280, 115, 160, 115);
	_iceAni->setDefPlayFrame(false, false);
	_iceAni->setFPS(10.0);
}


SkillIce::~SkillIce()
{
}

HRESULT SkillIce::Init()
{
	return S_OK;
}

void SkillIce::Release()
{
}

void SkillIce::Update()
{
	_iceAni->frameUpdate(TIMEMANAGER.getElapsedTime());

	if (_start)	StartAni();
	ReplayAni();
	_zRC = RectMake(_x, _y, 70, 10);
}

void SkillIce::Render()
{
	if (_iceAni->isPlay())
	{
		_ice->aniRender(getMemDC()
			, (_zRC.left + _zRC.right) / 2 - _ice->GetFrameWidth() / 2
			, _zRC.top - _ice->GetFreamHeight()
			, _iceAni);
		Rectangle(getMemDC(), _zRC.left, _zRC.top, _zRC.right, _zRC.bottom);
	}
}

void SkillIce::StartAni()
{
	_iceAni->start();
	_replayAni = true;
	_start = false;
}

void SkillIce::ReplayAni()
{
	if (_replayAni == true && !_iceAni->isPlay())
	{
		if (_skillCount > 3)
		{
			_replayAni = false;
			_skillCount = 0;
			return;
		}
		_skillCount++;
		_x += _ice->GetFrameWidth() - 30;
		_iceAni->start();
	}
}

void SkillIce::StartSkill(float x, float y)
{
	_start = true;

	_x = x;
	_y = y;
}
