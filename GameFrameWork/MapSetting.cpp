#include "stdafx.h"
#include "MapSetting.h"


MapSetting::MapSetting()
{
}


MapSetting::~MapSetting()
{
}

HRESULT MapSetting::Init()
{
	tm = new TileMap;
	tm->Init();
	return S_OK;
}

void MapSetting::Render()
{
	tm->Render();
}

void MapSetting::Release()
{
}

void MapSetting::Update()
{
	tm->Update();
	if (KEYMANAGER.isOnceKeyDown(VK_RETURN))
		SCENEMANAGER.changeScene("¿Œ∞‘¿”");
}
