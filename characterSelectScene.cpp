#include "stdafx.h"
#include "characterSelectScene.h"


characterSelectScene::characterSelectScene()
{
}


characterSelectScene::~characterSelectScene()
{

}

HRESULT characterSelectScene::init(void)
{

	return S_OK;
}

void characterSelectScene::release(void)
{

}

void characterSelectScene::update(void)	
{

}

void characterSelectScene::render(void)	
{
	IMAGEMANAGER->findImage("오버워치캐릭터선택")->render(getMemDC(), 0, 0);
}
