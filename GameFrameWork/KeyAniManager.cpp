#include "stdafx.h"
#include "KeyAniManager.h"
#include "animation.h"
#include "image.h"

KeyAniManager::KeyAniManager()
{
}


KeyAniManager::~KeyAniManager()
{
}

HRESULT KeyAniManager::init()
{
	return S_OK;
}

void KeyAniManager::release()
{
	deleteAll();
}

void KeyAniManager::update()
{
	animMapIter mIter = totalAnim.begin();

	for (;mIter != totalAnim.end(); mIter++)
	{
		if (!mIter->second->isPlay())
			continue;

		mIter->second->frameUpdate(TIMEMANAGER.getElapsedTime()*1.0f);
	}
}

void KeyAniManager::render()
{
}

void KeyAniManager::addDefaultFrameAnimation(string animationKeyName, char * imageKeyName, int fps, bool reverse, bool loop)
{
	image*img = IMAGEMANAGER.findImage(imageKeyName);
	animation*anim = new animation;

	anim->init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFreamHeight());
	anim->setDefPlayFrame(reverse, loop);
	anim->setFPS(fps);
	
	totalAnim.insert(pair<string, animation*>(animationKeyName, anim));
}

void KeyAniManager::addDefaultFrameAnimation(string animationKeyName, char * imageKeyName, int fps, bool reverse, 
											bool loop, void * cbFunction)
{
	image*img = IMAGEMANAGER.findImage(imageKeyName);
	animation*anim = new animation;

	anim->init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFreamHeight());
	anim->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	anim->setFPS(fps);

	totalAnim.insert(pair<string, animation*>(animationKeyName, anim));
}

void KeyAniManager::addDefaultFrameAnimation(string animationKeyName, char * imageKeyName, int fps, bool reverse, 
											bool loop, void * cbFunction, void * obj)
{
	image*img = IMAGEMANAGER.findImage(imageKeyName);
	animation*anim = new animation;

	anim->init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFreamHeight());
	anim->setDefPlayFrame(reverse, loop,CALLBACK_FUNCTION_PARAMETER(cbFunction),obj);
	anim->setFPS(fps);

	totalAnim.insert(pair<string, animation*>(animationKeyName, anim));
}

void KeyAniManager::addArrayFrameAnimation(string animationKeyName, char * imageKeyName, int * arr, int arrLen, 
											int fps, bool loop)
{
	image*img = IMAGEMANAGER.findImage(imageKeyName);
	animation*anim = new animation;

	anim->init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFreamHeight());
	anim->setPlayFrame(arr, arrLen, loop);
	anim->setFPS(fps);

	totalAnim.insert(pair<string, animation*>(animationKeyName, anim));
}

void KeyAniManager::addArrayFrameAnimation(string animationKeyName, char * imageKeyName, int * arr, int arrLen, 
											int fps, bool loop, void * cbFunction)
{
	image*img = IMAGEMANAGER.findImage(imageKeyName);
	animation*anim = new animation;

	anim->init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFreamHeight());
	anim->setPlayFrame(arr, arrLen, loop,CALLBACK_FUNCTION(cbFunction));
	anim->setFPS(fps);

	totalAnim.insert(pair<string, animation*>(animationKeyName, anim));
}

void KeyAniManager::addArrayFrameAnimation(string animationKeyName, char * imageKeyName, int * arr, int arrLen,
											int fps, bool loop, void * cbFunction, void * obj)
{
	image*img = IMAGEMANAGER.findImage(imageKeyName);
	animation*anim = new animation;

	anim->init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFreamHeight());
	anim->setPlayFrame(arr, arrLen, loop,CALLBACK_FUNCTION_PARAMETER(cbFunction),obj);
	anim->setFPS(fps);

	totalAnim.insert(pair<string, animation*>(animationKeyName, anim));
}

void KeyAniManager::addCoordinateFrameAnimation(string animationKeyName, char * imageKeyName, int start, int end, 
												int fps, bool reverse, bool loop)
{
	image*img = IMAGEMANAGER.findImage(imageKeyName);
	animation*anim = new animation;

	anim->init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFreamHeight());
	anim->setPlayFrame(start, end, reverse, loop);
	anim->setFPS(fps);

	totalAnim.insert(pair<string, animation*>(animationKeyName, anim));
}

void KeyAniManager::addCoordinateFrameAnimation(string animationKeyName, char * imageKeyName, int start, int end, 
												int fps, bool reverse, bool loop, void * cbFunction)
{
	image*img = IMAGEMANAGER.findImage(imageKeyName);
	animation*anim = new animation;

	anim->init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFreamHeight());
	anim->setPlayFrame(start, end, reverse, loop,(CALLBACK_FUNCTION)cbFunction);
	anim->setFPS(fps);

	totalAnim.insert(pair<string, animation*>(animationKeyName, anim));
}

void KeyAniManager::addCoordinateFrameAnimation(string animationKeyName, char * imageKeyName, int start, int end, 
												int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	image*img = IMAGEMANAGER.findImage(imageKeyName);
	animation*anim = new animation;

	anim->init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFreamHeight());
	anim->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction,obj);
	anim->setFPS(fps);

	totalAnim.insert(pair<string, animation*>(animationKeyName, anim));
}

void KeyAniManager::start(string animationKeyName)
{
	animMapIter iter = totalAnim.find(animationKeyName);
	iter->second->start();
}

void KeyAniManager::stop(string animationKeyName)
{
	animMapIter iter = totalAnim.find(animationKeyName);
	iter->second->stop();
}

void KeyAniManager::pause(string animationKeyName)
{
	animMapIter iter = totalAnim.find(animationKeyName);
	iter->second->pause();
}

void KeyAniManager::resume(string animationKeyName)
{
	animMapIter iter = totalAnim.find(animationKeyName);
	iter->second->resume();
}

animation * KeyAniManager::findAnimation(string animationKeyName)
{
	animMapIter mIter = totalAnim.find(animationKeyName);

	if (mIter != totalAnim.end())
		return mIter->second;

	return NULL;
}

void KeyAniManager::deleteAll()
{
	animMapIter mIter = totalAnim.begin();

	for (; mIter != totalAnim.end();)
	{
		if (mIter->second != NULL)
		{
			mIter->second->release();
			SAFE_DELETE(mIter->second);
			mIter = totalAnim.erase(mIter);
		}
		else
			mIter++;
	}
	totalAnim.clear();
}
