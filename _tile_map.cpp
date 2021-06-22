#include "stdafx.h"
#include "_tile_map.h"


_tile_map::_tile_map()
{

}


_tile_map::~_tile_map()
{

}

HRESULT _tile_map::init(void)
{
	_image = IMAGEMANAGER->findImage("파판_1_중");
	_image2 = IMAGEMANAGER->addImage("인2뉴", "파판이미지/메뉴/인벤메뉴.bmp", 0, 0, 500*32, 500*32, true, RGB(255, 0, 255));
	_load = new Save_load;
	_load->init(true);
	load();
	_x = 0;
	_y = 0;
	draw();
	return S_OK;
}
void _tile_map::release(void)
{

}
void _tile_map::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += 10;
	}
}
void _tile_map::render(void)
{
	_image2->render(getMemDC(), 0,0, _x,_y,WINSIZEX-400,WINSIZEY);
}
void _tile_map::load(void)
{
	HANDLE file;
	DWORD read;
	char fileName[258];
	ZeroMemory(fileName, sizeof(fileName));
	strcpy(fileName, _load->mapTool_load("5"));
	file = CreateFile(fileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &TILEX, sizeof(int), &read, NULL);
	ReadFile(file, &TILEY, sizeof(int), &read, NULL);
	ReadFile(file, &TILEMAX, sizeof(int), &read, NULL);

	_tile = new tagtile[TILEMAX];

	for (int i = 0; i < TILEMAX; i++)
	{
		ReadFile(file, &_tile[i], sizeof(tagtile), &read, NULL);
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j <TILEX; j++)
		{
			_tile[i*TILEX + j].rc = RectMake(
				j*TILESIZE,
				i*TILESIZE,
				TILESIZE, TILESIZE);
		}
	}
	CloseHandle(file);
}
void _tile_map::draw(void)
{
	for (int i = 0; i < TILEMAX; i++)
	{
	 _image->frameRender(_image2->getMemDC(),
	 	_tile[i].rc.left, _tile[i].rc.top,
	 	_tile[i].tile_frameX, _tile[i].tile_frameY);
	}

	
}