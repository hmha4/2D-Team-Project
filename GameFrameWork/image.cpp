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
    //�̹��� ������ �����ִٸ� �����Ѵ�
    if (_imageInfo != NULL) Release();

    HDC hdc = GetDC(g_hWnd);

    _imageInfo = new ImageInfo;
    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //�� ��Ʈ�� �̹���
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;

    //��Ʈ���� ������ �����ʾҴٸ�
    if (_imageInfo->hBit == NULL)
    {
        //������Ű��
        Release();
        //�ʱ�ȭ ���� ��������
        return E_FAIL;
    }

    if (_alpha)
    {
        //���ĺ��� ����
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

//���Ϸκ��� �ʱ�ȭ ���ϸ�, ���ϰ���ũ�� , ���ϼ���ũ��, ����Į��
HRESULT image::init(const char * fileName, int width, int height,
    BOOL trans, COLORREF transColor)
{
    //�̹��� ������ �����ִٸ� �����Ѵ�
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
        //���ĺ��� ����
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

    //��Ʈ���� �������� �ʾ�����
    if (_imageInfo->hBit == NULL)
    {
        //�޸�������Ű��
        Release();
        //�ʱ�ȭ ���� ����
        return E_FAIL;
    }

    ReleaseDC(g_hWnd, hdc);//�Ҵ���� �������ڵ� �ݳ�
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
    _imageInfo->curFrameXIdx = 0;						//���������ӹ�ȣ �ʱ�ȭ
    _imageInfo->curFrameYIdx = 0;						//���������ӹ�ȣ �ʱ�ȭ
    _imageInfo->frameWidth = width / frameX;		//�̹��� �ʺ� ������x������ ����
    _imageInfo->frameHeight = height / frameY;   //�̹��� ���̸� ������y������ ����
    _imageInfo->maxFrameXIdx = frameX - 1;      //�ִ� ������ �ε���x
    _imageInfo->maxFrameYIdx = frameY - 1;       //�ִ� ������ �ε���y

    if (_alpha)
    {
        //���ĺ��� ����
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
        //���ĺ��� ����
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

//�޸� ���� �Լ�
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


//������ �÷��� ������ �Ǿ���Ѵٸ� ����� �Լ�
void image::setTransColor(BOOL trans, COLORREF transColor)
{
    _trans = trans;
    _transColor = transColor;
}


//������ �Լ� �Ѹ�DC , left , top ��ǥ
void image::Render(HDC hdc, int destX, int destY)
{

    if (_trans)//���ܽ�ų ������ ������
    {
        GdiTransparentBlt(
            hdc,								//�ѷ���DC
            destX,							//�ѷ��� ��ġ(left)
            destY,							//�ѷ��� ��ġ(top)
            _imageInfo->width,		//����ũ��
            _imageInfo->height,		//����ũ��
            _imageInfo->hMemDC,//�����ؿ� DC
            0, 0,								//�����ؿ� left,top
            _imageInfo->width,		//�����ؿ� ����ũ��
            _imageInfo->height,		//�����ؿ� ����ũ��
            _transColor					//���ܽ�ų ����
        );
    }
    else//���ܽ�ų ������ ������
    {
        BitBlt(hdc, destX, destY,
            _imageInfo->width,
            _imageInfo->height,
            _imageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

void image::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
    if (_trans)//���ܽ�ų ������ ������
    {
        GdiTransparentBlt(
            hdc,								//�ѷ���DC
            destX,							//�ѷ��� ��ġ(left)
            destY,							//�ѷ��� ��ġ(top)
            sourWidth,					//����ũ��
            sourHeight,					//����ũ��
            _imageInfo->hMemDC,//�����ؿ� DC
            sourX,							//�����ؿ� ��ġ(left)
            sourY,							//�����ؿ�	��ġ(top)
            sourWidth,					//�����ؿ� ����ũ��
            sourHeight,					//�����ؿ� ����ũ��
            _transColor					//���ܽ�ų ����
        );
    }
    else//���ܽ�ų ������ ������
    {
        BitBlt(
            hdc,								//�ѷ���DC
            destX,							//�ѷ��� ��ġ(left)
            destY,							//�ѷ��� ��ġ(top)
            sourWidth,					//����ũ��
            sourHeight,					//����ũ��
            _imageInfo->hMemDC,//�����ؿ� DC
            sourX,							//�����ؿ� ��ġ(left) 
            sourY,							//�����ؿ� ��ġ(top)
            SRCCOPY);
    }
}

void image::LoopRender(HDC hdc, const RECT rc, int offsetX, int offsetY)
{
    if (offsetX < 0)offsetX = _imageInfo->width + (offsetX%_imageInfo->width);
    if (offsetY < 0)offsetY = _imageInfo->height + (offsetY%_imageInfo->height);

    //�������� ������ ȭ���� �»�ܰ� �ʺ�,����
    int rectLeft = rc.left;
    int rectTop = rc.top;
    int rectWidth = rc.right - rc.left;
    int rectHeight = rc.bottom - rc.top;

    //ȭ�鿡 ����� ��ġ��Ʈ����
    RECT destRect;

    //ȭ�鿡 ������ ��ġ��Ʈ�� ������ �ʺ�,����
    RECT sourRect;
    float sourWidth = 0;
    float sourHeight = 0;

    //���� x����� �ϱ�
    for (int i = 0; i < rectWidth; i += sourWidth)
    {
        //������ ����Ʈ ��ġ ���� 
        sourRect.left = (i + offsetX) % _imageInfo->width;
        //������ ����Ʈ ��ġ ����
        sourRect.right = _imageInfo->width;
        //������ �ʺ� ����
        sourWidth = sourRect.right - sourRect.left;

        //ȭ������� ���� ��Ʈ���
        if (i + sourWidth > rectWidth)
        {
            //����Ʈ ��ġ �ٽð��
            sourRect.right = sourRect.right - (i + sourWidth) + rectWidth;
            sourWidth = sourRect.right - sourRect.left;
        }

        //����� ����Ʈ����Ʈ
        destRect.left = i + rectLeft;
        destRect.right = destRect.left + sourWidth;

        for (int j = 0; j < rectHeight; j += sourHeight)
        {
            //������ ž ��ġ ����
            sourRect.top = (j + offsetY) % _imageInfo->height;
            //������ ���� ��ġ ����
            sourRect.bottom = _imageInfo->height;
            //������ ���� ����
            sourHeight = sourRect.bottom - sourRect.top;

            //ȭ������� ���� ��Ʈ���
            if (j + sourHeight > rectHeight)
            {
                //����Ʈ ��ġ �ٽð��
                sourRect.bottom = sourRect.bottom - (j + rectHeight) + rectWidth;
                sourHeight = sourRect.bottom - sourRect.top;
            }

            //����� ž ����
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
            hdc,																					//������DC
            destX,																				//����� ��ġ(left)
            destY,																				//����� ��ġ(top)
            _imageInfo->frameWidth,												//����� �ʺ�
            _imageInfo->frameHeight,												//����� ���� 
            _imageInfo->hMemDC,														//�����ؿ�DC
            _imageInfo->curFrameXIdx*_imageInfo->frameWidth,	//�����ؿ�	 ��ġ(left)
            _imageInfo->curFrameYIdx*_imageInfo->frameHeight,	//�����ؿ� ����(top)
            _imageInfo->frameWidth,												//�����ؿ� �ʺ�
            _imageInfo->frameHeight,												//�����ؿ� ����
            _transColor);
    }
    else
    {
        BitBlt(
            hdc,																					//������DC
            destX,																				//����� ��ġ(left)
            destY,																				//����� ��ġ(top)
            _imageInfo->frameWidth,												//����� �ʺ�
            _imageInfo->frameHeight,												//����� ����
            _imageInfo->hMemDC,														//�����ؿ�DC
            _imageInfo->curFrameXIdx*_imageInfo->frameWidth,	//�����ؿ� ��ġ(left)
            _imageInfo->curFrameYIdx*_imageInfo->frameHeight,	//�����ؿ� ����(top)
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

    //������ ��ġ�� �°� �̹����� �ѷ��ش�
    alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
    //���� �̹����� ���ĺ��带 ��������ִ� �Լ�
    _blendFunc.SourceConstantAlpha = alpha;

    //����Ÿ ����ó�� ���ܽ�ų ������ �ִٸ�
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

    //���� �̹����� ���ĺ��带 ��������ִ� �Լ�
    _blendFunc.SourceConstantAlpha = alpha;

    //����Ÿ ����ó�� ���ܽ�ų ������ �ִٸ�
    if (_trans)
    {
        //����DC������ �޸� DC������ �̹��� �κп� �׷����� ������
        BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
            hdc, destX, destY, SRCCOPY);

        //����DC������ �̹���(�츮�� �����ִ�)������ ����=>�̹����� �� DC�����̹Ƿ�
        GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

        //�̷��� ����DC�� ����� �̹����� �ٽ� �޸� DC������ ����(���İ������)
        AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
            _blendImage->hMemDC,
            0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
    }
    else
    {
        //����Ÿ�� ���￵���� �������� ���ĺ����Լ��� ����Ͽ� �����ϸ� ��
        AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC,
            0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
    }
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
    //���� �̹����� ���ĺ��带 ��������ִ� �Լ�
    _blendFunc.SourceConstantAlpha = alpha;

    //����Ÿ ����ó�� ���ܽ�ų ������ �ִٸ�
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
    //���� �̹����� ���ĺ��带 ��������ִ� �Լ�
    _blendFunc.SourceConstantAlpha = alpha;

    //����Ÿ ����ó�� ���ܽ�ų ������ �ִٸ�
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

    //���� �̹����� ���ĺ��带 ��������ִ� �Լ�
    _blendFunc.SourceConstantAlpha = alpha;

    //����Ÿ ����ó�� ���ܽ�ų ������ �ִٸ�
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

	//���� �̹����� ���ĺ��带 ��������ִ� �Լ�
	_blendFunc.SourceConstantAlpha = alpha;

	//����Ÿ ����ó�� ���ܽ�ų ������ �ִٸ�
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
    //���� �̹����� ���ĺ��带 ��������ִ� �Լ�
    _blendFunc.SourceConstantAlpha = alpha;

    //����Ÿ ����ó�� ���ܽ�ų ������ �ִٸ�
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
