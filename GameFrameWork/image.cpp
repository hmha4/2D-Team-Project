#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

image::image()
    :_imageInfo(NULL), _fileName(NULL), _trans(false), _transColor(RGB(0, 0, 0)), _alpha(true)
{
}


image::~image()
{
}

HRESULT image::init(BOOL alpha)
{
    _alpha = alpha;
    return S_OK;
}

HRESULT image::init(int width, int height)
{
    //이미지 정보가 남아있다면 해제한다
    if (_imageInfo != NULL) Release();

    HDC hdc = GetDC(g_hWnd);

    _imageInfo = new ImageInfo;
    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //빈 비트맵 이미지
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;

    //비트맵이 생성이 되지않았다면
    if (_imageInfo->hBit == NULL)
    {
        //해제시키고
        Release();
        //초기화 실패 출력해줘라
        return E_FAIL;
    }

    if (_alpha)
    {
        //알파블랜드 셋팅
        _blendFunc.BlendFlags = 0;
        _blendFunc.AlphaFormat = 0;
        _blendFunc.BlendOp = AC_SRC_OVER;

        _blendImage = new ImageInfo;
        _blendImage->loadType = LOAD_EMPTY;
        _blendImage->hMemDC = CreateCompatibleDC(hdc);
        _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
        _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
        _blendImage->width = width;
        _blendImage->height = height;
    }

    ReleaseDC(g_hWnd, hdc);
    return S_OK;
}

//파일로부터 초기화 파일명, 파일가로크기 , 파일세로크기, 제외칼라
HRESULT image::init(const char * fileName, int width, int height,
    BOOL trans, COLORREF transColor)
{
    //이미지 정보가 남아있다면 해제한다
    if (_imageInfo != NULL)Release();

    HDC hdc = GetDC(g_hWnd);

    _imageInfo = new ImageInfo;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->width = width;
    _imageInfo->height = height;

    if (_alpha)
    {
        //알파블랜드 셋팅
        _blendFunc.BlendFlags = 0;
        _blendFunc.AlphaFormat = 0;
        _blendFunc.BlendOp = AC_SRC_OVER;

        _blendImage = new ImageInfo;
        _blendImage->loadType = LOAD_EMPTY;
        _blendImage->hMemDC = CreateCompatibleDC(hdc);
        _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
        _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
        _blendImage->width = width;
        _blendImage->height = height;
    }


    int len = strlen(fileName);
    _fileName = new CHAR[len + 1];
    strcpy(_fileName, fileName);

    _trans = trans;
    _transColor = transColor;

    //비트맵이 생성되지 않았으면
    if (_imageInfo->hBit == NULL)
    {
        //메모리해제시키고
        Release();
        //초기화 실패 띄운다
        return E_FAIL;
    }

    ReleaseDC(g_hWnd, hdc);//할당받은 윈도우핸들 반납
    return S_OK;
}

HRESULT image::init(const char * fileName, int x, int y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
    if (_imageInfo != NULL)
        Release();
    HDC hdc = GetDC(g_hWnd);

    _imageInfo = new ImageInfo;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;
    _imageInfo->x = x;
    _imageInfo->y = y;
    _imageInfo->resID = 0;
    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->curFrameXIdx = 0;						//현재프레임번호 초기화
    _imageInfo->curFrameYIdx = 0;						//현재프레임번호 초기화
    _imageInfo->frameWidth = width / frameX;		//이미지 너비를 프레임x개수로 나눔
    _imageInfo->frameHeight = height / frameY;   //이미지 높이를 프레임y개수로 나눔
    _imageInfo->maxFrameXIdx = frameX - 1;      //최대 프레임 인덱스x
    _imageInfo->maxFrameYIdx = frameY - 1;       //최대 프레임 인덱스y

    if (_alpha)
    {
        //알파블랜드 셋팅
        _blendFunc.BlendFlags = 0;
        _blendFunc.AlphaFormat = 0;
        _blendFunc.BlendOp = AC_SRC_OVER;

        _blendImage = new ImageInfo;
        _blendImage->loadType = LOAD_EMPTY;
        _blendImage->hMemDC = CreateCompatibleDC(hdc);
        _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
        _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
        _blendImage->width = width;
        _blendImage->height = height;
    }

    int len = strlen(fileName);
    _fileName = new char[len + 1];
    strcpy(_fileName, fileName);
    _trans = trans;
    _transColor = transColor;

    if (_imageInfo->hBit == NULL)
    {
        Release();
        return E_FAIL;
    }
    ReleaseDC(g_hWnd, hdc);
    return S_OK;
}

