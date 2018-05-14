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

	//맵을 담는 벡터의 처음부터 끝까지 탐색을 실시
	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter)
	{
		//맵의 반복자는 맵을 담는 벡터의 첫번째부터 끝까지 탐색을 실시
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//이펙트벡터의 반복자 설정
			iterEffects vArrIter;
			
			//이펙트벡터의 반복자는 맵의 세컨드값(이펙트객체)의 처음부터 끝까지 탐색을 실시
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
	image* img;					//이펙트이미지
	arrEffects vEffectBuffer;	//이펙트 클래스 담는 벡터
	arrEffect mArrEffect;		//이펙트 클래스에 키 값 붙인 맵

	//이미지 메니저에 이미지가 이미 있는 경우
	if (IMAGEMANAGER.findImage(imageName))
	{
		img = IMAGEMANAGER.findImage(imageName);
	}
	else // 없는경우는 추가해준다
	{
		img = IMAGEMANAGER.addImage(imageName, imageName, imageWidth, 
			imageHeight, true, RGB(255, 0, 255));
	}

	//버퍼 갯수만큼 이펙트벡터에 이펙트객체를 넣어준다.
	//(배열에 담겨서 서로다른 주소값에 객체들이 할당)
	for (int i = 0; i < buffer; ++i)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, effectWidth, effectHeight, fps, elapsedTime);
	}

	// 이펙트를 추가시킨 벡터를 키값을 부여하여 맵에 삽입
	mArrEffect.insert(pair<string, arrEffects>(effectName, vEffectBuffer));

	//마지막으로 맵을담는 벡터에 맵을 추가
	_vTotalEffect.push_back(mArrEffect);
}


void effectManager::play(string effectName, int x, int y)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//이펙트를 모두 넣어준 벡터를 검사
	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter)
	{
		//토탈 이펙트 벡터 안에 있는 맵의 이펙트 키 검사
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//이펙트 이름을 비교해서 같지 않으면 다음 맵으로 넘어감
			if (!(mIter->first == effectName)) break;

			//이펙트 키와 일치하면 이펙트를 실행시킨다
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				//이펙트 터트려줌
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->startEffect(x, y);
				return;
			}
		}
	}
}
