#pragma once
#include "animation.h"
class image
{
public:
    //�̹����� �ε�Ǵ� Ÿ��
    enum IMAGE_LOAD_KIND
    {
        LOAD_RESOURCE,		//���ҽ��κ���
        LOAD_FILE,					//���Ϸκ���
        LOAD_EMPTY,				//�� ��Ʈ���� ����
        LOAD_END
    };

    struct ImageInfo
    {
        DWORD		resID;			//���ҽ� �ҷ��ö� �������� �ѹ�
        HDC				hMemDC;		//�޸� DC
        HBITMAP		hBit;				//��Ʈ��
        HBITMAP		hOBit;			//�õ��Ʈ��
        int				width;
        int				height;
        BYTE			loadType;
        RECT			BoundingBox;

        //�������� �������� ������ �ִ� �̹����� ���Ѵ�
        float				x;							//�����x��ǥ ����Ʈ 
        float				y;							//�����y��ǥ  ž
        int				curFrameXIdx;		//���� �������� x ��ȣ
        int				curFrameYIdx;		//���� �������� y ��ȣ
        int			    maxFrameXIdx;	//�ִ� �������� x ��ȣ
        int				maxFrameYIdx;	//�ִ� �������� y ��ȣ
        int				frameWidth;			//������ �ʺ�
        int				frameHeight;		//������ ����

        ImageInfo()
        {
            resID = 0;
            hMemDC = NULL;
            hBit = NULL;
            hOBit = NULL;
            width = 0;
            height = 0;
            loadType = LOAD_RESOURCE;
        }
    };

private:
    ImageInfo*_imageInfo;			//�̹��� ���� ����ü
    CHAR*_fileName;					//���Ϸκ��� �ε��ؿö� �����̸� ����
    BOOL _trans;						//Ư���÷��� ���ܽ�ų����
    COLORREF _transColor;		//Ư���÷� ���� ��������

    BLENDFUNCTION _blendFunc;	 //���ĺ��� �Լ�
    ImageInfo*_blendImage;			 //���ĺ��� �̹���
    BOOL _alpha;						//���ĸ� ���� �̹������� �ƴ���

public:
    image();
    ~image();

    HRESULT init(BOOL alpha); // ���ĸ� ���� �̹������� ����

    HRESULT init(int width, int height);

    HRESULT init(const char*fileName, int width, int height,
        BOOL trans = FALSE, COLORREF transColor = FALSE);

    //�������� �������� ���ִ� �������� �ʱ�ȭ�Ҷ�(x,y��ǥ���� ���� �����Ҷ�)
    HRESULT init(const char*fileName, int x, int y, int width, int height,
        int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);

    //�������� �������� ���ִ� �������� �ʱ�ȭ�Ҷ�(x,y��ǥ ����)
    HRESULT init(const char*fileName, int width, int height, int frameX, int frameY,
        BOOL trans = FALSE, COLORREF transColor = FALSE);

    //�޸� �����Լ�
    void Release();

    //������ �÷��� ������ �Ǿ�� �Ѵٸ� ����� �Լ�
    void setTransColor(BOOL trans, COLORREF transColor);

    //������ �Լ� �Ѹ�DC, left, top ��ǥ
    void Render(HDC hdc, int destX, int destY);

    //������ �Լ� �̹����� Ư���κ��� �߶� �����ٶ� ���
    void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

    //��������
    void LoopRender(HDC hdc, const RECT rc, int offsetX, int offsetY);

    //������ �Լ� ������(��������)���� ���ִ� �̹��� ����Ҷ� ���
    void frameRender(HDC hdc, int destX, int destY);

    //������ �Լ� ������(��������)���� ���ִ� �̹����� �������ε����� ����Ҷ� ���
    void frameRender(HDC hdc, int destX, int destY, int curFrameX, int curFrameY);

    //���ϸ��̼� ����
    void aniRender(HDC hdc, int destX, int destY, animation*ani);
    void alphaAniRender(HDC hdc, int destX, int destY, animation * ani, BYTE alpha);

    //���� ������ �Լ�
    void alphaRender(HDC hdc, BYTE alpha);
    void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
    void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

