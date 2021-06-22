#include "stdafx.h"
#include "map_tool.h"


map_tool::map_tool()
{
}


map_tool::~map_tool()
{
}
HRESULT map_tool::init(void)
{
	SetWindowPos(_hWnd, NULL, 0, 0, WINSIZEX, WINSIZEY, SWP_NOMOVE);
	////스테이지///////////////////////////////////////////////////////////////////////////////////////////
	_save_load = new Save_load;
	_save_load->init(true);
	strcpy(FileName, _save_load->mapTool_load("1"));
	//배경///////////////////////////////////////////////////////////////////////////////////////////////////////
	

//타일셋////////////////////////////////////////////////////////////////////////////////////////////////////
	
		TILEX = 100;
		TILEY = 100;
		TILEMAX = TILEX*TILEY;
		_image = IMAGEMANAGER->addImage("map", TILEX*32, TILEY*32);
		_x = _y = 0;
		_tile = new tagtile[TILEMAX];
		setup();
//마우스 드레그//////////////////////////////////////////////////////////////////////////////////////////////
		_dragstart = false;
		_drag = new drag;
		_drag->init();
		_drag->_isdrag(_dragstart);
		_mouse_num = 0;
		y = 0;
		x = y;
		_current_drag = new tagtile[x*y];
//버튼셋/////////////////////////////////////////////////////////////////////////////////////////////////////
	_button = new button_M;
	_button->init();
	_button->set_bu("에메랄드", 675, 25, PointMake(0, 1), PointMake(0, 0), button_save,"save");
	_button->set_bu("블랙", 675, 75, PointMake(0, 1), PointMake(0, 0), button_load,"load");
	_button->set_bu("레드", 675, 125, PointMake(0, 1), PointMake(0, 0), button_ERASER,"eraser");
	_button->set_bu("베이지", 675, 175, PointMake(0, 1), PointMake(0, 0), button_WALL,"wall");
	_button->set_bu("화이트", 675, 225, PointMake(0, 1), PointMake(0, 0), button_GROUND,"ground");
	_button->set_bu("체리", 675, 275, PointMake(0, 1), PointMake(0, 0), button_OBJ,"obj");
	_button->set_bu("체리", 675, 325, PointMake(0, 1), PointMake(0, 0), button_battle, "battleNum");
	_select_num = button_GROUND;
//자판 셋/////////////////////////////////////////////////////////////////////////////////////////////////////
	_TEXTstart = false;
	a = new char[256];
	strcpy(a, textchar);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return S_OK;
}
void map_tool::release(void)
{
	SAFE_DELETE(_tile);
	SAFE_DELETE(_button);
	SAFE_DELETE(_drag);
	SAFE_DELETE(_current_drag);
	SAFE_DELETE(_save_load);
}
void map_tool::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('S')&&!_TEXTstart)
	{
		SCENEMANAGER->changeScene("메뉴");
		if (_tile == NULL)return;
	}
//////////////////////////마우스//////////////////////////////////////////////////////////////////////////////////
	switch (_mouse_num)
	{
	case mouse_01:
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			setmap();
			set_button();
		}
		_button->update();
		break;
	case mouse_02:
		_button->update();//건물 용 임 추가해야됨
		for (int i = 0; i < SAMPLETILEY*SAMPLETILEX; i++)
		{
			if (PtInRect(&_sample[i].rc, _ptMouse))
			{
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
				{
					_dragstart = true;
					_drag->update();
					
				}
				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
				{
					_dragstart = false;
					set_drag_samplemap();
				}
			}
			else set_button();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			setmap_drag();
		}
		_drag->_isdrag(_dragstart);
		if (_current_drag!=NULL)
		{
			for (int i = 0; i < y; i++)
			{
				for (int j = 0; j < x; j++)
				{
					_current_drag[i*x + j].rc = RectMake(
						j*TILESIZE_05 + _ptMouse.x,
						i*TILESIZE_05 + _ptMouse.y,
						TILESIZE_05, TILESIZE_05);
				}
			}
		}
		break;
	case mouse_03:
		_button->update();
		RECT rc = RectMake(0, 0, 600, WINSIZEY);
		if (PtInRect(&rc, _ptMouse))
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_dragstart = true;
				_drag->update();
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				_dragstart = false;
				set_drag_map();
			}
		}
		else
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				set_button();
			}
		}
		_drag->_isdrag(_dragstart);
		break;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_mouse_num += 1;
		if (_mouse_num > 2)
		{
			_mouse_num = 0;
		}
		if (_mouse_num == 2)
		{
			SAFE_DELETE(_current_drag);
			_current_drag = new tagtile[0];
			x = y = 0;
		}
	}
