#include "stdafx.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

HRESULT ImageManager::Init()
{
	return S_OK;
}

void ImageManager::Release()
{
}

image * ImageManager::findImage(string fName)
{
	//반복자를 이용하여 찾으려는 이름의 포인터를 찾는다
	imageMapIter mIter = mList.find(fName);

	//end()는 데이터 맨마지막의 다음을 가리키는 포인터이므로
	//만약 반복자가 맨끝까지 가지 않았다면
	//데이터를 찾았다는 뜻
	if (mIter != mList.end())
	{
		return mIter->second;//second는 value값
	}
	return NULL;
}

image * ImageManager::addImage(string strKey, int width, int height)
{
	//이미지를 먼저 찾는다
	image*img = findImage(strKey);

	//만약 img에 값이 있었다면 이미있기때문에 그냥 반환한다.
	if (img)return img;

	//만약 위에서 반환하고 함수가 종료되지 않았다면 객체화 시키고
	//초기화 과정이 필요하다
	img = new image;
	if (FAILED(img->init(width,height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//그리고 맵리스트에 초기화된 이미지를 삽입한다
	//pair로 쓸경우 pair<자료형,자료형>(변수,변수)
	//make_pair로 쓸경우 자료형 생략할수 있다
	mList.insert(make_pair(strKey, img));

	return img;
}

image * ImageManager::addImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약에 해당 이미지가 있다면 그 이미지 반환
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//insert 방식엔 크게 2가지가 있다
	//pair<자료형,자료형>(자료명,자료명) 자료형을 지정해서 넣어준다
	//make_pair(자료명,자료명)  알아서 형변환해서 넣어준다

	mList.insert(make_pair(strKey, img));

	return img;
}

image * ImageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약에 해당 이미지가 있다면 그 이미지 반환
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	mList.insert(make_pair(strKey, img));

	return img;
}

image * ImageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약에 해당 이미지가 있다면 그 이미지 반환
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	mList.insert(make_pair(strKey, img));

	return img;
}

image * ImageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약에 해당 이미지가 있다면 그 이미지 반환
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	mList.insert(make_pair(strKey, img));

	return img;
}


void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->Render(hdc,destX,destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);

	if (img) img->Render(hdc,	destX,destY, sourX,sourY, sourWidth, sourHeight);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY,currentFrameX,currentFrameY);
}

BOOL ImageManager::deleteImage(string strKey)
{
	//findImage를 사용하지 않는이유는 
	//반복자로 삭제데이터를 찾고 반복자를
	//맵리스트에서 지워주기 위함이다.
	imageMapIter key = mList.find(strKey);

	if (key != mList.end())
	{
		key->second->Release();
		SAFE_DELETE(key->second);
		mList.erase(key);

		return true;
	}
	return false;
}

BOOL ImageManager::deleteAll(void)
{
	//반복자를 맵의 맨앞을가리키게한다.
	imageMapIter mIter = mList.begin();

	//반복자가 맨마지막에 다음을 가리키기 전까지
	while (mIter != mList.end())
	{
		//벨류값에 데이터가 있다면
		if (mIter->second != NULL)
		{
			mIter->second->Release();
			SAFE_DELETE(mIter->second);
			//이터레이터 갱신은 촴 중요합니다
			//erase의 반환값은 현재 iter가 가리키는 다음포인터를 반환
			mIter = mList.erase(mIter);
		}
		else
			mIter++;//데이터 없으면 다음으로 넘겨준다
	}
	return true;
}
