#include "stdafx.h"
#include "SkillWarrior.h"
#include "SkillThunder.h"


SkillWarrior::SkillWarrior()
	:_x(0), _y(0), _start(0), _time(0), _makeThunder(0)
{
	_warrior = IMAGEMANAGER.addFrameImage("SKILL_THUNDER1", PathFile("image\\Skill", "SKILL_THUNDER1").c_str(), 4378 * 2, 172 * 2, 22, 1, true, RGB(255, 0, 255));

	_warriorAni = new animation;
	_warriorAni->init(4378 * 2, 172 * 2, 199 * 2, 172 * 2);
	_warriorAni->setDefPlayFrame(false, false);
	_warriorAni->setFPS(10);

	for (int ii = 0; ii < 5; ++ii)
	{
		_thunder[ii] = new SkillThunder;
		ZORDER.InputObj(_thunder[ii]);
	}
}


SkillWarrior::~SkillWarrior()
{
}

HRESULT SkillWarrior::Init()
{
	return S_OK;
}

void SkillWarrior::Release()
{
	for (int ii = 0; ii < 5; ++ii)
	{
		SAFE_DELETE(_thunder[ii]);
	}
}

void SkillWarrior::Update()
{
	_warriorAni->frameUpdate(TIMEMANAGER.getElapsedTime());

	if (_start) StartAni();

	if (_warriorAni->isPlay())
	{
		_zRC = RectMake(CAM.GetX(), CAM.GetY(), 800, 800);
	}

	for (int ii = 0; ii < 5; ++ii)
	{
		_thunder[ii]->Update();
	}

	if (_time > 0.9 && _time < 1.6 && !_thunder[0]->GetPlayAni())
	{
		for (int ii = 0; ii < 5; ++ii)
		{
			_thunder[ii]->StartSkill(CAM.GetX() + ii * 180 + 40
				, CAM.GetY() + 300 + (ii % 2) * 100);
		}
	}
}

void SkillWarrior::Render()
{
	if (_warriorAni->isPlay())
	{
		_time += TIMEMANAGER.getElapsedTime();
		_warrior->aniRender(getMemDC()
							, CAM.GetCenterX() - _warrior->GetFrameWidth() / 2
							, CAM.GetCenterY() - _warrior->GetFreamHeight() / 2 - 30
							, _warriorAni);
	}
}

void SkillWarrior::StartAni()
{
	_time = 0;
	_warriorAni->start();
	_start = false;
}

void SkillWarrior::StartSkill()
{
	_start = true;
	_zRC = RectMake(CAM.GetX(), CAM.GetY() + 500, 70, 10);
}

void SkillWarrior::StartThunder()
{
	for (int ii = 0; ii < 5; ++ii)
	{
		_thunder[ii]->StartSkill(CAM.GetX() + ii * 180 + 40
			, CAM.GetY() + 300 + (ii % 2) * 100);
	}
}
