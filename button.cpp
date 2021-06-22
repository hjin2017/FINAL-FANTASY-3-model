#include "stdafx.h"
#include "button.h"


button::button()
{
}


button::~button()
{

}

HRESULT button::init(string imageName,int x,int y,int cx,int cy,string direction, int num)
{
	_imageName = imageName;
	_direction = direction;
	_x = x; _y=y;
	_num = num;
	_rc = RectMake(_x, _y, IMAGEMANAGER->findImage(_imageName.c_str())->getFrameWidth(), IMAGEMANAGER->findImage(_imageName.c_str())->getFrameHeight());
	_framey = _framex = 0;
	centerx = cx;
	centery = cy;
	_select = false;
	return S_OK;
}

void button::release()
{

}
void button::update()
{
	if (_select)
	{
		_framey = 1;
	}
	else
	{
		_framey = 0;
	}
}
void button::render()
{
	HFONT _hfont;
	HFONT _old;
	char str[126];
	int font=15;
	SetBkMode(getMemDC(), TRANSPARENT);
	_hfont = CreateFont(font, 0, 0, 0, 0, 0, false, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("±Ã¼­"));
	_old = (HFONT)SelectObject(getMemDC(), _hfont);

	IMAGEMANAGER->findImage(_imageName.c_str())->frameRender(getMemDC(), _x, _y, _framex, _framey);
	sprintf(str, _direction.c_str());
	TextOut(getMemDC(), _x+ centerx, _y+ centery, str, strlen(str));

	SelectObject(getMemDC(), _old);
	DeleteObject(_hfont);
}
