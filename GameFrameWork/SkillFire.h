#pragma once
#include "gameNode.h"
class SkillFire :
	public gameNode
{
private:
	float			_x;
	float			_y;
	RECT			_zRC;
	BOOL			_start;
	BOOL			_playAni;

	image*			_fire;
	animation*		_fireAni;
public:
	SkillFire();
	~SkillFire();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	//	Z-ORDER¸¦ À§ÇÑ RC
	inline RECT &getRc() { return _zRC; }

	void StartAni();
	void StartSkill(float x, float y);

};

