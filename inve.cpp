#include "stdafx.h"
#include "inve.h"


inve::inve()
{
}


inve::~inve()
{
}
HRESULT inve::init(void)
{
	_image = IMAGEMANAGER->findImage("ÆÄÆÇ¼Õ_¼Ò");
	_count = 0;
	_pcount = 0;
	_text = new text_draw_c;
	set_character();
	_select = false;
	return S_OK;
}
void inve::release(void)
{
	SAFE_DELETE(_text);
}
void inve::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_select)
		{
			_pcount--;
			if (_pcount < 0)
			{
				_pcount = 3;
			}
		}
		else
		{
			_count--;
			if (_count < tool)
			{
				_count = save;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_select)
		{
			_pcount++;
			if (_pcount > 3)
			{
				_pcount = 0;
			}
		}
		else
		{
			_count++;
			if (_count > save)
			{
				_count = tool;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		set_select();
	}
	
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_select = false;
		_pcount = 0;
	}
	set_pointer();

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		SCENEMANAGER->changeScene("play");
	}
}
void inve::render(void)
{
	IMAGEMANAGER->findImage("½ºÅÝ¸Þ´º")->render(getMemDC(), 0, 0);

	for (int i = 0; i < end - 1; i++)
	{
		_text->text_draw(465, 40 + 42 * i, str_menu[i], 20);
	}
	_text->text_draw(212, 510, str_menu[gold], 20);

		_image->render(getMemDC(), 430, _y);
	
		if (_select)
		{
			_image->render(getMemDC(),20, _y2);
		}
	character_draw();

}
void inve::set_pointer(void)
{
	switch (_count)
	{
	case tool:
		_y = 40;
		break;
	case spell:
		_y = 40 + 42;
		break;
	case equipment:
		_y = 40 + 42 * 2;
		break;
	case state:
		_y = 40 + 42 * 3;
		break;
	case move:
		_y = 40 + 42 * 4;
		break;
	case job:
		_y = 40 + 42 * 5;
		break;
	case save:
		_y = 40 + 42 * 6;
		break;
	}
	switch (_pcount)
	{
	case 0:
		_y2 = 50;
		break;
	case 1:
		_y2 = 150;
		break;
	case 2:
		_y2 = 250;
		break;
	case 3:
		_y2 = 350;
		break;
	}
} 
void inve::set_character(void)
{
	for (int i = 0; i < 4; i++)
	{
		_p[i].move = DATABASE->getElementData(i)->pos;
		_p[i].hp = DATABASE->getElementData(i)->hp;
		_p[i].mp = DATABASE->getElementData(i)->mp;
		_p[i].name = DATABASE->getElementData(i)->name;
		_p[i].job = DATABASE->getElementData(i)->job;
		_p[i].maxhp = set_st(DATABASE->getElementData(i)->power, DATABASE->getElementData(i)->dex, DATABASE->getElementData(i)->Int)*DATABASE->getElementData(i)->lv;
		_p[i].maxmp = set_st(DATABASE->getElementData(i)->wis, DATABASE->getElementData(i)->Int, DATABASE->getElementData(i)->dex)*DATABASE->getElementData(i)->lv;
		_p[i].image = IMAGEMANAGER->findImage(imageName(_p[i].job, i + 1,true).c_str());
	}
	_glod = DATABASE->get_gold();
}
void inve::character_draw(void)
{
	char str[123];
	sprintf(str, "%d", _glod);
	TextOut(getMemDC(), 330, 510, str, strlen(str));
	for (int i = 0; i < 4; i++)
	{
		sprintf(str, _p[i].name.c_str());
		TextOut(getMemDC(), 150, 50 + 100 * i, str, strlen(str));

		sprintf(str, _p[i].job.c_str());
		TextOut(getMemDC(), 250, 50 + 100 * i, str, strlen(str));

		sprintf(str, "HP :          %d   /   %d", _p[i].hp, _p[i].maxhp);
		TextOut(getMemDC(), 150, 70 + 100 * i, str, strlen(str));

		sprintf(str, "MP :          %d   /   %d", _p[i].mp, _p[i].maxmp);
		TextOut(getMemDC(), 150, 90 + 100 * i, str, strlen(str));

		if (_p[i].move)
		{
			_p[i].image->frameRender(getMemDC(), 100, 50 + 100 * i, 0, 0);
		}
		else
		{
			_p[i].image->frameRender(getMemDC(), 50, 50 + 100 * i, 0, 0);
		}
	}

}
void inve::set_select(void)
{
	if (!_select)
	{
		switch (_count)
		{
		case tool:
			SCENEMANAGER->changeScene("inven_bag");
			break;
		case save:
			//Ã¾Áö¾À
			break;
		default:
			_select = true;
			break;
		}
	}
	else
	{
		switch (_count)
		{
		case move:
			if (!_p[_pcount].move)
			{
				_p[_pcount].move = true;
				DATABASE->setElementDataCurrent_pos(true, _pcount);
			}
			else
			{
				_p[_pcount].move = false;
				DATABASE->setElementDataCurrent_pos(false, _pcount);
			}
			break;
		case spell:
			//Ã¾
			break;
		case equipment:
			DATABASE->set_player(_pcount);
			SCENEMANAGER->changeScene("inven_equipment");
			break;
		case state:
			DATABASE->set_player(_pcount);
			SCENEMANAGER->changeScene("inven_state");
			break;
		case job:
			DATABASE->set_player(_pcount);
			SCENEMANAGER->changeScene("inven_job");
			break;

		}
	}
}
