#pragma once
#include "gameNode.h"
class EndingScene :
	public gameNode
{
private:
	enum STATE
	{
		STATE01,
		STATE02
	};
	enum CHARACTER
	{
		BOWMAN,
		MAGICIAN,
		WARRIOR,
		CLERIC,
		DWARF
	};
private:
	STATE _state;

	image * _fade;
	int _offSet;

	int _playerNum;
	CHARACTER _character[2];
	int _frameX[2];

	string _str;
	RECT _rc;
	float _y;
public:
	EndingScene();
	~EndingScene();

	HRESULT Init();
	void Render();
	void Update();
	void Release();
};

