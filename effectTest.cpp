#include "stdafx.h"
#include "effectTest.h"


effectTest::effectTest()
{
}


effectTest::~effectTest()
{
}

HRESULT effectTest::init()
{
	IMAGEMANAGER->addImage("Æø¹ß", "explosion.bmp", 832, 62, true, RGB(255, 0, 255));


	_effect = new effect;
	_effect->init(IMAGEMANAGER->findImage("Æø¹ß"), 32, 62, 1, 1.0f);

	//ÀÌÆåÆ® ÀÌ¸§, ÀÌÆåÆ®ÀÌ¹ÌÁö ÀÌ¸§,ÀÌ¹ÌÁö °¡·Î, ¼¼·ÎÅ©±â, ÀÌÆåÆ® °¡·Î ¼¼·Î
	EFFECTMANAGER->addEffect("explosion", "explosion.bmp", 832, 62, 32, 62, 1, 1.0f, 100);

	_count = 0;



	return S_OK;
}

void effectTest::release()
{

}

void effectTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_effect->startEffect(_ptMouse.x, _ptMouse.y);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		EFFECTMANAGER->play("explosion", _ptMouse.x, _ptMouse.y);
	}

	_count++;

	if (_count % 5 == 0)
	{
		EFFECTMANAGER->play("explosion", RND->getFromIntTo(100, 200), RND->getFromIntTo(100, 200));

		_count = 0;
	}


	_effect->update();
	EFFECTMANAGER->update();
}

void effectTest::render()
{

	_effect->render();
	EFFECTMANAGER->render();
}
