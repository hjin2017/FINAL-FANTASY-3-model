#include "stdafx.h"
#include "character_hp_mp.h"


character_hp_mp::character_hp_mp()
{
}


character_hp_mp::~character_hp_mp()
{
}
HRESULT character_hp_mp::init(void)
{
	for (int i = 0; i < 4; i++)
	{
		_pl[i].hp = DATABASE->getElementData(i)->hp;
		_pl[i].lv= DATABASE->getElementData(i)->lv;
		_pl[i].name = DATABASE->getElementData(i)->name;
		_pl[i].image = IMAGEMANAGER->findImage(imageName(DATABASE->getElementData(i)->job, i+1, true));
		_pl[i].maxhp = set_st(DATABASE->getElementData(i)->power, DATABASE->getElementData(i)->dex, DATABASE->getElementData(i)->Int)*_pl[i].lv;
	}
	_image = IMAGEMANAGER->findImage("파판손_소");
	_pcount = 0;
	_select = false;
	return S_OK;
}
void character_hp_mp::release(void)
{

}
void character_hp_mp::update(void) 
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		switch (_pcount)
		{
		case 2:
			_pcount = 0;
			break;
		case 3:
			_pcount = 1;
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		switch (_pcount)
		{
		case 0:
			_pcount = 2;
			break;
		case 1:
			_pcount = 3;
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		switch (_pcount)
		{
		case 0:
			_pcount = 1;
			break;
		case 2:
			_pcount = 3;
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		switch (_pcount)
		{
		case 1:
			_pcount = 0;
			break;
		case 3:
			_pcount = 2;
			break;
		}
	}

	switch (_pcount)
	{
	case 0:
		_pointerX = _x+0;
		_pointerY = _y+10;
		break;
	case 1:
		_pointerX = _x + 250;
		_pointerY = _y + 10;
		break;
	case 2:
		_pointerX = _x + 0;
		_pointerY = _y + 80;
		break;
	case 3:
		_pointerX = _x + 250;
		_pointerY = _y + 80;
		break;
	}
}
void character_hp_mp::render(void) 
{
	char str[123];
	IMAGEMANAGER->findImage("캐릭창")->render(getMemDC(), _x, _y);
	int k = 0;
	int j = 0;
	for (int i = 0; i < 4; i++)
	{

		_pl[i].image->frameRender(getMemDC(), (_x+30) + (j%2 * 250), (_y+10) + (k * 70));

		sprintf(str, _pl[i].name.c_str());
		TextOut(getMemDC(), (_x + 80) + (j % 2 * 250), (_y + 10) + (k * 70), str, strlen(str));
		sprintf(str, "LV :%d", _pl[i].lv);
		TextOut(getMemDC(), (_x + 230) + (j % 2 * 250), (_y + 10) + (k * 70), str, strlen(str));

		sprintf(str, "HP :                     %d / %d", _pl[i].hp, _pl[i].maxhp);
		TextOut(getMemDC(), (_x + 80) + (j % 2 * 250), (_y + 40) + (k * 70), str, strlen(str));

		j++;
		if (j % 2 == 0)
		{
			k++;
		}
	}	
	if (_select)
	{
		_image->render(getMemDC(), _pointerX, _pointerY);
	}
}
void character_hp_mp::set_hp(int h)
{
	tagpl_hp temp;
	temp = _pl[_pcount];
	_pl[_pcount].hp += h;
	if (_pl[_pcount].hp > _pl[_pcount].maxhp)
	{
		_pl[_pcount].hp = _pl[_pcount].maxhp;
	}
	else
	{
		_pl[_pcount]= temp;
	}
}