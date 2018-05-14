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
	//�ݺ��ڸ� �̿��Ͽ� ã������ �̸��� �����͸� ã�´�
	imageMapIter mIter = mList.find(fName);

	//end()�� ������ �Ǹ������� ������ ����Ű�� �������̹Ƿ�
	//���� �ݺ��ڰ� �ǳ����� ���� �ʾҴٸ�
	//�����͸� ã�Ҵٴ� ��
	if (mIter != mList.end())
	{
		return mIter->second;//second�� value��
	}
	return NULL;
}

image * ImageManager::addImage(string strKey, int width, int height)
{
	//�̹����� ���� ã�´�
	image*img = findImage(strKey);

	//���� img�� ���� �־��ٸ� �̹��ֱ⶧���� �׳� ��ȯ�Ѵ�.
	if (img)return img;

	//���� ������ ��ȯ�ϰ� �Լ��� ������� �ʾҴٸ� ��üȭ ��Ű��
	//�ʱ�ȭ ������ �ʿ��ϴ�
	img = new image;
	if (FAILED(img->init(width,height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//�׸��� �ʸ���Ʈ�� �ʱ�ȭ�� �̹����� �����Ѵ�
	//pair�� ����� pair<�ڷ���,�ڷ���>(����,����)
	//make_pair�� ����� �ڷ��� �����Ҽ� �ִ�
	mList.insert(make_pair(strKey, img));

	return img;
}

image * ImageManager::addImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//���࿡ �ش� �̹����� �ִٸ� �� �̹��� ��ȯ
	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//insert ��Ŀ� ũ�� 2������ �ִ�
	//pair<�ڷ���,�ڷ���>(�ڷ��,�ڷ��) �ڷ����� �����ؼ� �־��ش�
	//make_pair(�ڷ��,�ڷ��)  �˾Ƽ� ����ȯ�ؼ� �־��ش�

	mList.insert(make_pair(strKey, img));

	return img;
}

image * ImageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//���࿡ �ش� �̹����� �ִٸ� �� �̹��� ��ȯ
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

	//���࿡ �ش� �̹����� �ִٸ� �� �̹��� ��ȯ
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

	//���࿡ �ش� �̹����� �ִٸ� �� �̹��� ��ȯ
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
	//findImage�� ������� �ʴ������� 
	//�ݺ��ڷ� ���������͸� ã�� �ݺ��ڸ�
	//�ʸ���Ʈ���� �����ֱ� �����̴�.
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
	//�ݺ��ڸ� ���� �Ǿ�������Ű���Ѵ�.
	imageMapIter mIter = mList.begin();

	//�ݺ��ڰ� �Ǹ������� ������ ����Ű�� ������
	while (mIter != mList.end())
	{
		//�������� �����Ͱ� �ִٸ�
		if (mIter->second != NULL)
		{
			mIter->second->Release();
			SAFE_DELETE(mIter->second);
			//���ͷ����� ������ �q �߿��մϴ�
			//erase�� ��ȯ���� ���� iter�� ����Ű�� ���������͸� ��ȯ
			mIter = mList.erase(mIter);
		}
		else
			mIter++;//������ ������ �������� �Ѱ��ش�
	}
	return true;
}
