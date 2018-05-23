#pragma once
#include "gameNode.h"
class PlayerSkill :
	public gameNode
{
private:
	image*			_thunder;
	image*			_warrior;
	image*			_ice;
	image*			_fire;

	animation*		_thunderAni;
	animation*		_warriorAni;
	animation*		_iceAni;
	animation*		_fireAni;

	float			_x;
	float			_y;
	
	//스킬 선택
	// 0 : 번개, 1 : 얼음, 2 : 불
	int				_selectSkill;
public:
	PlayerSkill();
	~PlayerSkill();

	HRESULT Init();
	void Release();
	void Update(float x, float y);
	void Render();

	void DrawThunder(HDC hdc);
	void DrawWarrior(HDC hdc);
	void DrawIce(HDC hdc);
	void DrawFire(HDC hdc);
};

