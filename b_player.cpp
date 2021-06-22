#include "stdafx.h"
#include "b_player.h"


b_player::b_player()
{
}

b_player::~b_player()
{
}
HRESULT b_player::init(void)
{
	pl_init();

	return S_OK;
}
void b_player::release(void)
{
}
void b_player::update(void)
{
	for (int i = 0; i < 4; i++)
	{
		if (!_pl[i].life)
		{
			_pl[i].framex = 12;
			
		}
	}
}
void b_player::render(void)
{
	pl_state_draw();
}
void b_player::pl_init(void)
{
	char tmep[123];
	for (int i = 0; i < 4; i++)
	{
		_pl[i].imageName = DATABASE->getElementData(i)->job +"_"+ itoa(i + 1, tmep, 10);
		_pl[i].name = DATABASE->getElementData(i)->name;
		_pl[i].framex = 0;
		_pl[i].framey = 0;
		_pl[i].hpmax = set_st(DATABASE->getElementData(i)->power, DATABASE->getElementData(i)->dex, DATABASE->getElementData(i)->Int)*DATABASE->getElementData(i)->lv;
		_pl[i].hp = DATABASE->getElementData(i)->hp;
		_pl[i].att = DATABASE->getElementData(i)->att;
		_pl[i].def = DATABASE->getElementData(i)->def;
		_pl[i].num = i;
		_pl[i].turn = false;
		if(_pl[i].hp>0)_pl[i].life = true;
		else _pl[i].life = false;
		if (!DATABASE->getElementData(i)->pos)
		{
			_pl[i].x = 500;
			_pl[i].y = 70 * i + 120;
		}
		else
		{
			_pl[i].x = 550;
			_pl[i].y = 70 * i + 120;
		}
	}
}
void b_player::pl_state_draw(void)
{
	char temp[123];
	_txt.text_draw(400, 415, "HP", 18);
	_txt.text_draw(230, 415, "¿Ã∏ß", 18);
	for (int i = 0; i < 4; i++)
	{
		IMAGEMANAGER->findImage(_pl[i].imageName.c_str())->frameRender(getMemDC(), _pl[i].x, _pl[i].y, _pl[i].framex, _pl[i].framey);
		_txt.text_draw(230, 30 * i + 440, _pl[i].name, 18);
		_txt.text_draw(390, 30 * i + 440, itoa(_pl[i].hp, temp, 10), 18);
		_txt.text_draw(450, 30 * i + 440, "/", 18);
		if(!_pl[i].turn)
		{
			_txt.text_draw(480, 30 * i + 440, itoa(_pl[i].hpmax, temp, 10), 18);
		}
		else
		{
			_txt.text_draw(480, 30 * i + 440, _pl[i].str.c_str(), 18);
		}
	}
}
bool b_player::pl_turn_move(int i)
{
	bool is = true;
		if (_pl[i].turn&&turn_count == 3)
		{
			_pl[i].framex++;
			if (_pl[i].framex == 9)
			{
				_pl[i].framex = 0;
				_pl[i].turn = false;
				is = false;
			}
		}
	return is ;
}