HRESULT image::init(const char*fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
    if (_imageInfo != NULL)
        Release();

    HDC hdc = GetDC(g_hWnd);

    _imageInfo = new ImageInfo;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;
    _imageInfo->resID = 0;
    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->curFrameXIdx = 0;
    _imageInfo->curFrameYIdx = 0;
    _imageInfo->frameWidth = width / frameX;
    _imageInfo->frameHeight = height / frameY;
    _imageInfo->maxFrameXIdx = frameX - 1;
    _imageInfo->maxFrameYIdx = frameY - 1;

    if (_alpha)
    {
        //알파블랜드 셋팅
        _blendFunc.BlendFlags = 0;
        _blendFunc.AlphaFormat = 0;
        _blendFunc.BlendOp = AC_SRC_OVER;

        _blendImage = new ImageInfo;
        _blendImage->loadType = LOAD_EMPTY;
        _blendImage->hMemDC = CreateCompatibleDC(hdc);
        _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
        _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
        _blendImage->width = width;
        _blendImage->height = height;
    }

    int len = strlen(fileName);
    _fileName = new char[len + 1];
    strcpy(_fileName, fileName);
    _trans = trans;
    _transColor = transColor;

    if (_imageInfo->hBit == NULL)
    {
        Release();
        return E_FAIL;
    }

    ReleaseDC(g_hWnd, hdc);
    return S_OK;
}

//메모리 해제 함수
void image::Release()
{
    if (_imageInfo)
    {
        SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
        DeleteObject(_imageInfo->hBit);
        DeleteDC(_imageInfo->hMemDC);

        SAFE_DELETE(_imageInfo);
        SAFE_DELETE(_fileName);
        _trans = false;
        _transColor = NULL;
    }
}


//날려줄 컬러가 변경이 되어야한다면 사용할 함수
void image::setTransColor(BOOL trans, COLORREF transColor)
{
    _trans = trans;
    _transColor = transColor;
}


