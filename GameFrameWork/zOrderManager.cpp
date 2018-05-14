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

//�̰� �ٽ��� �Լ� => gameNode�� getRc()�Լ��� �������
//gameNode*�� ���� ��üȭ����� �츮�� ����ϴ� ��ü���̹Ƿ� 
//��üȭ�Ǵ� ����� getRc()�� ȣ��Ǿ� �Ѵ�=> ���Ŭ������ �����ؾ���
void zOrderManager::Update()
{
	//������Ʈ���� ��� �񱳿������ָ鼭 �����ٰŴϱ�!
	//�����Ʈ�� �������
	for (int i = 0; i < zVec.size(); i++)
	{
		for (int j = 0; j < zVec.size() - (i + 1); j++)
		{
			//������ Y ��ǥ�� �������� ���������Ǿ� �ϹǷ�
			//������ ��� getRc()�Լ����� �÷��̾��� ��Ʈ�� ��ȯ �޽��ϴ�
			//�׸��ڸ� ���ενô� ���� �÷��̾�� �׸����� ��Ʈ�� 
			//��ȯ�Ͻø� �˴ϴ�. 

			if (!useShadowRect)
				//==============������ Y��ǥ�� ���� ��===============//
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
				//===============�׸��ڸ� ����ҽ�=====================//
				//�׸���1�� ������ �׸���2�� ž���� �������
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
	//���⼱ ���͸� ����ش� ��ü�� �ٸ��ʿ��� �޸����������ִϱ�
	zVec.clear();
}


