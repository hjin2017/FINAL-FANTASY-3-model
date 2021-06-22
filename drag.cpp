#include "stdafx.h"
#include "drag.h"


drag::drag()
{
}


drag::~drag()
{
}
HRESULT drag::init(void)
{
	return S_OK;
}
void drag::release(void)
{

}
void drag::update(void)
{
	if (!isdrag)
	{
		_x = _ptMouse.x;
		_y = _ptMouse.y;
    }

	setdrag();
}
void drag::render(void)
{
	if (isdrag)
	{
		//top
		LineMake(getMemDC(), drag_rc.left, drag_rc.top, drag_rc.right, drag_rc.top);
		//right
		LineMake(getMemDC(), drag_rc.right, drag_rc.top, drag_rc.right, drag_rc.bottom);
		//bottom
		LineMake(getMemDC(), drag_rc.left, drag_rc.bottom, drag_rc.right, drag_rc.bottom);
		//left
		LineMake(getMemDC(), drag_rc.left, drag_rc.top, drag_rc.left, drag_rc.bottom);
	
	//	Rectangle(getMemDC(), drag_rc.left, drag_rc.top, drag_rc.right, drag_rc.bottom);
	
	}
}
void drag::setdrag(void)
{
	if (isdrag)
	{
		if (_x < _ptMouse.x&&_y < _ptMouse.y)
		{
			drag_rc = RectMake(_x, _y, getDistance(_x, 0, _ptMouse.x, 0), getDistance(0, _y, 0, _ptMouse.y));
		}
		else if (_x > _ptMouse.x&&_y > _ptMouse.y)
		{
			drag_rc = RectMake(_ptMouse.x, _ptMouse.y, getDistance(_x, 0, _ptMouse.x, 0), getDistance(0, _y, 0, _ptMouse.y));
		}
		else if (_x > _ptMouse.x&&_y < _ptMouse.y)
		{
			drag_rc = RectMake(_ptMouse.x, _y, getDistance(_x, 0, _ptMouse.x, 0), getDistance(0, _y, 0, _ptMouse.y));
		}
		else if (_x < _ptMouse.x&&_y > _ptMouse.y)
		{
			drag_rc = RectMake(_x, _ptMouse.y, getDistance(_x, 0, _ptMouse.x, 0), getDistance(0, _y, 0, _ptMouse.y));
		}
	}
	else drag_rc = RectMake(0, 0, 0, 0);
		
}