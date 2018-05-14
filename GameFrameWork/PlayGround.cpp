#include "stdafx.h"
#include "playGround.h"


PlayGround::PlayGround()
{
}


PlayGround::~PlayGround()
{

}

//�ʱ�ȭ ���ִ� ����
HRESULT PlayGround::Init()
{
    gameNode::init(true);


    return S_OK;
}

//�޸� ���� (�����Ҵ� ������)
void PlayGround::Release()
{
    gameNode::Release();

}


//����
void PlayGround::Update()
{
    gameNode::Update();


    SCENEMANAGER.update();
    ZORDER.Update();
    BULLET.BulletUpdate();
    EFFECTMANAGER.update();

    CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, true);
}

//�׷��ִ�
void PlayGround::Render()
{
    PatBlt(getMemDC(), 0, 0, GAMESIZEX, GAMESIZEY, BLACKNESS);


    SCENEMANAGER.render();//=>�̰� ������ ��Ʈ���� �Ⱦ��� �ֵ鷻��
    ZORDER.Render();//=>��Ʈ���������� ���⼭���ϱ� ������ ���� ������ʿ���� ��Ʈ������ ��ü�߰��� �ϸ��
    EFFECTMANAGER.render();
    CAM.Render(getHDC());
}
