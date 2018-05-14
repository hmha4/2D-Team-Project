#include "stdafx.h"
#include "TileMap.h"


TileMap::TileMap()
{
    IMAGEMANAGER.addFrameImage("타일맵", PathFile("image", "타일투").c_str(), 650, 400, 13, 8, false, RGB(255, 0, 255));
    IMAGEMANAGER.addFrameImage("버튼", PathFile("image", "버튼").c_str(), 122, 62, 1, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER.addFrameImage("타일메인", PathFile("image", "타일메인").c_str(), 600, 400, 1, 1, true, RGB(255, 0, 255));
}


TileMap::~TileMap()
{
}

HRESULT TileMap::Init()
{
    cam = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 10, 10);
    CAM.SetPos(0, 0);

    TileInit();

    //버튼초기화

    for (int i = 0; i < 4; i++)
        buttons[i] = new button;

    buttons[0]->Init(IMAGEMANAGER.findImage("버튼"), "NONE", WINSIZEX / 2, WINSIZEY / 2, "돋음채", 20);
    buttons[1]->Init(IMAGEMANAGER.findImage("버튼"), "PLAYERSPAWN", WINSIZEX / 2, WINSIZEY / 2, "돋음채", 18);
    buttons[2]->Init(IMAGEMANAGER.findImage("버튼"), "ROAD", WINSIZEX / 2, WINSIZEY / 2, "돋음채", 20);
    buttons[3]->Init(IMAGEMANAGER.findImage("버튼"), "BLOCK", WINSIZEX / 2, WINSIZEY / 2, "돋음채", 20);

    save = new button;
    save->Init(IMAGEMANAGER.findImage("버튼"), "SAVE", WINSIZEX / 2, WINSIZEY / 2, "돋음채", 20);

    load = new button;
    load->Init(IMAGEMANAGER.findImage("버튼"), "LOAD", WINSIZEX / 2, WINSIZEY / 2, "돋음채", 20);

    metaIdx = -1;
    return S_OK;
}

void TileMap::Render()
{
    ShowTileRender();	//설치될타일랜더

    if (KEYMANAGER.isToggleKey('I'))
    {
        IMAGEMANAGER.findImage("타일메인")->Render(getMemDC(), CAM.GetX() + 680, CAM.GetY() + 400);
        BuildTileRender();	//설치할타일랜더
        ButtonsRender();	//버튼랜더
    }

}

void TileMap::Update()
{
    ControlCam();		//카메라조작
    ButtonsUpdate();	//버튼
    SelectTileMap();	//타일맵선택

    RECT rect = RectMake(CAM.GetX() + 630, CAM.GetY(), 650, 500);
    if (!PtInRect(&rect, TransCamMouse()))
        SettingTileMap();	//타일맵셋팅
}

void TileMap::Release()
{
}

void TileMap::TileInit()
{
    //설치할 타일맵 초기화
    buildTiles = new TileInfo[BUILDTILEX*BUILDTILEY];

    for (int i = 0; i < BUILDTILEY; i++)
    {
        for (int j = 0; j < BUILDTILEX; j++)
        {
            buildTiles[j + BUILDTILEX*i].tileName = "tile";
            buildTiles[j + BUILDTILEX*i].tileImg = IMAGEMANAGER.findImage("타일맵");
            buildTiles[j + BUILDTILEX*i].tileType = TileInfo::NONE;
            buildTiles[j + BUILDTILEX*i].frameX = j;
            buildTiles[j + BUILDTILEX*i].frameY = i;
            buildTiles[j + BUILDTILEX*i].rc = RectMake(WINSIZEX - j*TILESIZEXY,
                i*TILESIZEXY,
                TILESIZEXY,
                TILESIZEXY);
        }
    }

    //선택한 타일 초기화
    selectTile = new TileInfo;
    selectTile->tileImg = NULL;
    selectTile->tileType = TileInfo::NONE;

    //설치될 타일공간
    showTiles = new TileInfo[SHOWTILEX*SHOWTILEY];

    for (int i = 0; i < SHOWTILEY; i++)
    {
        for (int j = 0; j < SHOWTILEX; j++)
        {
            showTiles[j + SHOWTILEX*i].tileName = "tile";
            showTiles[j + SHOWTILEX*i].tileImg = NULL;
            showTiles[j + SHOWTILEX*i].tileType = TileInfo::NONE;
            showTiles[j + SHOWTILEX*i].frameX = j;
            showTiles[j + SHOWTILEX*i].frameY = i;
            showTiles[j + SHOWTILEX*i].rc = RectMake(j*TILESIZEXY, i*TILESIZEXY, TILESIZEXY, TILESIZEXY);
        }
    }
}

