#include "stdafx.h"
#include "zOrderManager.h"
#include "gameNode.h"

zOrderManager::zOrderManager()
{
}


zOrderManager::~zOrderManager()
{
}

void zOrderManager::init(bool _useShadowRc)
{
	useShadowRect = _useShadowRc;
}

void zOrderManager::InputObj(gameNode * obj)
{
	zVec.push_back(obj);
}

void zOrderManager::Render()
{
	for (int i = 0; i < zVec.size(); i++)
	{
		zVec[i]->Render();
	}
}

//이게 핵심인 함수 => gameNode에 getRc()함수를 사용하자
//gameNode*에 실제 객체화대상은 우리가 사용하는 객체들이므로 
//객체화되는 대상의 getRc()가 호출되야 한다=> 모든클래스가 구현해야함
void zOrderManager::Update()
{
	//업데이트에서 계속 비교연산해주면서 가려줄거니까!
	//버블솔트를 사용하자
	for (int i = 0; i < zVec.size(); i++)
	{
		for (int j = 0; j < zVec.size() - (i + 1); j++)
		{
			//중점의 Y 좌표가 작은쪽이 먼저랜더되야 하므로
			//저같은 경우 getRc()함수에서 플레이어의 렉트를 반환 받습니다
			//그림자를 따로두시는 분은 플레이어에서 그림자의 렉트를 
			//반환하시면 됩니다. 

			if (!useShadowRect)
				//==============중점의 Y좌표를 비교한 것===============//
			{
				if (GetCenterPos(zVec[j]->getRc()).y > GetCenterPos(zVec[j + 1]->getRc()).y)
				{
					gameNode*temp = zVec[j];
					zVec[j] = zVec[j + 1];
					zVec[j + 1] = temp;
				}
			}
			else
			{
				//===============그림자를 사용할시=====================//
				//그림자1의 바텀이 그림자2의 탑보다 작을경우
				if (zVec[j]->getRc().bottom > zVec[j + 1]->getRc().top)
				{
					gameNode*temp = zVec[j];
					zVec[j] = zVec[j + 1];
					zVec[j + 1] = temp;
				}
			}
		}
	}
}

void zOrderManager::Release()
{
	//여기선 벡터만 비워준다 객체는 다른쪽에서 메모리해제시켜주니까
	zVec.clear();
}


