#pragma once
#include "gameNode.h"
class SkillIce :
	public gameNode
{
private:
	float			_x;
	float			_y;
	RECT			_zRC;
	BOOL			_start;
	BOOL			_playAni;
	BOOL			_replayAni;
	int				_skillCount;

	image*			_ice;
	animation*		_iceAni;
public:
	SkillIce();
	~SkillIce();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	//	Z-ORDER¸¦ À§ÇÑ RC
	inline RECT &getRc() { return _zRC; }

	void StartAni();
	void ReplayAni();
	void StartSkill(float x, float y);
};