void TileMap::BuildTileRender()
{
    for (int i = 0; i < BUILDTILEY; i++)
    {
        for (int j = 0; j < BUILDTILEX; j++)
        {
            buildTiles[j + BUILDTILEX*i].rc = RectMake(WINSIZEX - j*TILESIZEXY + CAM.GetX(), i*TILESIZEXY + CAM.GetY(), TILESIZEXY, TILESIZEXY);


            buildTiles[j + BUILDTILEX*i].tileImg->frameRender(getMemDC(),
                buildTiles[j + BUILDTILEX*i].rc.left,
                buildTiles[j + BUILDTILEX*i].rc.top,
                buildTiles[j + BUILDTILEX*i].frameX,
                buildTiles[j + BUILDTILEX*i].frameY);
        }
    }

    for (int i = 0; i < BUILDTILEY; i++)
    {
        for (int j = 0; j < BUILDTILEX; j++)
        {
            if (buildTiles[j + BUILDTILEX*i].tileType != TileInfo::NONE)
                DrawRect(getMemDC(), buildTiles[j + BUILDTILEX*i].rc,
                    5, RGB(0, 0, 255));
        }
    }

    if (selectTile->tileType != TileInfo::NONE)
    {
        selectTile->tileImg->frameRender(getMemDC(),
            TransCamMouse().x - TILESIZEXY / 2,
            TransCamMouse().y - TILESIZEXY / 2,
            selectTile->frameX,
            selectTile->frameY);
    }
}

void TileMap::ShowTileRender()
{
    for (int i = 0; i < SHOWTILEY; i++)
    {
        for (int j = 0; j < SHOWTILEX; j++)
        {
            //NONE상태의 벽돌은 그냥 렉트랜더하고
            if (showTiles[j + SHOWTILEX*i].tileType == TileInfo::NONE)
            {
                Rectangle(getMemDC(),
                    showTiles[j + SHOWTILEX*i].rc.left,
                    showTiles[j + SHOWTILEX*i].rc.top,
                    showTiles[j + SHOWTILEX*i].rc.right,
                    showTiles[j + SHOWTILEX*i].rc.bottom);
            }
            else
            {
                //아니면 그림정보 렌더해야함 이건 렌더맵에서 따로 잘라서 보여주기식
                showTiles[j + SHOWTILEX*i].tileImg->frameRender(getMemDC(),
                    showTiles[j + SHOWTILEX*i].rc.left,
                    showTiles[j + SHOWTILEX*i].rc.top,
                    showTiles[j + SHOWTILEX*i].frameX,
                    showTiles[j + SHOWTILEX*i].frameY);
            }
        }
    }

}

void TileMap::ButtonsRender()
{
    for (int i = 0; i < 4; i++)
    {
        buttons[i]->Render();
        if (selectTile->tileType == i)
        {
            DrawRect(getMemDC(), buttons[i]->GetRect(), 3, RGB(0, 0, 255));
        }
    }
    save->Render();
    load->Render();
}

void TileMap::ButtonsUpdate()
{
    for (int i = 0; i < 4; i++)
    {
        buttons[i]->Update(VK_LBUTTON, false);
        buttons[i]->GetRect() = RectMake(CAM.GetX() + 680 + 160 * i, CAM.GetY() + 400, 122, 31);
    }
    save->Update(VK_LBUTTON, false);
    save->GetRect() = RectMake(CAM.GetX() + 840, CAM.GetY() + 450, 122, 31);

    load->Update(VK_LBUTTON, false);
    load->GetRect() = RectMake(CAM.GetX() + 1000, CAM.GetY() + 450, 122, 31);

    if (save->IsOnceClick())
    {
        SaveTileMap();
        MessageBox(g_hWnd, "저장되었습니다", "SaveTileMap", MB_OK);
        save->IsOnceClick() = false;
    }

    if (load->IsOnceClick())
    {
        LoadTileMap();
        MessageBox(g_hWnd, "로드했습니다", "LoadTileMap", MB_OK);
        load->IsOnceClick() = false;
    }

    if (selectTile->tileType != TileInfo::NONE)
    {
        //NONE버튼 눌렀을때 selectTile 다시 NULL로
        if (buttons[0]->IsStayClick())
        {
            selectTile->tileType = TileInfo::NONE;
            buildTiles[selectTile->frameX + selectTile->frameY*BUILDTILEX].tileType = selectTile->tileType;
            for (int i = 0; i<4; i++)
                buttons[i]->IsStayClick() = false;
        }

        //PLAYERSPAWN버튼 눌렀을때
        if (buttons[1]->IsStayClick())
        {
            selectTile->tileType = TileInfo::PLAYER_SPAWN;
        }

        //ROAD버튼 눌렀을때
        if (buttons[2]->IsStayClick())
        {
            selectTile->tileType = TileInfo::ROAD;
        }

        //BLOCK버튼 눌렀을때
        if (buttons[3]->IsStayClick())
        {
            selectTile->tileType = TileInfo::BLOCK;
        }
    }
}

