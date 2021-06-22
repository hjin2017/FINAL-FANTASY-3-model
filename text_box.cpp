#include "stdafx.h"
#include "text_box.h"


text_box::text_box()
{
}


text_box::~text_box()
{
}
//말 풍선
 HRESULT text_box::init(string str ,string fileName, int w, int h)
{
	 _k = str;
	IMAGEMANAGER->addImage(_k.c_str(), fileName.c_str(), w, h, true, RGB(255, 0, 255));
	return S_OK;
}
 void text_box::render(void)
 {
	 text_box_draw();
 }
 void text_box::set_text_box_op(int x, int y, int tx, int ty, string s, int fontsize)
 {
	 _x = x; _y = y; _tx = tx; _ty = ty; _s = s; _fontsize = fontsize;
 }
 void text_box::text_box_draw(void)
{
	
	IMAGEMANAGER->findImage(_k.c_str())->render(getMemDC(), _x, _y);

	HFONT _hfont;
	HFONT _old;

	char str[126];
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	_hfont = CreateFont(_fontsize, 0, 0, 0, 0, 0, false, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
	_old = (HFONT)SelectObject(getMemDC(), _hfont);

	sprintf(str, _s.c_str());
	TextOut(getMemDC(), _x + _tx, _y+ _ty, str, strlen(str));

	SelectObject(getMemDC(), _old);
	DeleteObject(_hfont);
}

HRESULT text_box_M::init()
{
	return S_OK;
}
void text_box_M::release(void)
{

}
void text_box_M::render(void)
{
	for (int i = 0; i < _vb.size(); i++)
	{
		_vb[i]->render();
	}
}
void text_box_M::set_text_box(string key,int w, int h, int x, int y, int tx, int ty, string s, int fontsize)
{
	text_box* t;
	t = new text_box;
	t->init(key,"파판이미지/메뉴/말.bmp", w, h);
	t->set_text_box_op(x, y, tx, ty, s, fontsize);
	_vb.push_back(t);
}
void text_box_M::removeall(void)
{
	int x = _vb.size();
	for (int i = 0; i < x; i++)
	{
		SAFE_DELETE(_vb[i]);
		SAFE_RELEASE(_vb[i]);
	}
	for (int i = 0; i < x; i++)
	{
		_vib = _vb.begin();
		_vb.erase(_vib);
	}
	_vb.clear();
}
text_box_M::text_box_M()
{
}

text_box_M::~text_box_M()
{
}

//배경없는 말
text_draw_c::text_draw_c()
{
}

text_draw_c::~text_draw_c()
{
}
void text_draw_c::text_draw(int x, int y, string s, int fontsize)
{
	HFONT _hfont;
	HFONT _old;

	char str[126];
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	_hfont = CreateFont(fontsize, 0, 0, 0, 0, 0, false, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
	_old = (HFONT)SelectObject(getMemDC(), _hfont);

	sprintf(str, s.c_str());
	TextOut(getMemDC(), x  ,y , str, strlen(str));

	SelectObject(getMemDC(), _old);
	DeleteObject(_hfont);
}
void text_draw_c::text_draw_int(int x, int y, string s, int num, int fontsize)
{
	HFONT _hfont;
	HFONT _old;
	string st = s;
	char str[126];
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	_hfont = CreateFont(fontsize, 0, 0, 0, 0, 0, false, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
	_old = (HFONT)SelectObject(getMemDC(), _hfont);
	st += "%d";
	sprintf(str, st.c_str(),num);
	TextOut(getMemDC(), x, y, str, strlen(str));

	SelectObject(getMemDC(), _old);
	DeleteObject(_hfont);
}