//텍스트 엔터////////////////////////////////////////////////////////////////////////////////////
	{
		strcpy(a, textchar);
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _TEXTstart)
		{
			switch (_select_num)
			{
			case button_save:
			{
				//초기화//쓰레기값이 같이들어가서 정리
				int nu;
				strcpy(a, textchar);
				nu = atoi(a);
				strcpy(a,itoa( nu,a,10));
				//정리
				char str[258];
				ZeroMemory(str, sizeof(str));
				strcat(str, "파판맵/mapSave");
				strcat(str, a);
				strcat(str, ".map");
				//리셋
				textchar[0] = '\0';
				_save_load->mapTool_save(a, str);//텍스트 저장
				_TEXTstart = false;
				_select_num = button_GROUND;
				strcpy(FileName, _save_load->mapTool_load(a));//텍스트에서 정보 얻어 
				save();//맵에 세이브
				//전체맵 초기화
				SCENEMANAGER->changeScene("메뉴");
				if (_tile == NULL)return;
			}
			break;
			case button_load:
			{
				strcpy(a, textchar);
				textchar[0] = '\0';
				_TEXTstart = false;
				int nu = atoi(a);
				strcpy(a, itoa(nu, a, 10));
				strcpy(FileName, _save_load->mapTool_load(a));
				load();
				_select_num = button_GROUND;
			}
			break;
			case button_battle:
				strcpy(a, textchar);
				_current.battle_num = atoi(a);
				textchar[0] = '\0';
				_TEXTstart = false;
				_select_num = button_GROUND;
			break;
			}
		}
		////별개////////////////////////
		switch (_select_num)
		{
		case button_save:
			_TEXTstart = true;
			_current.move = true;
			_current.obj = OBJ_NORMAL;
		break;
		case button_load:
			_TEXTstart = true;
			_current.move = true;
			_current.obj = OBJ_NORMAL;
		break;
		case button_battle:
			_TEXTstart = true;
			_current.move = true;
			_current.obj = OBJ_NORMAL;
		break;
		}
	}
//세이브 로드/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	camera();
}
/////////////////랜더///////////////////////////////////////////////////////////////////////////////////////
void map_tool::render(void)
{
	char str[128];

	IMAGEMANAGER->findImage("파판_1_소")->render(getMemDC(), WINSIZEX- _image->getWidth()-16,0 );

//타일 맵////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	_image->render(getMemDC(), 0, 0, _x, _y, WINSIZEX-600, WINSIZEY);
//텍스트/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	switch (_select_num)
	{
		if (!_TEXTstart)break;
	case button_save:
			Rectangle(getMemDC(), 740, 10, 810, 40);
			sprintf(str, "넘버 :");
			TextOut(getMemDC(), 740 + 5, 10 + 5, str, strlen(str));
			sprintf(str, a);
			TextOut(getMemDC(), 740 + 50, 10 + 5, str, strlen(str));
	break;
	case button_load:
		Rectangle(getMemDC(), 740, 60, 810, 90);
		sprintf(str, "넘버 :");
		TextOut(getMemDC(), 740 + 5, 60 + 5, str, strlen(str));
		sprintf(str, a);
		TextOut(getMemDC(), 740 + 50, 60 + 5, str, strlen(str));
	break;
	case button_battle:
		Rectangle(getMemDC(), 740, 310, 760, 340);
		sprintf(str, a);
		TextOut(getMemDC(), 740 + 5, 310 + 5, str, strlen(str));
	break;
	}
////확인용//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		//for (int i = 0; i < SAMPLETILEY*SAMPLETILEX; i++)
		//{
		//	Rectangle(getMemDC(), _sample[i].rc.left, _sample[i].rc.top, _sample[i].rc.right, _sample[i].rc.bottom);
		//	sprintf(str, "%d", _sample[i].tile_frameY);
		//	TextOut(getMemDC(), _sample[i].rc.left + _x, _sample[i].rc.top + _y, str, strlen(str));
		//}
	    for (int i = 0; i < TILEMAX; i++)
		{
			//Rectangle(getMemDC(), _tile[i].rc.left, _tile[i].rc.top, _tile[i].rc.right, _tile[i].rc.bottom);
			if (_tile[i].battle_num == 0)continue;
			sprintf(str, "%d",_tile[i].battle_num);
			TextOut(getMemDC(), _tile[i].rc.left, _tile[i].rc.top , str, strlen(str));
		}
	}

