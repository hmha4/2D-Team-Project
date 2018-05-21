#pragma once
#include "animation.h"
class image
{
public:
    //이미지가 로드되는 타입
    enum IMAGE_LOAD_KIND
    {
        LOAD_RESOURCE,		//리소스로부터
        LOAD_FILE,					//파일로부터
        LOAD_EMPTY,				//빈 비트맵을 생성
        LOAD_END
    };

    struct ImageInfo
    {
        DWORD		resID;			//리소스 불러올때 레지스터 넘버
        HDC				hMemDC;		//메모리 DC
        HBITMAP		hBit;				//비트맵
        HBITMAP		hOBit;			//올드비트맵
        int				width;
        int				height;
        BYTE			loadType;
        RECT			BoundingBox;

        //프레임은 여러장의 사진이 있는 이미지를 말한다
        float				x;							//출력할x좌표 레프트 
        float				y;							//출력할y좌표  탑
        int				curFrameXIdx;		//현재 프레임의 x 번호
        int				curFrameYIdx;		//현재 프레임의 y 번호
        int			    maxFrameXIdx;	//최대 프레임의 x 번호
        int				maxFrameYIdx;	//최대 프레임의 y 번호
        int				frameWidth;			//프레임 너비
        int				frameHeight;		//프레임 높이

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
    ImageInfo*_imageInfo;			//이미지 정보 구조체
    CHAR*_fileName;					//파일로부터 로드해올때 파일이름 저장
    BOOL _trans;						//특정컬러를 제외시킬건지
    COLORREF _transColor;		//특정컬러 값이 무엇인지

    BLENDFUNCTION _blendFunc;	 //알파블렌드 함수
    ImageInfo*_blendImage;			 //알파블렌드 이미지
    BOOL _alpha;						//알파를 먹일 이미지인지 아닌지

public:
    image();
    ~image();

    HRESULT init(BOOL alpha); // 알파를 먹일 이미지인지 설정

    HRESULT init(int width, int height);

    HRESULT init(const char*fileName, int width, int height,
        BOOL trans = FALSE, COLORREF transColor = FALSE);

    //여러장의 사진으로 되있는 프레임을 초기화할때(x,y좌표까지 같이 설정할때)
    HRESULT init(const char*fileName, int x, int y, int width, int height,
        int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);

    //여러장의 사진으로 되있는 프레임을 초기화할때(x,y좌표 없이)
    HRESULT init(const char*fileName, int width, int height, int frameX, int frameY,
        BOOL trans = FALSE, COLORREF transColor = FALSE);

    //메모리 해제함수
    void Release();

    //날려줄 컬러가 변경이 되어야 한다면 사용할 함수
    void setTransColor(BOOL trans, COLORREF transColor);

    //렌더링 함수 뿌릴DC, left, top 좌표
    void Render(HDC hdc, int destX, int destY);

    //렌더링 함수 이미지의 특정부분을 잘라서 보여줄때 사용
    void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

    //루프렌더
    void LoopRender(HDC hdc, const RECT rc, int offsetX, int offsetY);

    //렌더링 함수 프레임(여러사진)으로 되있는 이미지 출력할때 사용
    void frameRender(HDC hdc, int destX, int destY);

    //렌더링 함수 프레임(여러사진)으로 되있는 이미지를 프레임인덱스로 출력할때 사용
    void frameRender(HDC hdc, int destX, int destY, int curFrameX, int curFrameY);

    //에니메이션 렌더
    void aniRender(HDC hdc, int destX, int destY, animation*ani);
    void alphaAniRender(HDC hdc, int destX, int destY, animation * ani, BYTE alpha);

    //알파 렌더링 함수
    void alphaRender(HDC hdc, BYTE alpha);
    void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
    void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

    //알파 프레임 렌더링 함수
    void alphaFrameRender(HDC hdc, BYTE alpha);
    void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY, int frameX, int frameY, BYTE alpha);
    void alphaFrameRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

    inline HDC getMemDC() { return _imageInfo->hMemDC; }

    bool FrustumCull(int destX, int destY);

    //이미지 조작을 간편하게 하기위한 Getter,Setter
    //x,y좌표
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

    //중점좌표개념으로 셋팅하기
    inline void SetCenter(float x, float y)
    {
        //단일 이미지일때는 최대프레임인덱스가 0을넘지 않기때문
        if (_imageInfo->maxFrameXIdx <= 0 && _imageInfo->maxFrameYIdx <= 0) // 단일 이미지일때
        {
            _imageInfo->x = x - (_imageInfo->width / 2);
            _imageInfo->y = y - (_imageInfo->height / 2);
        }
        else // 프레임 이미지일때
        {
            _imageInfo->x = x - (_imageInfo->frameWidth / 2);
            _imageInfo->y = y - (_imageInfo->frameHeight / 2);
        }
    }

    //중점 x좌표 
    inline float GetCenterX()
    {
        //단일이미지 일때는 너비를 이용 
        //프레임이미지 일때는 프레임 너비 이용
        return _imageInfo->maxFrameXIdx <= 0 ? _imageInfo->x + (_imageInfo->width / 2) : _imageInfo->x + (_imageInfo->frameWidth / 2);
    }

    //중점 y좌표
    inline float GetCenterY()
    {
        //단일이미지 일때는 높이를 이용 
        //프레임이미지 일때는 프레임 높이 이용
        return _imageInfo->maxFrameYIdx <= 0 ? _imageInfo->y + (_imageInfo->height / 2) : _imageInfo->y + (_imageInfo->frameHeight / 2);
    }

    //충돌체크용 바운딩박스
    inline RECT boundingBox()
    {
        //이미지는 레프트,탑을 기준으로 만들어지기 때문에 x,y를 레프트,탑에 맞춘다
        if (_imageInfo->maxFrameXIdx <= 0 && _imageInfo->maxFrameYIdx <= 0) // 단일 이미지일때
        {
            RECT rc = { _imageInfo->x,_imageInfo->y,
                _imageInfo->x + _imageInfo->width,
                _imageInfo->y + _imageInfo->height };
        }
        else // 프레임 이미지일때
        {
            RECT rc = { _imageInfo->x,_imageInfo->y,
                _imageInfo->x + _imageInfo->frameWidth,
                _imageInfo->y + _imageInfo->frameHeight };
        }
    }

    //프레임번호 
    inline int GetFrameX() { return _imageInfo->curFrameXIdx; }
    inline int GetFrameY() { return _imageInfo->curFrameYIdx; }

    inline void SetFrameX(int frameX)
    {
        _imageInfo->curFrameXIdx = frameX;
        //만약 내가 설정한 인덱스가 최대인덱스보다 커지면
        if (_imageInfo->curFrameXIdx > _imageInfo->maxFrameXIdx)
        {
            //최대인덱스로 고정 : 이미지가 벗어나는걸 방지
            _imageInfo->curFrameXIdx = _imageInfo->maxFrameXIdx;
        }
    }
    inline void SetFrameY(int frameY)
    {
        _imageInfo->curFrameYIdx = frameY;
        //만약 내가 설정한 인덱스가 최대인덱스보다 커지면
        if (_imageInfo->curFrameYIdx > _imageInfo->maxFrameYIdx)
        {
            //최대인덱스로 고정 : 이미지가 벗어나는걸 방지
            _imageInfo->curFrameYIdx = _imageInfo->maxFrameYIdx;
        }
    }
};

