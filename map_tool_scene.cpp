#include "stdafx.h"
#include "map_tool_scene.h"


map_tool_scene::map_tool_scene()
{
}


map_tool_scene::~map_tool_scene()
{
}
HRESULT map_tool_scene::init(void)
{
	init_map_tool();
	_current.move = true;
	_objD->set_fileName(_map_creat->get_fileName());
	_current.battle_num = 0;

	return S_OK;
}
void map_tool_scene::release(void)
{
	_map_creat->release();
	_map_load->release();
	SAFE_DELETE(_map_creat);
	SAFE_DELETE(_map_load);
	SAFE_DELETE(_objD);
}
void map_tool_scene::update(void)
{
	_objD->set_button_num(_select_num);
	
	//마우스
	mouse();
	//드레그
	_drag->update();
	for (int i = 0; i < buttonmax; i++)
	{
		_button[i]->update();
	}
	//키보드 
	keyboard();
	
}
void map_tool_scene::render(void)
{
	char str[123];
	IMAGEMANAGER->findImage("파판_1_소")->render(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("파판_1_소")->getWidth(), 0);

	_map_creat->render();//그려지는 맵

	_map_load->render();//복사할 맵

	_drag->render();	
	drag_draw();
	save_load_draw();	
	for (int i = 0; i < buttonmax; i++)
	{
		if (!_current.move&&i == graound)continue;
		if (_current.move&&i == wall)continue;
		 _button[i]->render();
	}
	if(_map_select_1)
	{
		mouse_set_tile((_ptMouse.x + _x) / 16, (_ptMouse.y + _y) / 16, _x, _y);
		sprintf_s(str, "%d %d", (_ptMouse.x + _x) / 16, (_ptMouse.y + _y) / 16);
		TextOut(getMemDC(), _ptMouse.x - 10, _ptMouse.y + 20, str, strlen(str));
	}
	else if(!_map_select_1)
	{
		mouse_set_tile((_ptMouse.x - (WINSIZEX / 2) + _x2) / 16, (_ptMouse.y - 300 + _y2) / 16, _x2- +(WINSIZEX / 2), _y2-300);
		sprintf_s(str, "%d %d", (_ptMouse.x-(WINSIZEX / 2) + _x2) / 16, ((_ptMouse.y- 300) + _y2) / 16);
		TextOut(getMemDC(), _ptMouse.x-10 , _ptMouse.y+20, str, strlen(str));
	}
	_objD->obj_draw();

	sprintf_s(str, "%d", _current.move);
	TextOut(getMemDC(), 200,200, str, strlen(str));
}
void map_tool_scene::keyboard(void)
{
	
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_map_select_1&& (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse)))
		{
			_x += 10;
		}
		else if((PtInRect(&RectMake(WINSIZEX / 2, 300, WINSIZEX, WINSIZEY), _ptMouse)))
		{
			_x2 += 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_map_select_1&& (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse)))
		{
			_x -= 10;
		}
		else if((PtInRect(&RectMake(WINSIZEX / 2, 300, WINSIZEX, WINSIZEY), _ptMouse)))
		{
			_x2 -= 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_map_select_1&& (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse)))
		{
			_y += 10;
		}
		else if((PtInRect(&RectMake(WINSIZEX / 2, 300, WINSIZEX, WINSIZEY), _ptMouse)))
		{
			_y2 += 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_map_select_1&& (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse)))
		{
			_y -= 10;
		}
		else if((PtInRect(&RectMake(WINSIZEX / 2, 300, WINSIZEX, WINSIZEY), _ptMouse)))
		{
			_y2 -= 10;
		}
	}
	if (_map_creat != NULL)
	{
		if (_map_select_1&& (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse)))
		{
			_map_creat->set_x(_x);
			_map_creat->set_y(_y);
		}
		else if((PtInRect(&RectMake(WINSIZEX / 2, 300, WINSIZEX, WINSIZEY), _ptMouse)))
		{
			_map_load->set_x(_x2);
			_map_load->set_y(_y2);
		}
	}
	
	if (KEYMANAGER->isOnceKeyDown('S') && _select_num != obj)
	{
		_TEXTstart = true;
		_saveload = save;
	}
	if (KEYMANAGER->isOnceKeyDown('L') && _select_num != obj)
	{
		_TEXTstart = true;
		_saveload = load;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) )
	{
		if (_TEXTstart)
		{
			key_save_load();
		}
		_objD->obj_control();
		_select_num = _objD->get_button_num();
	}

	for (int i = 0; i < sizeof(textchar); i++)
	{
		switch (_saveload)
		{
		case map_tool_scene::save:
			if (textchar[i] == 's')
			{ //똥갑 삭제
				textchar[i] = NULL;
			}
			break;
		case map_tool_scene::load:
			if (textchar[i] == 'l')
			{
				textchar[i] = NULL;
			}
		break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('A') && _select_num != obj)
	{
		SCENEMANAGER->changeScene("메뉴");
	}
}
void map_tool_scene::set_up_sample(void)
{
	//샘플맵 인잇
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sample[i * SAMPLETILEX + j].tile_frameX = j;
			_sample[i * SAMPLETILEX + j].tile_frameY = i;
			_sample[i*SAMPLETILEX + j].rc = RectMake(
				j*TILESIZE_05 + WINSIZEX  - IMAGEMANAGER->findImage("파판_1_소")->getWidth(),
				i*TILESIZE_05,
				TILESIZE_05, TILESIZE_05);
		}
	}
}
void map_tool_scene::mouse(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < buttonmax; i++)
		{
			if (PtInRect(&_button[i]->get_rc(), _ptMouse))
			{
				if (!_current.move&&i == wall)continue;
				if (_current.move&&i == graound)continue;
				_select_num = _button[i]->get_num();
				_button[i]->set_slect(true);
			}
		}

		set_obj_mouse();

		switch (_count)
		{ //드레그 시작점
		case mouse_drag:
			if (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse))
			{
				_drag->_isdrag(true);
				_drag->set_first(_ptMouse);
			}
		break;
		case mouse_set_map_drag:
			//복사 할 곳 드레그 시작점
			if (PtInRect(&RectMake(WINSIZEX / 2, 300, WINSIZEX, WINSIZEY), _ptMouse))
			{
				_drag->_isdrag(true);
				_drag->set_first(_ptMouse);
			}
			//드레그 붙여넣기
			else if (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse))
			{
				if (current_tilex == 0)return;
				set_map();
			}
		break;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		//샘플 클릭
		set_sample();
		//클릭으로 그리기
		if (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse) && (_select_num != obj && _select_num != new_obj)&& _count == mouse_one)
		{
			set_map();
		}
	}
	//키업
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			for (int i = 0; i < buttonmax; i++)
			{
				if (PtInRect(&_button[i]->get_rc(), _ptMouse))
				{
					set_button();
				}
				_button[i]->set_slect(false);
			}
			switch (_count)
			{
			case mouse_drag:
				//드레그 마지막 지점 저장 후 드레그 에 그림
				_drag->_isdrag(false);
				_drag->set_END(_ptMouse);
				set_map();
				break;
			case mouse_set_map_drag:
				//드레그 한걸 가상 드레그 속성 부여
				_drag->_isdrag(false);
				_drag->set_END(_ptMouse);
				current_map();
				break;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			//마우스 선택
			_count++;
			if (_count > mouse_set_map_drag)
			{
				_count = mouse_one;
			}
			_objD->set_obj_mouse_right();
		}
	//마우스 위치
	if (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse))
	{
		_map_select_1 = true;
	}
	else if(PtInRect(&RectMake(WINSIZEX / 2, 300, WINSIZEX, WINSIZEY), _ptMouse))
	{
		_map_select_1 = false;
	}
}
void map_tool_scene::set_map(void)
{
	switch (_count)
	{
	case mouse_one:
		//마우스 그리기 
		if (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse) && (_ptMouse.x + _x) / 16<100 && (_ptMouse.y + _y) / 16<100)
		{
			int x = (_ptMouse.x+_x )/ TILESIZE_05;
			int y = (_ptMouse.y +_y) / TILESIZE_05;
			_map_creat->set_tile(_current, y*_map_creat->get_tilex() + x);
		}
		break;
	case mouse_drag:
		//드레그 된곳 그리기
		if (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse))
		{
			for (int i= (_drag->get_first().y + _y) / TILESIZE_05; i < (_drag->get_end().y + _y) / TILESIZE_05; i++)
			{
				for (int j = (_drag->get_first().x + _x) / TILESIZE_05; j < (_drag->get_end().x + _x) / TILESIZE_05; j++)
				{
					_map_creat->set_tile(_current, i*_map_creat->get_tilex() + j);
				}
			}
		}
		break;
	case mouse_set_map_drag:
		//복사된거 붙여넣기
		if (PtInRect(&RectMake(0, 0, WINSIZEX / 2, WINSIZEY), _ptMouse))
		{
			int fx = (_ptMouse.x + _x) / TILESIZE_05;
			int fy = (_ptMouse.y + _y) / TILESIZE_05;

			int k = fy;
			for (int i = 0; i < current_tiley; i++)
			{
				int q = fx;
				for (int j = 0; j < current_tilex; j++)
				{
					//탬프 커런트 타일에 넣고 돌림
					_current.tile_frameX = current_tile[i*current_tilex + j].tile_frameX;
					_current.tile_frameY = current_tile[i*current_tilex + j].tile_frameY;
					_current.move = current_tile[i*current_tilex + j].move;
					_map_creat->set_tile(_current, k*_map_creat->get_tilex() + q); 
					q++;
				}
				k++;
			}
			current_tiley = 0;
			current_tilex = 0;
			SAFE_DELETE(current_tile);
			current_tile = new tagtile[current_tilex*current_tiley];
		}
		break;
	}
}
void map_tool_scene::set_sample(void)
{
	//커런트 타일에 복사
	for (int i = 0; i < SAMPLETILEY*SAMPLETILEX; i++)
	{
		if (PtInRect(&_sample[i].rc, _ptMouse))
		{
			_current.tile_frameX = _sample[i].tile_frameX;
			_current.tile_frameY = _sample[i].tile_frameY;
		}
	}
}
void map_tool_scene::current_map(void)
{
	//커런트 타일에 속성 부여
	if (_count == mouse_set_map_drag)
	{
		if (PtInRect(&RectMake(WINSIZEX / 2, 300, WINSIZEX, WINSIZEY), _ptMouse))
		{
			current_tilex = (_drag->get_first().x- _drag->get_end().x )/ TILESIZE_05;
			if (current_tilex < 0)
			{//음수 제거
				current_tilex=current_tilex*-1;
			}
			current_tiley = (_drag->get_first().y - _drag->get_end().y) / TILESIZE_05;
			if (current_tiley < 0) 
			{//음수 제거
				current_tiley=current_tiley*-1;
			}
			//사용할 만 큼 동적 할당
			current_tile = new tagtile[current_tilex*current_tiley];

			int fx = (_drag->get_first().x+ _x2 - WINSIZEX / 2) / TILESIZE_05;
			int fy = (_drag->get_first().y+ _y2 - 300)/ TILESIZE_05;
			//시작점이 다르지만 같은 형태로 돌림 변수 두개 추가하여
			//같은 방식으로 돌림
			int k = fy;
			for (int i = 0; i < current_tiley; i++)
			{
				int q = fx;
				for (int j = 0; j < current_tilex; j++)
				{
					//동적할당된 타일에 속성 부여
					current_tile[i*current_tilex+ j].tile_frameX = _map_load->get_tile(k*_map_load->get_tilex() + q).tile_frameX;
					current_tile[i*current_tilex + j].tile_frameY = _map_load->get_tile(k*_map_load->get_tilex() + q).tile_frameY;
					current_tile[i*current_tilex + j].move = _map_load->get_tile(k*_map_load->get_tilex() + q).move;
					current_tile[i*current_tilex + j].battle_num = _map_load->get_tile(k*_map_load->get_tilex() + q).battle_num;
					current_tile[i*current_tilex + j].rc = RectMake(j*TILESIZE_05, i*TILESIZE_05, TILESIZE_05, TILESIZE_05);
					q++;
				}
				k++;
			}
		}
	}
}
void map_tool_scene::drag_draw(void)
{
	for (int i = 0; i < current_tiley*current_tilex; i++)//드레그 확인용
	{
		IMAGEMANAGER->findImage("파판_1_소")->frameRender(getMemDC(),
			current_tile[i].rc.left + _ptMouse.x,
			current_tile[i].rc.top + _ptMouse.y,
			current_tile[i].tile_frameX, current_tile[i].tile_frameY);
	}
}
void map_tool_scene::save_load_draw(void)
{
	if (_TEXTstart)//세이브 로드 확인용
	{
		char str[123];
		sprintf(str, textchar);
		Rectangle(getMemDC(), _ptMouse.x, _ptMouse.y - 30, _ptMouse.x + 25, _ptMouse.y);
		TextOut(getMemDC(), _ptMouse.x, _ptMouse.y - 25, str, strlen(str));
	}
}
void map_tool_scene::key_save_load(void)
{
	switch (_saveload)
	{
	case map_tool_scene::save:
	{
		//세이브 정장
		_TEXTstart = false;
		char temp[123];
		strcpy(temp, textchar);
		int i = atoi(temp);
		strcpy(temp, itoa(i, temp, 10));
		char str[258];
		ZeroMemory(str, sizeof(str));
		strcat(str, "파판맵/mapSave");
		strcat(str, temp);
		strcat(str, ".map");
		_map_creat->save(temp, str);
		textchar[0] = '\0';
		_saveload = end;
	}
	break;
	case map_tool_scene::load:
	{
		//로드맵
		_TEXTstart = false;
		string temp;
		temp+= textchar;
		_map_creat->changeName(atoi(temp.c_str()));
		_objD->set_fileName(_map_creat->get_fileName());
		textchar[0] = '\0';
		_saveload = end;
		temp.clear();
	}
	break;
	case map_tool_scene::end:
		break;
	}
}
void map_tool_scene::init_map_tool(void)
{
	_map_creat = new map_creat;
	_map_creat->init();
	_map_load = new map_load;
	_map_load->init();
	_drag = new drag;
	_drag->init();
	_drag->_isdrag(false);
	_map_count = 1;
	set_up_sample();
	_x = _y = _x2 = _y2 = 0;
	_map_select_1 = true;
	_count = 0;
	current_tiley = 0;
	current_tilex = 0;
	_TEXTstart = false;
	for (int i = 0; i < buttonmax; i++)
	{
		_button[i] = new button;
	}
	_button[left]->init("체리", 676, 264,20,9, "<<<", left);
	_button[right]->init("체리", 1285, 264, 20, 9, ">>>", right);
	_button[wall]->init("화이트", 740, 264, 24, 9, "벽", wall);
	_button[obj]->init("화이트", 868, 264, 20, 9, "obj", obj);
	_button[new_obj]->init("화이트", 804, 264, 2, 9, "new_obj", new_obj);
	_button[graound]->init("화이트", 740, 264, 5, 9, "ground", graound);
	_button[battle_num_F]->init("화이트", 932, 264, 5, 9, "적LV+", battle_num_F);
	_button[battle_num_M]->init("화이트", 996, 264, 5, 9, "적LV-", battle_num_M);
	_objD = new map_tool_obj_darw;
	_objD->init();
}
void map_tool_scene::set_button(void)
{
	switch (_select_num)
	{
	case left:
		_map_count--;
		_map_load->changeName(_map_count);
		break;
	case right:
		_map_count++;
		_map_load->changeName(_map_count);
		break;
	case wall:
		_current.move= false;
		break;
	case obj:
		_TEXTstart = true;
		break;
	case new_obj:
		_TEXTstart = true;
		break;
	case graound:
		_current.move = true;
		break;
	case battle_num_F:
		_current.battle_num++;
		break;
	case battle_num_M:
		_current.battle_num--;
		break;
	}
}
void map_tool_scene::mouse_set_tile(int x, int y,int cx,int cy)
{
	if (x < 0 || y < 0)return;
		if (x > _map_creat->get_tilex() || y > _map_creat->get_tilex())return;
		IMAGEMANAGER->findImage("파판_1_소")->frameRender(getMemDC(),
			_map_load->get_tile(y * 100 + x).rc.left - cx, _map_creat->get_tile(y * _map_creat->get_tilex() + x).rc.top - cy,
			_objD->get_currentobj().x, _objD->get_currentobj().y);
}
void map_tool_scene::set_obj_mouse(void)
{
	if (_objD->get_obj() == dr_coordinate)
	{
		char temp[123];
		_objD->set_obj_str(_objD->set_obj_save(itoa((_ptMouse.x + _x) / TILESIZE_05, temp, 10), false));
		_objD->set_obj_str(_objD->set_obj_save(itoa((_ptMouse.y + _y) / TILESIZE_05, temp, 10), false));
		int x = (_ptMouse.x + _x) / 16;
		int y = (_ptMouse.y + _y) / 16;
		for (int i = 0; i < _objD->get_str().size(); i++)
		{
			if (_objD->get_str()[i] == 'p')
			{
				_map_creat->set_obj(y*_map_creat->get_tilex() + x, 12, 0);
				_objD->set_obj(dr_obj_View);
			}
			else if (_objD->get_str()[i] == 'n')
			{
				_map_creat->set_obj(y*_map_creat->get_tilex() + x, 4, 2);
				_objD->set_obj(dr_obj_job);
				_TEXTstart = true;
			}
			else if (_objD->get_str()[i] == 'w')
			{
				_map_creat->set_obj(y*_map_creat->get_tilex() + x, _objD->get_currentobj().x, _objD->get_currentobj().y);
				_objD->set_obj_str(_objD->set_obj_save("!", false));
				_objD->set_obj(dr_coordinate2);
			}
		}
	}
	else if (_objD->get_obj() == dr_coordinate2 && _map_select_1==_objD->get_currentobj().sir)
	{
		char temp[123];
		if (!_map_select_1)
		{
			_objD->set_obj_str(_objD->set_obj_save(itoa((_ptMouse.x - (WINSIZEX / 2) + _x2) / TILESIZE_05, temp, 10), false));
			_objD->set_obj_str(_objD->set_obj_save(itoa((_ptMouse.y - 300 + _y2) / TILESIZE_05, temp, 10), false));
		}
		else if (_map_select_1)
		{
			_objD->set_obj_str(_objD->set_obj_save(itoa((_ptMouse.x + _x) / TILESIZE_05, temp, 10), false));
			_objD->set_obj_str(_objD->set_obj_save(itoa((_ptMouse.y + _y) / TILESIZE_05, temp, 10), false));
		}
		for (int i = 0; i < _objD->get_str().size(); i++)
		{
		    if (!_map_select_1)
		    {
		    	int x = (_ptMouse.x - (WINSIZEX / 2) + _x2) / 16;
		    	int y = (_ptMouse.y - 300 + _y2) / 16;
				if (_objD->get_str()[i] == '!')
				{
					_objD->set_obj_str(_objD->set_obj_save(itoa(_map_load->get_num(), temp, 10), false));
					_objD->set_obj(dr_obj_View);
				}
		    }
		    else if (_map_select_1)
		    {
		    	int x = (_ptMouse.x + _x) / 16;
		    	int y = (_ptMouse.y + _y) / 16;
			    if (_objD->get_str()[i] == '!')
			    {
			    	_objD->set_obj_str(_objD->set_obj_save(itoa(_map_load->get_num(), temp, 10), false));
			    	_map_creat->set_obj(y*_map_creat->get_tilex() + x, _objD->get_currentobj().x, _objD->get_currentobj().y);
			    	_objD->set_obj(dr_obj_View);
			    }
			}
		}
	}
}