//드레그 이미지/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!_dragstart&&_mouse_num == mouse_02)
	{
		for (int i = 0; i < x*y; i++)
		{
			//Rectangle(getMemDC(), _current_drag[i].rc.left, _current_drag[i].rc.top, _current_drag[i].rc.right, _current_drag[i].rc.bottom);
			_image->frameRender(getMemDC(),
				_current_drag[i].rc.left, _current_drag[i].rc.top,
				_current_drag[i].tile_frameX, _current_drag[i].tile_frameY);
		}
	}
	else
	{
		SAFE_DELETE(_current_drag);
	}
	sprintf(str, FileName);
	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y-15, str, strlen(str));
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (_mouse_num == mouse_02|| _mouse_num == mouse_03)
	{
		_drag->render();
	}
	setView();
	_button->render();
////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void map_tool::setup(void)
{
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sample[i * SAMPLETILEX + j].tile_frameX = j;
			_sample[i * SAMPLETILEX + j].tile_frameY = i;
			_sample[i*SAMPLETILEX + j].rc = RectMake(
				j*TILESIZE_05 + WINSIZEX-16 - _image->getWidth(),
				i*TILESIZE_05,
				TILESIZE_05, TILESIZE_05);
		}
	}
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
		_tile[i].tile_frameY = 2;
		_tile[i].obj_frameX = 0;
		_tile[i].obj_frameY = 0;
		_tile[i].big = false;
		_tile[i].map_move = false;
		_tile[i].move = true;
		_tile[i].map_x = 0;
		_tile[i].map_y = 0;
		_tile[i].map_num = 0;
		_tile[i].battle_num = 0;
	}
	for (int i = 0; i < TILEMAX; i++)
	{
		int x, y;
		y = i / TILEX;
		x = i - y*TILEX;
		if ((x == 8)|| (x == TILEX - 9)||(y==8)||(y== TILEY-8))
		{
			_tile[i].obj = OBJ_NORMAL;
			_tile[i].tile_frameX = 0;
			_tile[i].tile_frameY = 0;
			_tile[i].obj_frameX = 0;
			_tile[i].obj_frameY = 0;
			_tile[i].big = false;
			_tile[i].map_move = false;
			_tile[i].move = false;
			_tile[i].map_x = 0;
			_tile[i].map_y = 0;
			_tile[i].map_num = 0;
			_tile[i].battle_num = 0;
		}

	}
	_current.obj = OBJ_NORMAL;
	_current.tile_frameX = 0;
	_current.tile_frameY = 0;
	_current.obj_frameX = 0;
	_current.obj_frameY = 0;
	_current.big = false;
	_current.map_move = false;
	_current.move = true;
	_current.map_x = 0;
	_current.map_y = 0;
	_current.map_num = 0;
	_current.battle_num = 0;

	for (int i = 0; i < TILEMAX; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &RectMake(-_x, -_y, 600, WINSIZEY), &_tile[i].rc))
		{
			IMAGEMANAGER->findImage("파판_1_소")->frameRender(_image->getMemDC(),
				_tile[i].rc.left + _x, _tile[i].rc.top + _y,
				_tile[i].tile_frameX, _tile[i].tile_frameY);
		}
	}
	for (int i = 0; i < TILEMAX; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &RectMake(-_x, -_y, 600, WINSIZEY), &_tile[i].rc))
		{
			if (_tile[i].obj == OBJ_NORMAL)continue;
			IMAGEMANAGER->findImage("파판_1_소")->frameRender(_image->getMemDC(),
				_tile[i].rc.left + _x, _tile[i].rc.top + _y,
				_tile[i].obj_frameX, _tile[i].obj_frameY);
		}
	}


}
void map_tool::setmap(void)
{
	for (int i = 0; i < TILEX*TILEY; i++)
	{
		RECT rc = RectMake(0, 0, 600, WINSIZEY);
		if ((!PtInRect(&rc, _ptMouse)))continue;
		if (!PtInRect(&_tile[i].rc, _ptMouse))continue;
		switch (_select_num)
		{
		case button_GROUND:
			_tile[i].tile_frameX = _current.tile_frameX;
			_tile[i].tile_frameY = _current.tile_frameY;
			_tile[i].move = _current.move;
			_tile[i].obj = _current.obj;
			_tile[i].battle_num = _current.battle_num;
			break;
		case button_WALL:
			_tile[i].tile_frameX = _current.tile_frameX;
			_tile[i].tile_frameY = _current.tile_frameY;
			_tile[i].move = _current.move;
			_tile[i].obj = _current.obj;
			break;
		case button_OBJ:
			_tile[i].obj_frameX = _current.tile_frameX;
			_tile[i].obj_frameY = _current.tile_frameY;
			_tile[i].move = _current.move;
			_tile[i].obj = _current.obj;
			break;
		}
	}
}
void map_tool::set_button(void)
{
	for (int i = 0; i < SAMPLETILEY*SAMPLETILEX; i++)
	{
		if (PtInRect(&_sample[i].rc, _ptMouse))
		{
			_current.tile_frameX = _sample[i].tile_frameX;
			_current.tile_frameY = _sample[i].tile_frameY;
		}
	}
	for (int i = 0; i < _button->get_buV().size(); i++)
	{
		if (!_button->get_buV()[i]->select())continue;
		_select_num = _button->get_buV()[i]->button_num();
	}
	switch (_select_num)
	{
	case button_GROUND:
		_current.move = true;
		_current.obj = OBJ_NORMAL;
		break;
	case button_OBJ:
		_current.move = false;
		_current.obj = set_obj(_current.tile_frameX, _current.tile_frameY);
		break;
	case button_WALL:
		_current.move = false;
		_current.obj = OBJ_NORMAL;
		_current.battle_num = 0;
		break;
	}
}
void map_tool::save(void)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(FileName, GENERIC_WRITE, 0, NULL,
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
void map_tool::load(void)
{
	HANDLE file;
	DWORD read;

		file = CreateFile(FileName, GENERIC_READ, 0, NULL,
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
					j*TILESIZE_05,
					i*TILESIZE_05,
					TILESIZE_05, TILESIZE_05);
			}
		}
	CloseHandle(file);
}
void map_tool::camera(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 10;
	}
}
tileobj map_tool::set_obj(int x, int y)
{
	if (x == 12 && y == 0)
	{
		return OBJ_PLAYER;
	}
	else if (x == 14 && y == 1)
	{
		return OBJ_STONE_01;
	}
	else if (x == 13 && y == 0)
	{
		return OBJ_TUNNEL;
	}
	else return OBJ_NORMAL;
}
void map_tool::setView(void)
{
	char str[258];

	switch (_select_num)
	{
	case button_save:
		sprintf(str, FileName);
		TextOut(getMemDC(), 625, 425, str, strlen(str));
		break;
	case button_GROUND:	case button_WALL:case button_OBJ:case button_battle:
		sprintf(str, "오브젝트 %d", _current.obj);
		TextOut(getMemDC(), 625, 375, str, strlen(str));
		sprintf(str, "프레임xy %d. %d", _current.tile_frameX, _current.tile_frameY);
		TextOut(getMemDC(), 625, 425, str, strlen(str));
		sprintf(str, "크기 %d", _current.big);
		TextOut(getMemDC(), 625, 475, str, strlen(str));
		sprintf(str, "맵 이동 %d", _current.map_move);
		TextOut(getMemDC(), 625, 525, str, strlen(str));
		sprintf(str, "맵 이동 %d. %d", _current.map_x, _current.map_y);
		TextOut(getMemDC(), 625, 575, str, strlen(str));
		sprintf(str, "현제 맵 %d", _current.map_num);
		TextOut(getMemDC(), 625, 625, str, strlen(str));
		sprintf(str, "전투 지형 %d", _current.battle_num);
		TextOut(getMemDC(), 625, 675, str, strlen(str));
		break;
	}
	
}
void map_tool::set_drag_samplemap()
{	
	int __x=_ptMouse.x;
	int __y= _ptMouse.y;
	
	RECT start;
	int sint;
	RECT end;
	bool sd=false;
	
	//샘플타일 읽기 여기서 바꿔야 건물 읽음
			for (int i = 0; i < SAMPLETILEY*SAMPLETILEX; i++)
			{
				if (PtInRect(&_sample[i].rc, PointMake(_drag->get_x(), _drag->get_y())))
				{
					start = _sample[i].rc;
					sint = i;
					sd = true;
				}
				
				if (PtInRect(&_sample[i].rc, PointMake(__x, __y))&&sd)
				{
					end = _sample[i].rc;
					sd = true;
				}
				
			}
			if (sd)
			{
				x = getDistance(start.left, start.top, end.right, start.top) / 16;
				y = getDistance(start.left, start.top, start.left, end.bottom) / 16;
	
				_current_drag = new tagtile[x*y];
	
				
				int j = 0;
				int k = 0;
				for (int i = 0; i < y*x; i++)
				{
	
					_current_drag[i].tile_frameX = _sample[sint + j + k].tile_frameX;
					_current_drag[i].tile_frameY = _sample[sint + j + k].tile_frameY;
					j++;
					if (j > x - 1)
					{
						j = 0;
						k += SAMPLETILEX;
					}
				}

			}
			else _current_drag = new tagtile[0];

}
void map_tool::set_drag_map(void)
{
	//타일에 그리기
	for (int i = 0; i < TILEX*TILEY; i++)
	{
		RECT rc = RectMake(0, 0, 600, WINSIZEY);
		if ((!PtInRect(&rc, _ptMouse)))
		{
			_drag->set_rcright(rc);
		}
		RECT rc2;
		if (!IntersectRect(&rc2, &_tile[i].rc, &_drag->get_rc()))continue;
		switch (_select_num)
		{
		case button_GROUND:
			_tile[i].tile_frameX = _current.tile_frameX;
			_tile[i].tile_frameY = _current.tile_frameY;
			_tile[i].move = _current.move;
			_tile[i].obj = _current.obj;
			_tile[i].battle_num = _current.battle_num;

			break;
		case button_WALL:
			_tile[i].tile_frameX = _current.tile_frameX;
			_tile[i].tile_frameY = _current.tile_frameY;
			_tile[i].move = _current.move;
			_tile[i].obj = _current.obj;

			break;
		case button_OBJ:
			_tile[i].obj_frameX = _current.tile_frameX;
			_tile[i].obj_frameY = _current.tile_frameY;
			_tile[i].move = _current.move;
			_tile[i].obj = _current.obj;
			break;

		}
	}

}
void map_tool::setmap_drag(void)
{
	//마우스 클릭그리기
	int sint;

	for (int i = 0; i < TILEX*TILEY; i++)
	{
		if (PtInRect(&_tile[i].rc, _ptMouse))
		{
			sint = i;
		}
	}
	int j = 0;
	int k = 0;
	for (int i = 0; i < y*x; i++)
	{
		RECT rc = RectMake(0, 0, 600, WINSIZEY);
		if ((!PtInRect(&rc, _ptMouse)))continue;
		_tile[sint + j + k].tile_frameX = _current_drag[i].tile_frameX;
		_tile[sint + j + k].tile_frameY = _current_drag[i].tile_frameY;

		switch (_select_num)
		{
		case button_GROUND:
			_tile[sint + j + k].tile_frameX = _current_drag[i].tile_frameX;
			_tile[sint + j + k].tile_frameY = _current_drag[i].tile_frameY;
			_tile[sint + j + k].move = _current.move;
			_tile[sint + j + k].obj = _current.obj;
			_tile[sint + j + k].battle_num = _current.battle_num;
			break;
		case button_WALL:
			_tile[sint + j + k].tile_frameX = _current_drag[i].tile_frameX;
			_tile[sint + j + k].tile_frameY = _current_drag[i].tile_frameY;
			_tile[sint + j + k].move = _current.move;
			_tile[sint + j + k].obj = _current.obj;
			break;
		case button_OBJ:
			_tile[sint + j + k].tile_frameX = _current_drag[i].tile_frameX;
			_tile[sint + j + k].tile_frameY = _current_drag[i].tile_frameY;
			_tile[sint + j + k].move = _current.move;
			_tile[sint + j + k].obj = _current.obj;
			break;
		}

		j++;
		if (j > x - 1)
		{
			j = 0;
			k += TILEX;
		}
	}
}