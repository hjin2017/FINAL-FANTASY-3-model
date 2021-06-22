#include "stdafx.h"
#include "inven_equipment.h"


inven_equipment::inven_equipment()
{
}


inven_equipment::~inven_equipment()
{
}
HRESULT inven_equipment::init(void)
{
	load_eq(DATABASE->getElementData(DATABASE->get_player())->handle_1.name, DATABASE->getElementData(DATABASE->get_player())->handle_1.num, DATABASE->getElementData(DATABASE->get_player())->handle_1.selecst, hand_1);
	load_eq(DATABASE->getElementData(DATABASE->get_player())->handle_2.name, DATABASE->getElementData(DATABASE->get_player())->handle_2.num, DATABASE->getElementData(DATABASE->get_player())->handle_2.selecst, hand_2);
	load_eq(DATABASE->getElementData(DATABASE->get_player())->arm.name, DATABASE->getElementData(DATABASE->get_player())->arm.num, DATABASE->getElementData(DATABASE->get_player())->arm.selecst, arm);
	load_eq(DATABASE->getElementData(DATABASE->get_player())->haed.name, DATABASE->getElementData(DATABASE->get_player())->haed.num, DATABASE->getElementData(DATABASE->get_player())->haed.selecst, haed);
	load_eq(DATABASE->getElementData(DATABASE->get_player())->body.name, DATABASE->getElementData(DATABASE->get_player())->body.num, DATABASE->getElementData(DATABASE->get_player())->body.selecst, body);
	load_eq("해체", 2, false, clear);
	_eq[clear].name = "해체";

	_pl.name = DATABASE->getElementData(DATABASE->get_player())->name;
	_pl.att = _eq[hand_1].att + _eq[hand_2].att + set_st(DATABASE->getElementData(DATABASE->get_player())->power,0,0);
	_pl.def = _eq[haed].def + _eq[body].def + _eq[arm].def + set_st(DATABASE->getElementData(DATABASE->get_player())->dex, 0, 0);
	_pl.image = IMAGEMANAGER->findImage(imageName(DATABASE->getElementData(DATABASE->get_player())->job, DATABASE->get_player()+1, true).c_str());
	_count = 0;
	_bag = new bag;
	_bag->init();
	_bag->set_xy(20, 150);
	_select = false;
	return S_OK;
}
void inven_equipment::release(void)
{
	_bag->release();
	SAFE_DELETE(_bag);

}
void inven_equipment::update(void) 
{
	
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (!_select)
		{
			poincoli();
		}
		else
		{
			set_eq();
		}
	}
	//손 구분
	if (!_select)
	{
		key();
		poinrect();
	}
	else
	{
		_bag->update();
	}
	_pl.att = _eq[hand_1].att + _eq[hand_2].att + _eq[haed].att + _eq[body].att + _eq[arm].att + set_st(DATABASE->getElementData(DATABASE->get_player())->power, 0, 0);
	_pl.def = _eq[hand_1].def + _eq[hand_2].def + _eq[haed].def + _eq[body].def + _eq[arm].def + set_st(DATABASE->getElementData(DATABASE->get_player())->dex, 0, 0);

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_select)
		{
			_select = false;
		}
		else
		{
			DATABASE->setElementDataCurrent_arm(_eq[arm].itname, _eq[arm].num, DATABASE->get_player(), _eq[arm].select);
			DATABASE->setElementDataCurrent_handle_1(_eq[hand_1].itname, _eq[hand_1].num, DATABASE->get_player(), _eq[hand_1].select);
			DATABASE->setElementDataCurrent_handle_2(_eq[hand_2].itname, _eq[hand_2].num, DATABASE->get_player(), _eq[hand_2].select);
			DATABASE->setElementDataCurrent_haed(_eq[haed].itname, _eq[haed].num, DATABASE->get_player(), _eq[haed].select);
			DATABASE->setElementDataCurrent_body(_eq[body].itname, _eq[body].num, DATABASE->get_player(), _eq[body].select);
			DATABASE->setElementDataCurrentdef(_pl.def, DATABASE->get_player());
			DATABASE->setElementDataCurrentdef(_pl.att, DATABASE->get_player());
			_bag->save();
			SCENEMANAGER->changeScene("inven");
		}
	}
}
void inven_equipment::render(void) 
{
	char str[123];
	IMAGEMANAGER->findImage("캐릭창")->render(getMemDC(), 20, 0);
	_pl.image->frameRender(getMemDC(), 250, 50);
	sprintf(str, _pl.name.c_str());
	TextOut(getMemDC(), 50, 20, str, strlen(str));
	sprintf(str, "공격력 : %d",_pl.att);
	TextOut(getMemDC(), 250, 20, str, strlen(str));
	sprintf(str, "방어력 : %d", _pl.def);
	TextOut(getMemDC(), 350, 20, str, strlen(str));
	int j = 0;
	int k = 0;
	for (int i = 0; i < end; i++)
	{
		_eq[i].image->frameRender(getMemDC(), 50+280*(j%2), 50+(k*30), _eq[i].frameX, _eq[i].frameY);
		sprintf(str, _eq[i].name.c_str());
		TextOut(getMemDC(), 90 + 280 * (j % 2), 50 + (k * 30), str, strlen(str));
		j++;
		if (j % 2 == 0)
		{
			k++;
		}
	}
	IMAGEMANAGER->findImage("파판손_소")->render(getMemDC(), _x, _y);
	if (_select)
	{
		_bag->render();
	}
}
void inven_equipment::load_eq(string itName, int num,bool select, int eqnum)
{

	char temp[123];
	vector<string>vs;
	vs = TXTDATA->txtLoad("테스/아이탬.txt");
	for (int i = 0; i < vs.size(); i++)
	{
		if (select)
		{
			if (vs[i] == itName&&vs[i+1]==itoa(num,temp,10))
			{
				_eq[eqnum].name =vs[i + 2].c_str();
				_eq[eqnum].att = atoi(vs[i+3].c_str());
				_eq[eqnum].def = atoi(vs[i + 4].c_str());
				_eq[eqnum].frameX = atoi(vs[i + 7].c_str());
				_eq[eqnum].frameY = atoi(vs[i + 8].c_str());
				_eq[eqnum].image = IMAGEMANAGER->findImage("테스트아이탬");
				_eq[eqnum].num = num;
				_eq[eqnum].itname = itName;
				_eq[eqnum].select = true;
				break;
			}
		}
		else
		{
			_eq[eqnum].name = "없음";
			_eq[eqnum].att = NULL;
			_eq[eqnum].def = NULL;//
			_eq[eqnum].frameX = NULL;
			_eq[eqnum].frameY = NULL;
			_eq[eqnum].image = IMAGEMANAGER->findImage("테스트아이탬");
			_eq[eqnum].num = NULL;
			_eq[eqnum].itname= _eq[eqnum].name;
			_eq[eqnum].select = false;
		}
	}
}
void inven_equipment::key(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_count == 0)
		{
			_count -= 2;
			if (_count < 0)
			{
				_count = 0;
			}
		}
		else if (_count == 1)
		{
			_count -= 2;
			if (_count < 1)
			{
				_count = 1;
			}
		}
		else
		{
			_count -= 2;
		}

	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_count == 4)
		{
			_count += 2;
			if (_count > 4)
			{
				_count = 4;
			}
		}
		else if (_count == 5)
		{
			_count += 2;
			if (_count > 5)
			{
				_count = 5;
			}
		}
		else
		{
			_count += 2;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		switch (_count)
		{
		case 0:
			_count = 1;
			break;
		case 2:
			_count = 3;
			break;
		case 4:
			_count = 5;
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		switch (_count)
		{
		case 1:
			_count = 0;
			break;
		case 3:
			_count = 2;
			break;
		case 5:
			_count = 4;
			break;
		}
	}
	switch (_count)
	{
	case hand_1:
		_x = 20;
		_y = 50;
		break;
	case hand_2:
		_x = 20;
		_y = 80;
		break;
	case haed:
		_x = 300;
		_y = 50;
		break;
	case body:
		_x = 300;
		_y = 80;
		break;
	case arm:
		_x = 300;
		_y = 110;
		break;
	case clear:
		_x = 20;
		_y = 110;
		break;
	}
}
void inven_equipment::poinrect(void)
{
	_rc = RectMake(_x, _y, 100, 20);
	int j = 0;
	int k = 0;
	for (int i = 0; i < end; i++)
	{
		_eq[i].rc = RectMake(50 + 280 * (j % 2), 50 + (k * 30), _eq[i].image->getFrameWidth(), _eq[i].image->getFrameHeight());
		j++;
		if (j % 2 == 0)
		{
			k++;
		}
	}
}
void inven_equipment::poincoli(void)
{
	RECT temp;
	for (int i = 0; i < end; i++)
	{
		if (IntersectRect(&temp, &_eq[i].rc, &_rc))
		{
			if (_eq[i].name == "없음")
			{
				_select = true;
			}
			else  if (_eq[i].name == "해체")
			{
				_select = false;
				for (int j = 0; j < end; j++)
				{
					_current_eq = _eq[j];
					if (_current_eq.name == "없음")
					{
						_bag->set_bag(_current_eq.name, _current_eq.num);
					}
					else
					{
						_bag->set_bag(_current_eq.itname, _current_eq.num);
					}
				}
				//초기화
				load_eq("없음", 1, false, hand_1);
				load_eq("없음", 1, false, hand_2);
				load_eq("없음", 1, false, arm);
				load_eq("없음", 1, false, haed);
				load_eq("없음", 1, false, body);
			}
			else
			{
				_current_eq = _eq[i];
				load_eq("1", 1, false, i);
				_select = true;
				if (_current_eq.name == "없음")
				{
					_bag->set_bag(_current_eq.name, _current_eq.num);
				}
				else
				{
					_bag->set_bag(_current_eq.itname, _current_eq.num);
				}
				_current_eq.itname = "없음";
				_current_eq.name = "없음";
				_current_eq.num = NULL;
				_bag->set_currentitem("없음", NULL);
				string s = _bag->get_currentItem().itemName;
			}
		}
	}
}
void inven_equipment::set_eq(void)
{
	if (_eq[_count].select)
	{
		poincoli();
	}
	else if(!_eq[_count].select)
	{
		_bag->set_eq();
		switch (_count)
		{
		case hand_1:
			//손 1에 검과 지팡이 착용가능하다
			if (_bag->get_currentItem().itemName == "검" || _bag->get_currentItem().itemName == "지팡이")
			{
				string s = _bag->get_currentItem().itemName;
				load_eq(_bag->get_currentItem().itemName, _bag->get_currentItem().num, true, _count);
				_bag->set_currentitem("없음", NULL);
			}
			//둘다 아니면 가방으로 돌아가
			else if (_bag->get_currentItem().itemName != "검"&& _bag->get_currentItem().itemName != "지팡이")
			{
				_bag->set_bag(_bag->get_currentItem().itemName, _bag->get_currentItem().num);
				_bag->set_currentitem("없음", NULL);
			}
			break;
		case haed:
			if (_bag->get_currentItem().itemName == "머리")
			{
				load_eq(_bag->get_currentItem().itemName, _bag->get_currentItem().num, true, _count);
				_bag->set_currentitem("없음", NULL);
			}
			else if (_bag->get_currentItem().itemName != "머리")
			{
				_bag->set_bag(_bag->get_currentItem().itemName, _bag->get_currentItem().num);
				_bag->set_currentitem("없음", NULL);
			}
			break;
		case hand_2:
			if (_bag->get_currentItem().itemName == "검"|| _bag->get_currentItem().itemName == "지팡이")
			{
				load_eq(_bag->get_currentItem().itemName, _bag->get_currentItem().num, true, _count);
				_bag->set_currentitem("없음", NULL);
			}
			else if(_bag->get_currentItem().itemName != "검" && _bag->get_currentItem().itemName != "지팡이")
			{
				_bag->set_bag(_bag->get_currentItem().itemName, _bag->get_currentItem().num);
				_bag->set_currentitem("없음", NULL);
			}
			break;
		case body:
			if (_bag->get_currentItem().itemName == "가슴")
			{
				load_eq(_bag->get_currentItem().itemName, _bag->get_currentItem().num, true, _count);
				_bag->set_currentitem("없음", NULL);
			}
			else if (_bag->get_currentItem().itemName != "가슴")
			{
				_bag->set_bag(_bag->get_currentItem().itemName, _bag->get_currentItem().num);
				_bag->set_currentitem("없음", NULL);
			}
			break;
		case arm:
			if (_bag->get_currentItem().itemName == "팔")
			{
				load_eq(_bag->get_currentItem().itemName, _bag->get_currentItem().num, true, _count);
				_bag->set_currentitem("없음", NULL);
			}
			else if (_bag->get_currentItem().itemName != "팔")
			{
				_bag->set_bag(_bag->get_currentItem().itemName, _bag->get_currentItem().num);
				_bag->set_currentitem("없음", NULL);
			}
			break;
		}
		
	}

}