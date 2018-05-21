#include "stdafx.h"
#include "playGround.h"
//test

PlayGround::PlayGround()
{
}


PlayGround::~PlayGround()
{

}

//초기화 해주는 곳임
HRESULT PlayGround::Init()
{
    gameNode::init(true);
	SCENEMANAGER.addScene("스테이지1.1", new Stage1_1);
	SCENEMANAGER.addScene("SelectScene", new SelectScene);
	SCENEMANAGER.changeScene("SelectScene");

	_UI = new PlayUI;

    return S_OK;
}

//메모리 해제 (동적할당 해제등)
void PlayGround::Release()
{
    gameNode::Release();

}


//연산
void PlayGround::Update()
{
    gameNode::Update();


    SCENEMANAGER.update();
    ZORDER.Update();
    BULLET.BulletUpdate();
    EFFECTMANAGER.update();

    //CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, true);
}

//그려주는
void PlayGround::Render()
{
    PatBlt(getMemDC(), 0, 0, GAMESIZEX, GAMESIZEY, BLACKNESS);


    SCENEMANAGER.render();//=>이건 씬에서 제트오더 안쓰는 애들렌더
    ZORDER.Render();//=>제트오더렌더는 여기서쓰니까 씬에서 따로 얘써줄필요없음 제트오더에 객체추가만 하면됨
    EFFECTMANAGER.render();
	_UI->render();
    CAM.Render(getHDC());
}
