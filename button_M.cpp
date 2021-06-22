#include "stdafx.h"
#include "button_M.h"


button_M::button_M()
{
}


button_M::~button_M()
{
}
HRESULT button_M::init(void)
{
	

	return S_OK;
}
void button_M::release(void)
{
	//_buV.clear();
}
void button_M::update(void)	
{
	for (_buVI = _buV.begin(); _buVI < _buV.end(); _buVI++)
	{
		(*_buVI)->update();
	}
}
void button_M::render(void)	
{
	for (_buVI = _buV.begin(); _buVI < _buV.end(); _buVI++)
	{
		(*_buVI)->render();
	}
}
void button_M::set_bu(const char* imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint,
	int num, const char* Name)
{
		button* s;
		s = new button;
		s->init(imageName,x,y, btnDownFramePoint, btnUpFramePoint, num, Name);
		_buV.push_back(s);
}