//렌더링 함수 뿌릴DC , left , top 좌표
void image::Render(HDC hdc, int destX, int destY)
{

    if (_trans)//제외시킬 색상이 있으면
    {
        GdiTransparentBlt(
            hdc,								//뿌려줄DC
            destX,							//뿌려줄 위치(left)
            destY,							//뿌려줄 위치(top)
            _imageInfo->width,		//가로크기
            _imageInfo->height,		//세로크기
            _imageInfo->hMemDC,//복사해올 DC
            0, 0,								//복사해올 left,top
            _imageInfo->width,		//복사해올 가로크기
            _imageInfo->height,		//복사해올 세로크기
            _transColor					//제외시킬 색상
        );
    }
    else//제외시킬 색상이 없으면
    {
        BitBlt(hdc, destX, destY,
            _imageInfo->width,
            _imageInfo->height,
            _imageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

void image::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
    if (_trans)//제외시킬 색상이 있으면
    {
        GdiTransparentBlt(
            hdc,								//뿌려줄DC
            destX,							//뿌려줄 위치(left)
            destY,							//뿌려줄 위치(top)
            sourWidth,					//가로크기
            sourHeight,					//세로크기
            _imageInfo->hMemDC,//복사해올 DC
            sourX,							//복사해올 위치(left)
            sourY,							//복사해올	위치(top)
            sourWidth,					//복사해올 가로크기
            sourHeight,					//복사해올 세로크기
            _transColor					//제외시킬 색상
        );
    }
    else//제외시킬 색상이 없으면
    {
        BitBlt(
            hdc,								//뿌려줄DC
            destX,							//뿌려줄 위치(left)
            destY,							//뿌려줄 위치(top)
            sourWidth,					//가로크기
            sourHeight,					//세로크기
            _imageInfo->hMemDC,//복사해올 DC
            sourX,							//복사해올 위치(left) 
            sourY,							//복사해올 위치(top)
            SRCCOPY);
    }
}

void image::LoopRender(HDC hdc, const RECT rc, int offsetX, int offsetY)
{
    if (offsetX < 0)offsetX = _imageInfo->width + (offsetX%_imageInfo->width);
    if (offsetY < 0)offsetY = _imageInfo->height + (offsetY%_imageInfo->height);

    //연속으로 보여줄 화면의 좌상단과 너비,높이
    int rectLeft = rc.left;
    int rectTop = rc.top;
    int rectWidth = rc.right - rc.left;
    int rectHeight = rc.bottom - rc.top;

    //화면에 출력할 위치렉트설정
    RECT destRect;

    //화면에 복사할 위치렉트와 복사할 너비,높이
    RECT sourRect;
    float sourWidth = 0;
    float sourHeight = 0;

    //먼저 x축부터 하기
    for (int i = 0; i < rectWidth; i += sourWidth)
    {
        //복사할 레프트 위치 설정 
        sourRect.left = (i + offsetX) % _imageInfo->width;
        //복사할 라이트 위치 설정
        sourRect.right = _imageInfo->width;
        //복사할 너비 설정
        sourWidth = sourRect.right - sourRect.left;

        //화면밖으로 나간 렉트계산
        if (i + sourWidth > rectWidth)
        {
            //라이트 위치 다시계산
            sourRect.right = sourRect.right - (i + sourWidth) + rectWidth;
            sourWidth = sourRect.right - sourRect.left;
        }

        //출력할 레프트라이트
        destRect.left = i + rectLeft;
        destRect.right = destRect.left + sourWidth;

        for (int j = 0; j < rectHeight; j += sourHeight)
        {
            //복사할 탑 위치 설정
            sourRect.top = (j + offsetY) % _imageInfo->height;
            //복사할 바텀 위치 설정
            sourRect.bottom = _imageInfo->height;
            //복사할 높이 설정
            sourHeight = sourRect.bottom - sourRect.top;

            //화면밖으로 나간 렉트계산
            if (j + sourHeight > rectHeight)
            {
                //라이트 위치 다시계산
                sourRect.bottom = sourRect.bottom - (j + rectHeight) + rectWidth;
                sourHeight = sourRect.bottom - sourRect.top;
            }

            //출력할 탑 바텀
            destRect.top = j + rectTop;
            destRect.bottom = destRect.top + sourHeight;

            Render(
                hdc,
                destRect.left,
                destRect.top,
                sourRect.left,
                sourRect.top,
                sourWidth,
                sourHeight);
        }
    }
}

void image::frameRender(HDC hdc, int destX, int destY)
{
    if (!FrustumCull(destX, destY)) return;

    if (_trans)
    {
        GdiTransparentBlt(
            hdc,																					//복사할DC
            destX,																				//출력할 위치(left)
            destY,																				//출력할 위치(top)
            _imageInfo->frameWidth,												//출력할 너비
            _imageInfo->frameHeight,												//출력할 높이 
            _imageInfo->hMemDC,														//복사해올DC
            _imageInfo->curFrameXIdx*_imageInfo->frameWidth,	//복사해올	 위치(left)
            _imageInfo->curFrameYIdx*_imageInfo->frameHeight,	//복사해올 높이(top)
            _imageInfo->frameWidth,												//복사해올 너비
            _imageInfo->frameHeight,												//복사해올 높이
            _transColor);
    }
    else
    {
        BitBlt(
            hdc,																					//복사할DC
            destX,																				//출력할 위치(left)
            destY,																				//출력할 위치(top)
            _imageInfo->frameWidth,												//출력할 너비
            _imageInfo->frameHeight,												//출력할 높이
            _imageInfo->hMemDC,														//복사해올DC
            _imageInfo->curFrameXIdx*_imageInfo->frameWidth,	//복사해올 위치(left)
            _imageInfo->curFrameYIdx*_imageInfo->frameHeight,	//복사해올 높이(top)
            SRCCOPY);
    }
}

void image::frameRender(HDC hdc, int destX, int destY, int curFrameX, int curFrameY)
{
    if (!FrustumCull(destX, destY)) return;

    _imageInfo->curFrameXIdx = curFrameX;
    _imageInfo->curFrameYIdx = curFrameY;

    if (_trans)
    {
        GdiTransparentBlt(
            hdc,
            destX,
            destY,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            curFrameX * _imageInfo->frameWidth,
            curFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _transColor
        );
    }
    else
    {
        BitBlt(hdc,
            destX,
            destY,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            curFrameX * _imageInfo->frameWidth,
            curFrameY * _imageInfo->frameHeight,
            SRCCOPY);
    }
}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
{
    if (!FrustumCull(destX, destY)) return;

    Render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::alphaAniRender(HDC hdc, int destX, int destY, animation * ani, BYTE alpha)
{
    if (!FrustumCull(destX, destY)) return;

    //프레임 위치에 맞게 이미지를 뿌려준다
    alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
    //실제 이미지에 알파블렌드를 접목시켜주는 함수
    _blendFunc.SourceConstantAlpha = alpha;

    //마젠타 색상처럼 제외시킬 색상이 있다면
    if (_trans)
    {
        BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
            hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

        GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

        AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
            _blendImage->hMemDC,
            0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
    }
    else
    {
        AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC,
            0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
    }
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
    if (!FrustumCull(destX, destY)) return;

    //실제 이미지에 알파블렌드를 접목시켜주는 함수
    _blendFunc.SourceConstantAlpha = alpha;

    //마젠타 색상처럼 제외시킬 색상이 있다면
    if (_trans)
    {
        //블랜딩DC영역에 메모리 DC영역에 이미지 부분에 그려진걸 복사함
        BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
            hdc, destX, destY, SRCCOPY);

        //블랜딩DC영역에 이미지(우리가 보여주는)영역을 복사=>이미지가 들어간 DC영역이므로
        GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

        //이렇게 블랜딩DC에 복사된 이미지를 다시 메모리 DC영역에 복사(알파값줘야함)
        AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
            _blendImage->hMemDC,
            0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
    }
    else
    {
        //마젠타로 지울영역이 없을때는 알파블랜드함수만 사용하여 복사하면 됨
        AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC,
            0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
    }
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
    //실제 이미지에 알파블렌드를 접목시켜주는 함수
    _blendFunc.SourceConstantAlpha = alpha;

    //마젠타 색상처럼 제외시킬 색상이 있다면
    if (_trans)
    {
        BitBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
            hdc, destX, destY, SRCCOPY);

        GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
            _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

        AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _blendImage->hMemDC,
            0, 0, sourWidth, sourHeight, _blendFunc);
    }
    else
    {
        AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC,
			sourX, sourY, sourWidth, sourHeight, _blendFunc);
    }
}

