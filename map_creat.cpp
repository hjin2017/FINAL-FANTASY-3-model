#include "stdafx.h"
#include "map_creat.h"


map_creat::map_creat()
{
}

map_creat::~map_creat()
{
}
HRESULT map_creat::init(void)
{
	_save = new Save_load;
	_save->init(true);

	_FileName+= _save->mapTool_load("0");
	TILEX = 100;
	TILEY = 100;
	TILEMAX = TILEX*TILEY;
	_x = _y = 0;
	_tile = new tagtile[TILEMAX];
	_image = IMAGEMANAGER->addImage("save_map", TILEX*TILESIZE_05, TILEY*TILESIZE_05);
	set_up_map();
	return S_OK;
}
void map_creat::release(void)
{
	_save->release();
	SAFE_DELETE(_save);
	SAFE_DELETE(_tile);
}
void map_creat::render(void)
{
	char str[234];
	_image->render(getMemDC(), 0, 0, _x, _y, WINSIZEX/2, WINSIZEY);
	for (int i = 0; i < TILEMAX; i++)
	{

		sprintf(str, "%d", _tile[i].battle_num);
		TextOut(getMemDC(), _tile[i].rc.left - _x, _tile[i].rc.top - _y, str, strlen(str));

		if (_tile[i].obj == OBJ_NORMAL)continue;
		IMAGEMANAGER->findImage("파판_1_소")->frameRender(getMemDC(),
			_tile[i].rc.left-_x, _tile[i].rc.top - _y,
			_tile[i].obj_frameX, _tile[i].obj_frameY);
	}

	sprintf(str,"%d", set_num(_FileName.c_str()));
	TextOut(getMemDC(), 50, 50, str, strlen(str));

}
void map_creat::set_up_map(void)
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tile[i*TILEX + j].rc = RectMake(
				j*TILESIZE_05,
				i*TILESIZE_05,
				TILESIZE_05, TILESIZE_05);
		}
	}
	
	for (int i = 0; i < TILEMAX; i++)
	{
		_tile[i].obj = OBJ_NORMAL;
		_tile[i].tile_frameX = 3;
		_tile[i].tile_frameY = 0;
		_tile[i].battle_num = 0;
		_tile[i].move = false;
	}
	
	for (int i = 0; i < TILEMAX; i++)
	{
		int x, y;
		y = i / TILEX;
		x = i - y*TILEX;
		if ((x == 8) || (x == TILEX - 9) || (y == 8) || (y == TILEY - 8))
		{
			_tile[i].obj = OBJ_NORMAL;
			_tile[i].tile_frameX = 0;
			_tile[i].tile_frameY = 0;
			_tile[i].obj_frameX = 0;
			_tile[i].obj_frameY = 0;
			_tile[i].move = true;
			_tile[i].battle_num = 0;
		}
	}
	
	for (int i = 0; i < TILEX*TILEY; i++)
	{
		IMAGEMANAGER->findImage("파판_1_소")->frameRender(_image->getMemDC(),
		_tile[i].rc.left, _tile[i].rc.top,
		_tile[i].tile_frameX, _tile[i].tile_frameY);
	}
}
void map_creat::set_tile(tagtile temp,int i)
{
	_tile[i].tile_frameX = temp.tile_frameX;
	_tile[i].tile_frameY = temp.tile_frameY;
	_tile[i].move = temp.move;
	_tile[i].battle_num = temp.battle_num;
	IMAGEMANAGER->findImage("파판_1_소")->frameRender(_image->getMemDC(),
		_tile[i].rc.left, _tile[i].rc.top,
		_tile[i].tile_frameX, _tile[i].tile_frameY);
}
void map_creat::save(char* num, char* str)
{
	_FileName.clear();
	_save->mapTool_save(num, str);

	_FileName+= _save->mapTool_load(num);
	
	HANDLE file;
	DWORD write;
	
	file = CreateFile(_FileName.c_str(), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, &TILEX, sizeof(int), &write, NULL);
	WriteFile(file, &TILEY, sizeof(int), &write, NULL);
	WriteFile(file, &TILEMAX, sizeof(int), &write, NULL);

	for (int i = 0; i < TILEMAX; i++)
	{
		WriteFile(file, &_tile[i], sizeof(tagtile), &write, NULL);
	}
	CloseHandle(file);
}
void map_creat::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(_FileName.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &TILEX, sizeof(int), &read, NULL);
	ReadFile(file, &TILEY, sizeof(int), &read, NULL);
	ReadFile(file, &TILEMAX, sizeof(int), &read, NULL);
	_tile = new tagtile[TILEMAX];

	for (int i = 0; i < TILEMAX; i++)
	{
		ReadFile(file, &_tile[i], sizeof(tagtile), &read, NULL);
	}

	CloseHandle(file);
}
void map_creat::changeName(int i)
{
	_FileName.clear();
	char temp[123];
	SAFE_DELETE(_tile);	
	Rectangle(_image->getMemDC(), 0, 0, TILEX*TILESIZE_05, TILEY*TILESIZE_05);	
	_FileName+= _save->mapTool_load(itoa(i, temp, 10));
	load();
	set_up_load_map();

}
void map_creat::set_up_load_map(void)
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tile[i*TILEX + j].rc = RectMake(
				j*TILESIZE_05,
				i*TILESIZE_05,
				TILESIZE_05, TILESIZE_05);
		}
	}
	for (int i = 0; i < TILEMAX; i++)
	{
		IMAGEMANAGER->findImage("파판_1_소")->frameRender(_image->getMemDC(),
			_tile[i].rc.left, _tile[i].rc.top,
			_tile[i].tile_frameX, _tile[i].tile_frameY);
	}
}

