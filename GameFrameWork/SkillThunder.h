#pragma once
#include "gameNode.h"

class SkillThunder :
	public gameNode
{
private:
	float			_x;
	float			_y;
	RECT			_zRC;
	BOOL			_start;
	BOOL			_playAni;

	image*			_thunder;
	animation*		_thunderAni;
public:
	SkillThunder();
	~SkillThunder();
	
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	//	Z-ORDER¸¦ À§ÇÑ RC
	inline RECT &getRc() { return _zRC; }

	void StartAni();
	void StartSkill(float x, float y);

	BOOL GetPlayAni() { return _thunderAni->isPlay(); }
};