    //���� ������ ������ �Լ�
    void alphaFrameRender(HDC hdc, BYTE alpha);
    void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY, int frameX, int frameY, BYTE alpha);
    void alphaFrameRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

    inline HDC getMemDC() { return _imageInfo->hMemDC; }

    bool FrustumCull(int destX, int destY);

    //�̹��� ������ �����ϰ� �ϱ����� Getter,Setter
    //x,y��ǥ
    inline float GetX() { return _imageInfo->x; }
    inline float GetY() { return _imageInfo->y; }
    inline void SetX(float x) { _imageInfo->x = x; }
    inline void SetY(float y) { _imageInfo->y = y; }

    //width,height,frameWidth,frameHeight
    inline int GetWidth() { return _imageInfo->width; }
    inline int GetHeight() { return _imageInfo->height; }
    inline int GetFrameWidth() { return _imageInfo->frameWidth; }
    inline int GetFreamHeight() { return _imageInfo->frameHeight; }

    //maxframex,y
    inline int GetMaxFrameX() { return _imageInfo->maxFrameXIdx; }
    inline int GetMaxFrameY() { return _imageInfo->maxFrameYIdx; }

    //������ǥ�������� �����ϱ�
    inline void SetCenter(float x, float y)
    {
        //���� �̹����϶��� �ִ��������ε����� 0������ �ʱ⶧��
        if (_imageInfo->maxFrameXIdx <= 0 && _imageInfo->maxFrameYIdx <= 0) // ���� �̹����϶�
        {
            _imageInfo->x = x - (_imageInfo->width / 2);
            _imageInfo->y = y - (_imageInfo->height / 2);
        }
        else // ������ �̹����϶�
        {
            _imageInfo->x = x - (_imageInfo->frameWidth / 2);
            _imageInfo->y = y - (_imageInfo->frameHeight / 2);
        }
    }

    //���� x��ǥ 
    inline float GetCenterX()
    {
        //�����̹��� �϶��� �ʺ� �̿� 
        //�������̹��� �϶��� ������ �ʺ� �̿�
        return _imageInfo->maxFrameXIdx <= 0 ? _imageInfo->x + (_imageInfo->width / 2) : _imageInfo->x + (_imageInfo->frameWidth / 2);
    }

    //���� y��ǥ
    inline float GetCenterY()
    {
        //�����̹��� �϶��� ���̸� �̿� 
        //�������̹��� �϶��� ������ ���� �̿�
        return _imageInfo->maxFrameYIdx <= 0 ? _imageInfo->y + (_imageInfo->height / 2) : _imageInfo->y + (_imageInfo->frameHeight / 2);
    }

    //�浹üũ�� �ٿ���ڽ�
    inline RECT boundingBox()
    {
        //�̹����� ����Ʈ,ž�� �������� ��������� ������ x,y�� ����Ʈ,ž�� �����
        if (_imageInfo->maxFrameXIdx <= 0 && _imageInfo->maxFrameYIdx <= 0) // ���� �̹����϶�
        {
            RECT rc = { _imageInfo->x,_imageInfo->y,
                _imageInfo->x + _imageInfo->width,
                _imageInfo->y + _imageInfo->height };
        }
        else // ������ �̹����϶�
        {
            RECT rc = { _imageInfo->x,_imageInfo->y,
                _imageInfo->x + _imageInfo->frameWidth,
                _imageInfo->y + _imageInfo->frameHeight };
        }
    }

    //�����ӹ�ȣ 
    inline int GetFrameX() { return _imageInfo->curFrameXIdx; }
    inline int GetFrameY() { return _imageInfo->curFrameYIdx; }

    inline void SetFrameX(int frameX)
    {
        _imageInfo->curFrameXIdx = frameX;
        //���� ���� ������ �ε����� �ִ��ε������� Ŀ����
        if (_imageInfo->curFrameXIdx > _imageInfo->maxFrameXIdx)
        {
            //�ִ��ε����� ���� : �̹����� ����°� ����
            _imageInfo->curFrameXIdx = _imageInfo->maxFrameXIdx;
        }
    }
    inline void SetFrameY(int frameY)
    {
        _imageInfo->curFrameYIdx = frameY;
        //���� ���� ������ �ε����� �ִ��ε������� Ŀ����
        if (_imageInfo->curFrameYIdx > _imageInfo->maxFrameYIdx)
        {
            //�ִ��ε����� ���� : �̹����� ����°� ����
            _imageInfo->curFrameYIdx = _imageInfo->maxFrameYIdx;
        }
    }
};

