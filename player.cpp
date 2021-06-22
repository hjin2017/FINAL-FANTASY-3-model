#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init(void)
{
	
	_pr = PR_DOWN;
	_fameY = 0;
	_count = _pcount=0;
	job(DATABASE->getElementData(_pcount)->job, _pcount + 1);
	_rc = RectMake((600 / 2) - _image->getFrameWidth() / 2, (600 / 2) - _image->getFrameHeight() / 2, _image->getFrameWidth(), _image->getFrameHeight());
	return S_OK;
}
void player::release(void)
{
}
void player::update(void) 
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_pr = PR_LEFT;
		move();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_pr = PR_RIGHT;
		move();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_pr = PR_UP;
		move();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_pr = PR_DOWN;
		move();
	}
	if (KEYMANAGER->isOnceKeyDown(' '))
	{
		_pcount++;
		if (_pcount == 4)
		{
			_pcount = 0;
		}
		job(DATABASE->getElementData(_pcount)->job, _pcount + 1);
	}	
}
void player::render(void) 
{
	_image->frameRender(getMemDC(), (600 / 2) - _image->getFrameWidth() / 2, (600 / 2) - _image->getFrameHeight() / 2, _pr, _fameY + _count / 15);

}
void player::move(void)
{
	_count++;
	if (_count == 30)
	{
		_count = 0;
	}
}
void player::job(string job, int num)
{
	char str[258];
	char temp[258];
	ZeroMemory(str, sizeof(str));
	strcpy(str, job.c_str());
	strcat(str, itoa(num, temp, 10));
  _image = IMAGEMANAGER->findImage(str);
	
}