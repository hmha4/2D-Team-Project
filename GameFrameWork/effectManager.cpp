#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"

effectManager::effectManager()
{
}


effectManager::~effectManager()
{

}

HRESULT effectManager::init()
{

	return S_OK;
}

void effectManager::release()
{
	iterTotalEffect vIter;
	iterEffect mIter;

	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				iterEffects vArrIter = mIter->second.begin();
				for (; vArrIter != mIter->second.end();)
				{
					(*vArrIter)->release();
					delete *vArrIter;
					vArrIter = mIter->second.erase(vArrIter);
				}
			}
			else ++mIter;
		}
	}
}

void effectManager::update()
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//���� ��� ������ ó������ ������ Ž���� �ǽ�
	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter)
	{
		//���� �ݺ��ڴ� ���� ��� ������ ù��°���� ������ Ž���� �ǽ�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//����Ʈ������ �ݺ��� ����
			iterEffects vArrIter;
			
			//����Ʈ������ �ݺ��ڴ� ���� �����尪(����Ʈ��ü)�� ó������ ������ Ž���� �ǽ�
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update();
			}
		}
	}
}

void effectManager::render()
{
	iterTotalEffect vIter;
	iterEffect mIter;

	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render();
			}
		}
	}
}


void effectManager::addEffect(string effectName, const char* imageName, int imageWidth,
	int imageHeight, int effectWidth, int effectHeight, int fps, float elapsedTime, int buffer)
{
	image* img;					//����Ʈ�̹���
	arrEffects vEffectBuffer;	//����Ʈ Ŭ���� ��� ����
	arrEffect mArrEffect;		//����Ʈ Ŭ������ Ű �� ���� ��

	//�̹��� �޴����� �̹����� �̹� �ִ� ���
	if (IMAGEMANAGER.findImage(imageName))
	{
		img = IMAGEMANAGER.findImage(imageName);
	}
	else // ���°��� �߰����ش�
	{
		img = IMAGEMANAGER.addImage(imageName, imageName, imageWidth, 
			imageHeight, true, RGB(255, 0, 255));
	}

	//���� ������ŭ ����Ʈ���Ϳ� ����Ʈ��ü�� �־��ش�.
	//(�迭�� ��ܼ� ���δٸ� �ּҰ��� ��ü���� �Ҵ�)
	for (int i = 0; i < buffer; ++i)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps, elapsedTime);
	}

	// ����Ʈ�� �߰���Ų ���͸� Ű���� �ο��Ͽ� �ʿ� ����
	mArrEffect.insert(pair<string, arrEffects>(effectName, vEffectBuffer));

	//���������� ������� ���Ϳ� ���� �߰�
	_vTotalEffect.push_back(mArrEffect);
}


void effectManager::play(string effectName, int x, int y)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־��� ���͸� �˻�
	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter)
	{
		//��Ż ����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//����Ʈ �̸��� ���ؼ� ���� ������ ���� ������ �Ѿ
			if (!(mIter->first == effectName)) break;

			//����Ʈ Ű�� ��ġ�ϸ� ����Ʈ�� �����Ų��
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				//����Ʈ ��Ʈ����
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->startEffect(x, y);
				return;
			}
		}
	}
}