map_load::map_load()
{
}

map_load::~map_load()
{
}
HRESULT map_load::init(void)
{
	_x = _y = 0;
	_load = new Save_load;
	_load->init(true);
	_FileName+= _load->mapTool_load("1");
	load();
	_image_load = IMAGEMANAGER->addImage("load_map", TILEX*TILESIZE_05, TILEY*TILESIZE_05);

	set_up_map();

	return S_OK;
}
void map_load::release(void)
{
	_load->release();
	SAFE_DELETE(_load);
	SAFE_DELETE(_tile);
}
void map_load::render(void)	
{


	char str[123];
	_image_load->render(getMemDC(), WINSIZEX/2, 300, _x, _y, WINSIZEX, WINSIZEY);
	
	sprintf(str, "%d", set_num(_FileName.c_str()));
	TextOut(getMemDC(), 700, 320, str, strlen(str));

}
void map_load::set_up_map(void)				
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tile[i*TILEX + j].rc = RectMake(
				j*TILESIZE_05,
				i*TILESIZE_05,
				TILESIZE_05, TILESIZE_05);
		}
	}
	for (int i = 0; i < TILEMAX; i++)
	{
		IMAGEMANAGER->findImage("파판_1_소")->frameRender(_image_load->getMemDC(),
			_tile[i].rc.left, _tile[i].rc.top ,
			_tile[i].tile_frameX, _tile[i].tile_frameY);
	}
}

void map_load::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(_FileName.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &TILEX, sizeof(int), &read, NULL);
	ReadFile(file, &TILEY, sizeof(int), &read, NULL);
	ReadFile(file, &TILEMAX, sizeof(int), &read, NULL);
	_tile = new tagtile[TILEMAX];

	for (int i = 0; i < TILEMAX; i++)
	{
		ReadFile(file, &_tile[i], sizeof(tagtile), &read, NULL);
	}

	CloseHandle(file);
}
void map_load::changeName(int i)
{
	_FileName.clear();
	char temp[123];
	SAFE_DELETE(_tile);
	Rectangle(_image_load->getMemDC(), 0, 0, TILEX*TILESIZE_05, TILEY*TILESIZE_05);
	_FileName+= _load->mapTool_load(itoa(i, temp, 10));
	load();
	set_up_map();
}

tile_map::tile_map()
{
}

tile_map::~tile_map()
{
}
HRESULT tile_map::init(void)
{
	_x = _y = 0;
	_load = new Save_load;
	_load->init(true);
	char temp[123];
	_FileName+= _load->mapTool_load(itoa(DATABASE->get_map_num(), temp,10));
	load();
	_image_map = IMAGEMANAGER->addImage(_FileName, TILEX*TILESIZE, TILEY*TILESIZE);
	set_up_map();
	return S_OK;
}
void tile_map::release(void)
{
	_load->release();
	SAFE_DELETE(_tile);
	SAFE_DELETE(_load);
}

void tile_map::render(void)
{
	
	_image_map->render(getMemDC(), 0, 0, _x, _y, 600, WINSIZEY);
}
void tile_map::set_up_map(void)
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tile[i*TILEX + j].rc = RectMake(
				j*TILESIZE,
				i*TILESIZE,
				TILESIZE, TILESIZE);
		}
	}
	for (int i = 0; i < TILEMAX; i++)
	{
		IMAGEMANAGER->findImage("파판_1_중")->frameRender(_image_map->getMemDC(),
			_tile[i].rc.left, _tile[i].rc.top,
			_tile[i].tile_frameX, _tile[i].tile_frameY);
	}
}
void tile_map::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(_FileName.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &TILEX, sizeof(int), &read, NULL);
	ReadFile(file, &TILEY, sizeof(int), &read, NULL);
	ReadFile(file, &TILEMAX, sizeof(int), &read, NULL);
	_tile = new tagtile[TILEMAX];

	for (int i = 0; i < TILEMAX; i++)
	{
		ReadFile(file, &_tile[i], sizeof(tagtile), &read, NULL);
	}

	CloseHandle(file);
}