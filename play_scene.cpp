#include "stdafx.h"
#include "play_scene.h"


play_scene::play_scene()
{
}


play_scene::~play_scene()
{
}

HRESULT play_scene::init(void)
{
	_p = new player;
	_p->init();
	_tile =new tile_map;
	_tile->init();
	_obj = new obj_npc_M;
	_obj->init();
	_d = down;
	_movescene = false;
	SetWindowPos(_hWnd, NULL, 0, 0, 600, 600, SWP_NOMOVE);
    //npc 좌표
	set_npc();
	//카메라 _x좌표 _x-285 는 내 좌표
	_tile->set_x(_x - 285);
	_tile->set_y(_y - 285);
	_text = false;
	return S_OK;
}
void play_scene::release(void)
{
	re_set();
}
void play_scene::update(void)
{
	for (int i = 0; i < _obj->get_npcV().size(); i++)
	{
		_obj->get_npcV()[i]->set_xy(_x-285, _y-285);
	}
	_p->update();
	_obj->update();
	_tile->set_x(_x - 285);
	_tile->set_y(_y - 285);

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_d = up;
		coil_wall();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_d = down;
		coil_wall();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_d = left;
		coil_wall();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_d = right;
		coil_wall();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (_text)
		{//상자 타일 속성 변경
			_text = false;
			for (int i = 0; i < _obj->get_npcV().size(); i++)
			{
				//만약 박스 먹는건 sp라는 이뮨
				if (_obj->get_npcV()[i]->get_obj() == OBJ_SP)
				{
					_obj->get_npcV()[i]->set_obj(OBJ_NORMAL);
				}
				else if (_obj->get_npcV()[i]->get_obj() == OBJ_NPC)
				{
					//말이 끝났음
					_obj->get_npcV()[i]->set_select(false);
					//상인이면
					if (_obj->get_npcV()[i]->get_bag_name() == "상인")
					{
						//데바에 상인 인덱스 넘기고
						DATABASE->set_salesman(_obj->get_npcV()[i]->get_bag_num(), _obj->get_npcV()[i]->get_bag_lv());
						//씬 전환  하고 스톱
						SCENEMANAGER->changeScene("salesman");
						DATABASE->setpos(PointMake(_x / 32, _y / 32));
						break;
					}
				}
				else if (_obj->get_npcV()[i]->get_obj() == OBJ_WURP_01)
				{
					//말이 끝났음
					_obj->get_npcV()[i]->set_select(false);

					if (DATABASE->get_map_num() == _obj->get_npcV()[i]->get_map_num()&& _obj->get_npcV()[i]->get_bag_name()=="문")
					{
						_x = _obj->get_npcV()[i]->get_x2();
						_y = _obj->get_npcV()[i]->get_y2();
					break;
					}
					else if(DATABASE->get_map_num() != _obj->get_npcV()[i]->get_map_num() && _obj->get_npcV()[i]->get_bag_name() == "문")
					{
						vector<string> vs;
						bool set=true;
						char temp[123];
						vs = TXTDATA->txtLoad("파판로그/mapSave.txt");
						for (int i = 0; i < vs.size(); i++)
						{
							if (vs[i] == "/"&&atoi(vs[i + 1].c_str()) == DATABASE->get_map_num())
							{
								set = false;
							}
						}
						if (set)
						{
							string s;
							s = ",";
							s +="/";
							s += ",";
							s += itoa(DATABASE->get_map_num(), temp, 10);
							s += ",";
							vs.push_back(s);
							TXTDATA->txtSave("파판로그/mapSave.txt",vs);
							vs.clear();
						}
						DATABASE->set_map_num(_obj->get_npcV()[i]->get_map_num());
						DATABASE->setpos(PointMake(_obj->get_npcV()[i]->get_x2(), _obj->get_npcV()[i]->get_y2()));
						_movescene = true;
					}
				}
			}
		}
		else
		{
			//상자 나 엔씨있넹
			coil_obj();
		}
	}
	if (_movescene)
	{
		SCENEMANAGER->changeScene("temp_node");
	}
	//첸지는 항상 맨 마지막에 해야 됨
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("메뉴");
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		SCENEMANAGER->changeScene("battle_scene");
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		bag_log();
		SCENEMANAGER->changeScene("inven");
		DATABASE->setpos(PointMake(_x/32,_y / 32));
	}
}
void play_scene::render(void)
{
	_tile->render();
	_obj->render();
	_p->render();
	if (_text)
	{
		for (int i = 0; i < _obj->get_npcV().size(); i++)
		{
			if (_obj->get_npcV()[i]->get_obj() == OBJ_SP)
			{
				_obj->get_npcV()[i]->text();
			}
			else if (_obj->get_npcV()[i]->get_obj() == OBJ_NPC)
			{
				_obj->get_npcV()[i]->text();
			}
			else if (_obj->get_npcV()[i]->get_obj() == OBJ_WURP_01)
			{
				_obj->get_npcV()[i]->text();
			}
		}
	}
}
void play_scene::coil_wall(void)
{
	//네 타일 인덱스
	int x = (_x+16) / 32;
	int y = (_y+16) / 32;
	POINT top;
	int i=0;
	int j=0;
	switch (_d)
	{
	case play_scene::left:
		//j는 내 x좌표 앞임 왼쪽
		j = -1;
		//_x 6이동
		_x -= 6;
		//내 타일 앞에 1앞선다
		top=PointMake(_tile->get_tile(y * 100 + x).rc.left+ j, _tile->get_tile(y * 100 + x).rc.top );
		break;
	case play_scene::right:
		j = 1;
		_x +=6;
		top = PointMake(_tile->get_tile(y * 100 + x).rc.right+ j, _tile->get_tile(y * 100 + x).rc.top );
		break;
	case play_scene::up:
		//i 는 y축
		i = -1;
		_y -= 6;
		top = PointMake(_tile->get_tile(y * 100 + x).rc.left , _tile->get_tile(y * 100 + x).rc.top+ i);
		break;
	case play_scene::down:
		i = 1;
		_y += 6;
		top = PointMake(_tile->get_tile(y * 100 + x).rc.left , _tile->get_tile(y * 100 + x).rc.bottom + i);
		break;
	}
	RECT temp;
	temp = RectMake(_tile->get_tile((y + i) * 100 + (x + j)).rc.left, _tile->get_tile((y + i) * 100 + (x + j)).rc.top,TILESIZE,TILESIZE);
	//충돌 내 타일 앞에 타일
	if ((PtInRect(&temp, top)&& !_tile->get_tile((y + i) * 100 + (x + j)).move))
	{
		switch (_d)
		{
		case play_scene::left:
			//앞에 모있음 그타일 오른쪽에 붙어라
			_x = _tile->get_tile((y + i) * 100 + (x + j)).rc.right;
			break;
		case play_scene::right:
			//모있음 타일에 붙어라
			_x = _tile->get_tile((y + i) * 100 + (x + j)).rc.left -32;
			break;
		case play_scene::up:
			//모있음 타일에 붙어라
			_y = _tile->get_tile((y + i) * 100 + (x + j)).rc.bottom;
			break;
		case play_scene::down:
			//모있음 타일에 붙어라
			_y = _tile->get_tile((y + i) * 100 + (x + j)).rc.top -32;
			break;
		}	
	}
	
}
void play_scene::coil_obj(void)
{
	int x = (_x + 16) / 32;
	int y = (_y + 16) / 32;
	POINT top;
	int dri = 0;
	int drj = 0;

	switch (_d)
	{
	case play_scene::left:
		//drj는 x쪽 방향
		drj = -1;
		top = PointMake(_tile->get_tile(y * 100 + x).rc.left + drj, _tile->get_tile(y * 100 + x).rc.top);
		break;
	case play_scene::right:
		drj = 1;
		top = PointMake(_tile->get_tile(y * 100 + x).rc.right + drj, _tile->get_tile(y * 100 + x).rc.top);
		break;
	case play_scene::up:
		dri = -1;
		top = PointMake(_tile->get_tile(y * 100 + x).rc.left, _tile->get_tile(y * 100 + x).rc.top + dri);
		break;
	case play_scene::down:
		dri = 1;
		top = PointMake(_tile->get_tile(y * 100 + x).rc.left, _tile->get_tile(y * 100 + x).rc.bottom + dri);
		break;
	}
	for (int i = 0; i < _obj->get_npcV().size(); i++)
	{
		RECT temp;
		RECT rc;
		//내 앞 방향을 가리킴 
		rc = RectMake(_tile->get_tile((y + dri) * 100 + (x + drj)).rc.left, _tile->get_tile((y + dri) * 100 + (x + drj)).rc.top,TILESIZE,TILESIZE);
		//그 타일이 노말이면 넘기고 아니면
		if (_tile->get_tile((y + dri) * 100 + (x + drj)).obj == OBJ_NORMAL)continue;
		//내 앞에 npc나 박스 가 있으면
		if(IntersectRect(&temp,&_obj->get_npcV()[i]->get_rc(),&rc))
		{
			//타일 속성을 엔피씨와 동기화
			_obj->get_npcV()[i]->set_obj(_tile->get_tile((y + dri) * 100 + (x + drj)).obj);
			//그게 사용 않했으면
			if (_obj->get_npcV()[i]->get_select())break;
			//npc면
			if (_obj->get_npcV()[i]->get_obj() == OBJ_NPC)
			{   //말하고
				_text = true;
				//구분 짓고
				_obj->get_npcV()[i]->set_select(true);
			}
			//상자면
			else if (_obj->get_npcV()[i]->get_obj() == OBJ_BOX_01)
			{
				//아이탬 보여줄거야
				_obj->get_npcV()[i]->set_obj(OBJ_SP);
				//말을 뿌려라
				_text = true;
				//아이탬 썻네
				_obj->get_npcV()[i]->set_select(true);
				//이 타일은 뭐지
				_tile->update_tile(OBJ_NORMAL, false, (y + dri) * 100 + (x + drj));
				//상자에 있는 템 가방으로 이동
				set_bag(_obj->get_npcV()[i]->get_bag_name(), _obj->get_npcV()[i]->get_bag_num());
			}
			else if (_obj->get_npcV()[i]->get_obj() == OBJ_WURP_01)
			{
				//아이탬 보여줄거야
				bag_log();
				_obj->get_npcV()[i]->set_obj(OBJ_WURP_01);

				if (_obj->get_npcV()[i]->get_select())break;
				if (_obj->get_npcV()[i]->get_obj() == OBJ_WURP_01)
				{   //말하고
					_text = true;
					//구분 짓고
					_obj->get_npcV()[i]->set_select(true);
					for (int k = -1; k < 2; k++)
					{
						for (int j = -1; j < 2; j++)
						{
							_tile->update_tile(OBJ_NORMAL, true, (_obj->get_npcV()[i]->get_y2() + k) * 100 + (_obj->get_npcV()[i]->get_x2() + j));
						}
					}
				}
			}
		}
	}
}
void play_scene::set_bag(string itemName, int inum)
{
	//가방 txt추가 
	vector<string> vs;
	vs = TXTDATA->txtLoad("테스/가방.txt");
	char temp[123];
	string item;
	int countnum=0;
	for (int i = 0; i < vs.size(); i++)
	{
		// /이거 기준으로
		if (vs[i] == "/")
		{
			//탬이름이 같고 탬 넘버가 같으면
			if (vs[i + 1] == itemName&&vs[i + 2] == itoa(inum, temp, 10))
			{
				//탬이있으니 카운트 만 받아서 1더함
				countnum = atoi(vs[i + 3].c_str());
				countnum++;
				//카운트 변경
				vs[i + 3] = itoa(countnum, temp, 10);
			}
		}
	}
	if (countnum == 0)
	{
		//카운트가 0이면 없는거네 템 생성 해서 넣어둠
		countnum = 1;
		item += '/';
		item += ',';
		item += itemName;
		item += ',';
		item += itoa(inum, temp, 10);
		item += ',';
		item += itoa(countnum, temp, 10);
		item += ',';
		//백터생성
		vs.push_back(item);
	}
	//지금 까지 한거 저장
	TXTDATA->txtSave("테스/가방.txt",vs);
	vs.clear();
}
void play_scene::set_npc(void)
{
	int bacount = 0;
	vector<string> vs;
	vs = TXTDATA->txtLoad(set_map_load_obj(DATABASE->get_map_num(),true).c_str());
	for (int i = 0; i < vs.size(); i++)
	{
		if (DATABASE->getpos().x == 0 && DATABASE->getpos().y == 0)
		{
			//플레이어 찾아서 위치잡음
			if (vs[i] == "p")
			{
				_x = _tile->get_tile(atoi(vs[i + 2].c_str()) * 100 + atoi(vs[i + 1].c_str())).rc.left;
				_y = _tile->get_tile(atoi(vs[i + 2].c_str()) * 100 + atoi(vs[i + 1].c_str())).rc.top;
			}
		}
		else 
		{
			_x = _tile->get_tile(DATABASE->getpos().y * 100 + DATABASE->getpos().x).rc.left;
			_y = _tile->get_tile(DATABASE->getpos().y * 100 + DATABASE->getpos().x).rc.top;
		}
		//가방 넣어줌
		if (vs[i] == "b")
		{
		string s=	vs[i + 2];
			_obj->set_obj_box(
				vs[i + 2],
				_tile->get_tile(atoi(vs[i - 1].c_str()) * 100 + atoi(vs[i - 2].c_str())).rc.left,
				_tile->get_tile(atoi(vs[i - 1].c_str()) * 100 + atoi(vs[i - 2].c_str())).rc.top,
				atoi(vs[i + 3].c_str()));
			_tile->update_tile(OBJ_BOX_01, false, atoi(vs[i - 1].c_str()) * 100 + atoi(vs[i - 2].c_str()));
			_obj->get_npcV()[bacount]->set_bag(atoi(vs[i+3].c_str()),0, vs[i + 2]);
			bacount++;
			
		}
		//엔피씨
		if (vs[i] == "m")
		{
			_obj->set_npc_stand(
				vs[i + 3],
				_tile->get_tile(atoi(vs[i - 1].c_str()) * 100 + atoi(vs[i - 2].c_str())).rc.left,
				_tile->get_tile(atoi(vs[i - 1].c_str()) * 100 + atoi(vs[i - 2].c_str())).rc.top,
				vs[i + 2],
				atoi(vs[i + 4].c_str()));
			_tile->update_tile(OBJ_NPC, false, atoi(vs[i - 1].c_str()) * 100 + atoi(vs[i - 2].c_str()));
			_obj->get_npcV()[bacount]->set_bag(atoi(vs[i + 4].c_str()), atoi(vs[i + 5].c_str()),vs[i + 3]);
			bacount++;
		}
		if (vs[i] == "w")
		{
			_obj->set_npc_imagine(
				vs[i + 2],
				_tile->get_tile(atoi(vs[i + 6].c_str()) * 100 + atoi(vs[i + 5].c_str())).rc.left,
				_tile->get_tile(atoi(vs[i + 6].c_str()) * 100 + atoi(vs[i + 5].c_str())).rc.top,
				 atoi(vs[i + 8].c_str()),
                 atoi(vs[i + 9].c_str()),
				atoi(vs[i + 10].c_str()));
			_obj->get_npcV()[bacount]->set_bag(atoi(vs[i + 1].c_str()), 100, vs[i + 2]);
			_tile->update_tile(OBJ_WURP_01, false, atoi(vs[i + 6].c_str()) * 100 + atoi(vs[i + 5].c_str()));
			bacount++;
		}
		//사용한 아이탬 빈 상자 표시
		if (vs[i] == "o")
		{
			_obj->set_obj_box(
				"없음",
				_tile->get_tile(atoi(vs[i + 2].c_str()) * 100 + atoi(vs[i + 1].c_str())).rc.left,
				_tile->get_tile(atoi(vs[i + 2].c_str()) * 100 + atoi(vs[i + 1].c_str())).rc.top,
				0);
			_tile->update_tile(OBJ_BOX_01, false, atoi(vs[i + 2].c_str()) * 100 + atoi(vs[i + 1].c_str()));
			bacount++;
			//exit(true);
		}
	}
	vs.clear();
}
void play_scene::re_set(void)
{
	//리무브 얼해줌
	_obj->removeall();
	_obj->release();
	SAFE_DELETE(_obj);
	_p->release();
	SAFE_DELETE(_p);
	_tile->release();
	SAFE_DELETE(_tile);
}
void play_scene::bag_log(void)
{
	//빈상자 텍스트 저장
	vector<string> vs;
	vs = TXTDATA->txtLoad(set_map_load_obj(DATABASE->get_map_num(), true).c_str());
	for (int i = 0; i < _obj->get_npcV().size(); i++)
	{
		if (_obj->get_npcV()[i]->get_obj() != OBJ_NORMAL)continue;
		//상자가 사용 된건가?
		if (_obj->get_npcV()[i]->get_select())
		{
			for (int j = 0; j < vs.size(); j++)
			{
				//뿌려진 obj이름과 넘버 가 같은 곳을 찾아서 
				if (vs[j] == _obj->get_npcV()[i]->get_bag_name() &&
					atoi(vs[j + 1].c_str()) == _obj->get_npcV()[i]->get_bag_num())
				{
					//지워줌  좌표는 빼고 
					vs[j].erase();
					vs[j + 1].erase();
					vs[j - 1].erase();
					vs[j - 2].erase();
					vs[j - 5] = "o";
					//이름을  'o'  변경
				}
			}
		}
	}
	//다시 저장

	TXTDATA->txtSave(set_map_load_obj(DATABASE->get_map_num(), true).c_str(), vs);
	vs.clear();

}