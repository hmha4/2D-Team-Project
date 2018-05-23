#include "stdafx.h"
#include "PlayerSkill.h"


PlayerSkill::PlayerSkill()
	:_selectSkill(3)
{
}


PlayerSkill::~PlayerSkill()
{
}

HRESULT PlayerSkill::Init()
{
	_thunder = IMAGEMANAGER.addFrameImage("SKILL_THUNDER2", PathFile("image\\Skill", "SKILL_THUNDER2").c_str(), 1320, 400, 6, 1, true, RGB(255, 0, 255));
	_warrior = IMAGEMANAGER.addFrameImage("SKILL_THUNDER1", PathFile("image\\Skill", "SKILL_THUNDER1").c_str(), 4378*2, 172*2, 22, 1, true, RGB(255, 0, 255));
	_ice = IMAGEMANAGER.addFrameImage("SKILL_ICE", PathFile("image\\Skill", "SKILL_ICE").c_str(), 1280, 115, 8, 1, true, RGB(255, 0, 255));
	_fire = IMAGEMANAGER.addFrameImage("SKILL_FIRE", PathFile("image\\Skill", "SKILL_FIRE").c_str(), 2030, 180, 29, 1, true, RGB(255, 0, 255));
	
	_thunderAni = new animation;
	_thunderAni->init(1320, 400, 220, 400);
	_thunderAni->setDefPlayFrame(false, true);
	_thunderAni->setFPS(6);

	_warriorAni = new animation;
	_warriorAni->init(4378*2, 172*2, 199*2, 172*2);
	_warriorAni->setDefPlayFrame(false, false);
	_warriorAni->setFPS(10);

	_iceAni = new animation;
	_iceAni->init(1280, 115, 160, 115);
	_iceAni->setDefPlayFrame(false, false);
	_iceAni->setFPS(10.0);

	_fireAni = new animation;
	_fireAni->init(2030, 180, 70, 180);
	_fireAni->setDefPlayFrame(false, false);
	_fireAni->setFPS(20.0);

	return S_OK;
}

void PlayerSkill::Release()
{
}

void PlayerSkill::Update(float x, float y)
{
	_x = x;
	_y = y;

	_thunderAni->frameUpdate(TIMEMANAGER.getElapsedTime());
	_warriorAni->frameUpdate(TIMEMANAGER.getElapsedTime());
	_iceAni->frameUpdate(TIMEMANAGER.getElapsedTime());
	_fireAni->frameUpdate(TIMEMANAGER.getElapsedTime());

	if (KEYMANAGER.isOnceKeyDown('E')) _selectSkill++;

	if (_selectSkill > 3) _selectSkill = 0;
}

void PlayerSkill::Render()
{
	if (_selectSkill == 0)
	{
		DrawThunder(getMemDC());
		DrawWarrior(getMemDC());
	}
	else if (_selectSkill == 1) DrawIce(getMemDC());
	else if (_selectSkill == 2) DrawFire(getMemDC());

}

void PlayerSkill::DrawThunder(HDC hdc)
{
	if (!_thunderAni->isPlay())	_thunderAni->start();
	_thunder->aniRender(hdc, _x, CAM.GetY(), _thunderAni);
}

void PlayerSkill::DrawWarrior(HDC hdc)
{
	if (!_warriorAni->isPlay()) _warriorAni->start();
	_warrior->aniRender(hdc, _x, CAM.GetY(), _warriorAni);
}

void PlayerSkill::DrawIce(HDC hdc)
{
	if (!_iceAni->isPlay()) _iceAni->start();
	_ice->aniRender(hdc, _x, _y, _iceAni);
}

void PlayerSkill::DrawFire(HDC hdc)
{
	if (!_fireAni->isPlay()) _fireAni->start();
	_fire->aniRender(hdc, _x, _y, _fireAni);
}
