#pragma once
#include "SingleTonBase.h"
#include "image.h"
#include <map>

class ImageManager:public SingleTonBase<ImageManager>
{
private:
	typedef map<string, image*>					imageMapList;
	typedef map<string, image*>::iterator		imageMapIter;
private:
	imageMapList mList;
public:
	ImageManager();
	~ImageManager();

	HRESULT Init();
	void Release();

	//�̹��� ã��
	image* findImage(string fName);

	//�̹��� �߰�
	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, 
		int width, int height, bool trans, COLORREF transColor);
	image* addImage(string strKey, const char* fileName, 
		float x, float y, int width, int height, bool trans, COLORREF transColor);

	//������ �̹��� �߰�
	image* addFrameImage(string strKey, const char* fileName, float x, float y, 
		int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, 
		int frameX, int frameY, bool trans, COLORREF transColor);

	//�̹��� ����
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, 
		int sourWidth, int sourHeight);

	//������ �̹��� ����
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, 
		int currentFrameX, int currentFrameY);

	//�̹��� ����
	BOOL deleteImage(string strKey);
	BOOL deleteAll(void);
};

