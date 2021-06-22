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
    //npc ��ǥ
	set_npc();
	//ī�޶� _x��ǥ _x-285 �� �� ��ǥ
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
		{//���� Ÿ�� �Ӽ� ����
			_text = false;
			for (int i = 0; i < _obj->get_npcV().size(); i++)
			{
				//���� �ڽ� �Դ°� sp��� �̹�
				if (_obj->get_npcV()[i]->get_obj() == OBJ_SP)
				{
					_obj->get_npcV()[i]->set_obj(OBJ_NORMAL);
				}
				else if (_obj->get_npcV()[i]->get_obj() == OBJ_NPC)
				{
					//���� ������
					_obj->get_npcV()[i]->set_select(false);
					//�����̸�
					if (_obj->get_npcV()[i]->get_bag_name() == "����")
					{
						//���ٿ� ���� �ε��� �ѱ��
						DATABASE->set_salesman(_obj->get_npcV()[i]->get_bag_num(), _obj->get_npcV()[i]->get_bag_lv());
						//�� ��ȯ  �ϰ� ����
						SCENEMANAGER->changeScene("salesman");
						DATABASE->setpos(PointMake(_x / 32, _y / 32));
						break;
					}
				}
				else if (_obj->get_npcV()[i]->get_obj() == OBJ_WURP_01)
				{
					//���� ������
					_obj->get_npcV()[i]->set_select(false);

					if (DATABASE->get_map_num() == _obj->get_npcV()[i]->get_map_num()&& _obj->get_npcV()[i]->get_bag_name()=="��")
					{
						_x = _obj->get_npcV()[i]->get_x2();
						_y = _obj->get_npcV()[i]->get_y2();
					break;
					}
					else if(DATABASE->get_map_num() != _obj->get_npcV()[i]->get_map_num() && _obj->get_npcV()[i]->get_bag_name() == "��")
					{
						vector<string> vs;
						bool set=true;
						char temp[123];
						vs = TXTDATA->txtLoad("���Ƿα�/mapSave.txt");
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
							TXTDATA->txtSave("���Ƿα�/mapSave.txt",vs);
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
			//���� �� �����ֳ�
			coil_obj();
		}
	}
	if (_movescene)
	{
		SCENEMANAGER->changeScene("temp_node");
	}
	//þ���� �׻� �� �������� �ؾ� ��
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("�޴�");
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
	//�� Ÿ�� �ε���
	int x = (_x+16) / 32;
	int y = (_y+16) / 32;
	POINT top;
	int i=0;
	int j=0;
	switch (_d)
	{
	case play_scene::left:
		//j�� �� x��ǥ ���� ����
		j = -1;
		//_x 6�̵�
		_x -= 6;
		//�� Ÿ�� �տ� 1�ռ���
		top=PointMake(_tile->get_tile(y * 100 + x).rc.left+ j, _tile->get_tile(y * 100 + x).rc.top );
		break;
	case play_scene::right:
		j = 1;
		_x +=6;
		top = PointMake(_tile->get_tile(y * 100 + x).rc.right+ j, _tile->get_tile(y * 100 + x).rc.top );
		break;
	case play_scene::up:
		//i �� y��
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
	//�浹 �� Ÿ�� �տ� Ÿ��
	if ((PtInRect(&temp, top)&& !_tile->get_tile((y + i) * 100 + (x + j)).move))
	{
		switch (_d)
		{
		case play_scene::left:
			//�տ� ������ ��Ÿ�� �����ʿ� �پ��
			_x = _tile->get_tile((y + i) * 100 + (x + j)).rc.right;
			break;
		case play_scene::right:
			//������ Ÿ�Ͽ� �پ��
			_x = _tile->get_tile((y + i) * 100 + (x + j)).rc.left -32;
			break;
		case play_scene::up:
			//������ Ÿ�Ͽ� �پ��
			_y = _tile->get_tile((y + i) * 100 + (x + j)).rc.bottom;
			break;
		case play_scene::down:
			//������ Ÿ�Ͽ� �پ��
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
		//drj�� x�� ����
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
		//�� �� ������ ����Ŵ 
		rc = RectMake(_tile->get_tile((y + dri) * 100 + (x + drj)).rc.left, _tile->get_tile((y + dri) * 100 + (x + drj)).rc.top,TILESIZE,TILESIZE);
		//�� Ÿ���� �븻�̸� �ѱ�� �ƴϸ�
		if (_tile->get_tile((y + dri) * 100 + (x + drj)).obj == OBJ_NORMAL)continue;
		//�� �տ� npc�� �ڽ� �� ������
		if(IntersectRect(&temp,&_obj->get_npcV()[i]->get_rc(),&rc))
		{
			//Ÿ�� �Ӽ��� ���Ǿ��� ����ȭ
			_obj->get_npcV()[i]->set_obj(_tile->get_tile((y + dri) * 100 + (x + drj)).obj);
			//�װ� ��� ��������
			if (_obj->get_npcV()[i]->get_select())break;
			//npc��
			if (_obj->get_npcV()[i]->get_obj() == OBJ_NPC)
			{   //���ϰ�
				_text = true;
				//���� ����
				_obj->get_npcV()[i]->set_select(true);
			}
			//���ڸ�
			else if (_obj->get_npcV()[i]->get_obj() == OBJ_BOX_01)
			{
				//������ �����ٰž�
				_obj->get_npcV()[i]->set_obj(OBJ_SP);
				//���� �ѷ���
				_text = true;
				//������ ����
				_obj->get_npcV()[i]->set_select(true);
				//�� Ÿ���� ����
				_tile->update_tile(OBJ_NORMAL, false, (y + dri) * 100 + (x + drj));
				//���ڿ� �ִ� �� �������� �̵�
				set_bag(_obj->get_npcV()[i]->get_bag_name(), _obj->get_npcV()[i]->get_bag_num());
			}
			else if (_obj->get_npcV()[i]->get_obj() == OBJ_WURP_01)
			{
				//������ �����ٰž�
				bag_log();
				_obj->get_npcV()[i]->set_obj(OBJ_WURP_01);

				if (_obj->get_npcV()[i]->get_select())break;
				if (_obj->get_npcV()[i]->get_obj() == OBJ_WURP_01)
				{   //���ϰ�
					_text = true;
					//���� ����
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
	//���� txt�߰� 
	vector<string> vs;
	vs = TXTDATA->txtLoad("�׽�/����.txt");
	char temp[123];
	string item;
	int countnum=0;
	for (int i = 0; i < vs.size(); i++)
	{
		// /�̰� ��������
		if (vs[i] == "/")
		{
			//���̸��� ���� �� �ѹ��� ������
			if (vs[i + 1] == itemName&&vs[i + 2] == itoa(inum, temp, 10))
			{
				//���������� ī��Ʈ �� �޾Ƽ� 1����
				countnum = atoi(vs[i + 3].c_str());
				countnum++;
				//ī��Ʈ ����
				vs[i + 3] = itoa(countnum, temp, 10);
			}
		}
	}
	if (countnum == 0)
	{
		//ī��Ʈ�� 0�̸� ���°ų� �� ���� �ؼ� �־��
		countnum = 1;
		item += '/';
		item += ',';
		item += itemName;
		item += ',';
		item += itoa(inum, temp, 10);
		item += ',';
		item += itoa(countnum, temp, 10);
		item += ',';
		//���ͻ���
		vs.push_back(item);
	}
	//���� ���� �Ѱ� ����
	TXTDATA->txtSave("�׽�/����.txt",vs);
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
			//�÷��̾� ã�Ƽ� ��ġ����
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
		//���� �־���
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
		//���Ǿ�
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
		//����� ������ �� ���� ǥ��
		if (vs[i] == "o")
		{
			_obj->set_obj_box(
				"����",
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
	//������ ������
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
	//����� �ؽ�Ʈ ����
	vector<string> vs;
	vs = TXTDATA->txtLoad(set_map_load_obj(DATABASE->get_map_num(), true).c_str());
	for (int i = 0; i < _obj->get_npcV().size(); i++)
	{
		if (_obj->get_npcV()[i]->get_obj() != OBJ_NORMAL)continue;
		//���ڰ� ��� �Ȱǰ�?
		if (_obj->get_npcV()[i]->get_select())
		{
			for (int j = 0; j < vs.size(); j++)
			{
				//�ѷ��� obj�̸��� �ѹ� �� ���� ���� ã�Ƽ� 
				if (vs[j] == _obj->get_npcV()[i]->get_bag_name() &&
					atoi(vs[j + 1].c_str()) == _obj->get_npcV()[i]->get_bag_num())
				{
					//������  ��ǥ�� ���� 
					vs[j].erase();
					vs[j + 1].erase();
					vs[j - 1].erase();
					vs[j - 2].erase();
					vs[j - 5] = "o";
					//�̸���  'o'  ����
				}
			}
		}
	}
	//�ٽ� ����

	TXTDATA->txtSave(set_map_load_obj(DATABASE->get_map_num(), true).c_str(), vs);
	vs.clear();

}