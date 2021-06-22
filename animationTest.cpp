#include "stdafx.h"
#include "animationTest.h"


animationTest::animationTest()
{
}


animationTest::~animationTest()
{
}

HRESULT animationTest::init()
{
	//낙타 이미지
	_camel = IMAGEMANAGER->addFrameImage("나윽타", "camel.bmp", 300, 267, 4, 3, true, RGB(255, 0, 255));

	//디폴트 애니메이션
	_ani1 = new animation;
	_ani1->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(), _camel->getFrameHeight());
	_ani1->setDefPlayFrame(false, true);
	_ani1->setFPS(1);

	//배열 애니메이션

	int arrAni[] = { 1, 3, 5, 7, 5, 2, 4, 6, 8 };
	_ani2 = new animation;
	_ani2->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(), _camel->getFrameHeight());
	_ani2->setPlayFrame(arrAni, 9, false);
	_ani2->setFPS(1);

	//구간 애니메이션
	_ani3 = new animation;
	_ani3->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(), _camel->getFrameHeight());
	_ani3->setPlayFrame(2, 6, true);
	_ani3->setFPS(1);

	return S_OK;
}

void animationTest::release()
{

}

void animationTest::update()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_ani1->start();
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_ani2->start();
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_ani3->start();
	}

	_ani1->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani3->frameUpdate(TIMEMANAGER->getElapsedTime() * 2);
}

void animationTest::render()
{
	_camel->aniRender(getMemDC(), 100, 200, _ani1);
	_camel->aniRender(getMemDC(), 200, 200, _ani2);
	_camel->aniRender(getMemDC(), 300, 200, _ani3);
}