#pragma once
#include "gameNode.h"

class SkillThunder;

class SkillWarrior :
	public gameNode
{
private:
	float			_x;
	float			_y;
	float			_time;
	RECT			_zRC;
	BOOL			_start;
	BOOL			_makeThunder;

	image*			_warrior;
	animation*		_warriorAni;

	SkillThunder*	_thunder[5];
public:
	SkillWarrior();
	~SkillWarrior();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	//	Z-ORDER¸¦ À§ÇÑ RC
	inline RECT &getRc() { return _zRC; }

	void StartAni();
	void StartSkill();
	void StartThunder();
};