void TileMap::ControlCam()
{
    if (KEYMANAGER.isStayKeyDown(VK_LEFT))
    {
        cam.left -= 5;
        cam.right -= 5;
    }
    if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
    {
        cam.left += 5;
        cam.right += 5;
    }
    if (KEYMANAGER.isStayKeyDown(VK_UP))
    {
        cam.top -= 5;
        cam.bottom -= 5;
    }
    if (KEYMANAGER.isStayKeyDown(VK_DOWN))
    {
        cam.top += 5;
        cam.bottom += 5;
    }
    CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, true);
}

void TileMap::SelectTileMap()
{
    //마우스와 빌드타일의 충돌로 판별
    for (int i = 0; i < BUILDTILEY; i++)
    {
        for (int j = 0; j < BUILDTILEX; j++)
        {
            //마우스로 설치할 타일중하나를 선택했을때
            if (PtInRect(&buildTiles[j + i*BUILDTILEX].rc, TransCamMouse()) &&
                KEYMANAGER.isOnceKeyDown(VK_LBUTTON))
            {
                if (metaIdx != -1)
                    buildTiles[metaIdx].tileType = TileInfo::NONE;

                selectTile = &buildTiles[j + i*BUILDTILEX];
                selectTile->tileType = TileInfo::ROAD;
                metaIdx = j + i*BUILDTILEX;
                break;
            }
        }
    }
}



void TileMap::SettingTileMap()
{
    for (int i = 0; i < SHOWTILEY; i++)
    {
        for (int j = 0; j < SHOWTILEX; j++)
        {
            if (PtInRect(&showTiles[j + i*SHOWTILEX].rc, TransCamMouse())
                && KEYMANAGER.isStayKeyDown(VK_LBUTTON))
            {
                showTiles[j + i*SHOWTILEX].tileImg = selectTile->tileImg;
                showTiles[j + i*SHOWTILEX].tileType = selectTile->tileType;
                showTiles[j + i*SHOWTILEX].frameX = selectTile->frameX;
                showTiles[j + i*SHOWTILEX].frameY = selectTile->frameY;
            }
        }
    }
}

void TileMap::SaveTileMap()
{
    FILE*fp;
    fopen_s(&fp, "타일맵데이터.txt", "w+t");

    char next = '\n';
    char token = '\t';
    char end = '@';

    string temp = "TileType\txPos\tyPos\tframeX\tframeY\n";
    fwrite(temp.c_str(), temp.size(), 1, fp);

    for (int i = 0; i < SHOWTILEY; i++)
    {
        for (int j = 0; j < SHOWTILEX; j++)
        {
            temp = showTiles[j + i*SHOWTILEX].tileName +
                token +
                to_string(showTiles[j + i*SHOWTILEX].tileType) +
                token +
                to_string(showTiles[j + i*SHOWTILEX].rc.left) +
                token +
                to_string(showTiles[j + i*SHOWTILEX].rc.top) +
                token +
                to_string(showTiles[j + i*SHOWTILEX].frameX) +
                token +
                to_string(showTiles[j + i*SHOWTILEX].frameY) +
                next;

            fwrite(temp.c_str(), temp.size(), 1, fp);
        }
    }
    fwrite(&end, sizeof(end), 1, fp);

    fclose(fp);
}

void TileMap::LoadTileMap()
{
    FILE*fp;
    fopen_s(&fp, "타일맵데이터.txt", "r");

    char temp[256];
    int x;
    int y;
    int frameX;
    int frameY;
    int tType;

    while (true)
    {
        fscanf_s(fp, "%s", temp, sizeof(temp));
        if (string(temp).find("frameY", 0) != string::npos)
            break;
    }

    while (true)
    {
        fscanf_s(fp, "%s", temp, sizeof(temp));
        if (temp[0] == '@')break;

        fscanf_s(fp, "%d%d%d%d%d", &tType, &x, &y, &frameX, &frameY);
        showTiles[x / TILESIZEXY + y / TILESIZEXY*SHOWTILEX].tileType = (TileInfo::TILETYPE)tType;
        showTiles[x / TILESIZEXY + y / TILESIZEXY*SHOWTILEX].frameX = frameX;
        showTiles[x / TILESIZEXY + y / TILESIZEXY*SHOWTILEX].frameY = frameY;
        showTiles[x / TILESIZEXY + y / TILESIZEXY*SHOWTILEX].tileImg = IMAGEMANAGER.findImage("타일맵");
    }

    fclose(fp);
}

POINT TileMap::TransCamMouse()
{
    POINT mouse = g_mousePos;
    mouse.x += CAM.GetX();
    mouse.y += CAM.GetY();

    return mouse;
}