void image::alphaFrameRender(HDC hdc, BYTE alpha)
{
    //실제 이미지에 알파블렌드를 접목시켜주는 함수
    _blendFunc.SourceConstantAlpha = alpha;

    //마젠타 색상처럼 제외시킬 색상이 있다면
    if (_trans)
    {
        BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
            hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

        GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

        AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _blendImage->hMemDC,
            0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
    }
    else
    {
        AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
    }
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
    if (!FrustumCull(destX, destY)) return;

    //실제 이미지에 알파블렌드를 접목시켜주는 함수
    _blendFunc.SourceConstantAlpha = alpha;

    //마젠타 색상처럼 제외시킬 색상이 있다면
    if (_trans)
    {
        BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
            hdc, destX, destY, SRCCOPY);

        GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);

        AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _blendImage->hMemDC,
            0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
    }
    else
    {
        AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
    }
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int frameX, int frameY, BYTE alpha)
{
	if (!FrustumCull(destX, destY)) return;

	//실제 이미지에 알파블렌드를 접목시켜주는 함수
	_blendFunc.SourceConstantAlpha = alpha;

	//마젠타 색상처럼 제외시킬 색상이 있다면
	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, frameX * _imageInfo->frameWidth, frameY * _imageInfo->frameHeight, _imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC,
			0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			frameX * _imageInfo->frameWidth, frameY * _imageInfo->frameHeight, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}


void image::alphaFrameRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
    //실제 이미지에 알파블렌드를 접목시켜주는 함수
    _blendFunc.SourceConstantAlpha = alpha;

    //마젠타 색상처럼 제외시킬 색상이 있다면
    if (_trans)
    {
        BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
            hdc, destX, destY, SRCCOPY);

        GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
            _imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);

        AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _blendImage->hMemDC,
            sourX, sourY, sourWidth, sourHeight, _blendFunc);
    }
    else
    {
        AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC,
            sourX, sourY, sourWidth, sourHeight, _blendFunc);
    }
}

bool image::FrustumCull(int destX, int destY)
{
    if (_imageInfo->maxFrameXIdx > 0 || _imageInfo->maxFrameYIdx > 0)
    {
        if (destX <= CAM.GetRC().right &&
            destX + _imageInfo->frameWidth >= CAM.GetRC().left &&
            destY <= CAM.GetRC().bottom &&
            destY + _imageInfo->frameHeight >= CAM.GetRC().top)
        {
            return true;
        }
    }
    else if (_imageInfo->maxFrameXIdx == 0 && _imageInfo->maxFrameYIdx == 0)
    {
        if (destX <= CAM.GetRC().right &&
            destX + _imageInfo->width >= CAM.GetRC().left &&
            destY <= CAM.GetRC().bottom &&
            destY + _imageInfo->height >= CAM.GetRC().top)
        {
            return true;
        }
    }

    return false;
}
