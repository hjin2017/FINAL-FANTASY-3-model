#include "stdafx.h"
#include "inven_bag.h"


inven_bag::inven_bag()
{
}


inven_bag::~inven_bag()
{
}

HRESULT inven_bag::init(void)
{
	_text_box = new text_box;
	_text_box->init("도구","파판이미지/메뉴/말.bmp", 150, 50);
	_text_box->set_text_box_op(20, 0, 20, 10, "도    구", 30);
	_bag = new bag;
	_bag->init();
	_bag->set_xy(20, 40);
	_select = false;
	_hp = new character_hp_mp;
	_hp->init();
	_hp->set_x_y(20, 355);
	return S_OK;
}
void inven_bag::release(void)
{
	_bag->release();
	_hp->release();
	SAFE_DELETE(_text_box);
	SAFE_DELETE(_bag);
	SAFE_DELETE(_hp);
	
}
void inven_bag::update(void) 
{
	if (!_select)
	{
		_bag->update();
	}
	else
	{
		_hp->update();
	}
	
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		
		if (!_select)
		{
			_select = true;
			_hp->set_select(true);
		}
		else
		{
			_select = false;
			_hp->set_select(false);
			_bag->use_potion();
			_hp->set_hp(_bag->get_currentItem().hp);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_bag->save();
		for (int i = 0; i < 4; i++)
		{
			DATABASE->setElementDataCurrentHP(_hp->get_hp(i).hp, i);
		}
		SCENEMANAGER->changeScene("inven");
	}
}
void inven_bag::render(void) 
{
	_hp->render();
	_bag->render();
	_text_box->text_box_draw();
}