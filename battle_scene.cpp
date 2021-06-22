#include "stdafx.h"
#include "battle_scene.h"


battle_scene::battle_scene()
{
}


battle_scene::~battle_scene()
{
}
HRESULT battle_scene::init(void)
{
	SetWindowPos(_hWnd, NULL, 0, 0, 600, 600, SWP_NOMOVE);
	_enemy = new enemy;
	_enemy->set_num(0);//배틀넘 입력
	_enemy->init();
	_pl = new b_player;
	_pl->init();
	_select = false;
	_plcount = em_count = 0;
	_turn = true;
	_die = false;
	entrun_count = 0;
	for (int i = 0; i < 4; i++)
	{
		i_temp[i] = 0;
	}
	
	return S_OK;
}
void battle_scene::release(void)
{
	SAFE_DELETE(_enemy);	
	SAFE_RELEASE(_enemy);
	SAFE_DELETE(_pl);
	SAFE_RELEASE(_pl);
}
void battle_scene::update(void)	
{
	pl_trun_dr();
	_enemy->update();
	_pl->update();
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_select) _selectcount=move_count(_selectcount, dr_att, dr_mig, -1);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_select) _selectcount = move_count(_selectcount, -dr_mig, dr_att, 1);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_select)
		{
			em_count = move_count(em_count, 0, _enemy->get_enmax() - 1, -1);
			if (!_enemy->get_temp()[em_count].life)
			{
				em_count = move_count(em_count, 0, _enemy->get_enmax() - 1, -1);
			}
		}

	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_select)
		{
			em_count = move_count(em_count, -_enemy->get_enmax() + 1, 0, 1);
			if (!_enemy->get_temp()[em_count].life)
			{
				em_count = move_count(em_count, -_enemy->get_enmax() + 1, 0, 1);
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		while (!_pl->get_pl()[_plcount].life)
		{
			_pl->set_trun(_plcount, true);
			_plcount++;
			if (_plcount == 4)
			{
				_plcount = 3;
				break;
			}
		}
		if (!_pl->get_pl()[_plcount].turn&& _pl->get_pl()[_plcount].life)
		{
			_select = true;
			_pl->set_trun(_plcount, true);
			_selectcount = 0;
		}
		else if (_pl->get_pl()[_plcount].turn&& _pl->get_pl()[_plcount].life)
		{
			_pl->set_str(_plcount, pl_trun_dr());
			i_temp[_plcount] = _enemy->get_temp()[em_count].num;
			_plcount++;
			_select = false;
			if (_plcount == 4)
			{
				_pl->set_turn_count(_plcount - 1);
				_plcount = 0; 
				_turn = true;
			}
		}
	}
	
	if (!_enemy->get_temp()[em_count].life)
	{
		em_count = move_count(em_count, -_enemy->get_enmax() + 1, 0, 1);
	}
	
	trun_a();

	int j = 0;
	for (int i = 0; i < _enemy->get_enmax(); i++)
	{
		if (_enemy->get_temp()[i].life)
		{
			j++;
		}
	}
	if (j == 0)SCENEMANAGER->changeScene("play");// 득 클래스 만들고 그거끝나면 씬전 환 하도록 하기 방어 스킬 도주 만들기

	if(_die)
		SCENEMANAGER->changeScene("메뉴");//다이 씬 제작 하쟈
}
void battle_scene::render(void)	
{
	IMAGEMANAGER->findImage("전투지역")->frameRender(getMemDC(), 0, 0,0,1);

	if (_select)
	{
		_enemy->render();
		IMAGEMANAGER->findImage("말4")->render(getMemDC(), 10, 410);
		pl_trun_txt();
		en_temp();
	}
	else
	{
		IMAGEMANAGER->findImage("말4")->render(getMemDC(), 10, 410);
		_enemy->render();
	}

	IMAGEMANAGER->findImage("말3")->render(getMemDC(), 210, 410);
	_pl->render();
	
}
void battle_scene::pl_trun_txt(void)
{
		_txt.text_draw(80, 415, "공격", 20);
		_txt.text_draw(80, 445, "방어", 20);
		_txt.text_draw(80, 475, "도주", 20);
		_txt.text_draw(80, 505, "가방", 20);
	    _txt.text_draw(80, 535, "마법", 20);
		IMAGEMANAGER->findImage("파판손_소")->render(getMemDC(), _plh.x, _plh.y);
}
string battle_scene::pl_trun_dr(void)
{
	string str;
	if (_select)
	{
		switch (_selectcount)
		{
		case dr_att:
			str = "공격";
			_plh.x = 50;
			_plh.y = 415;
			break;
		case dr_def:
			str = "방어";
			_plh.x = 50;
			_plh.y = 445;
			break;
		case dr_run:
			str = "도망";
			_plh.x = 50;
			_plh.y = 475;
			break;
		case dr_bag:
			str = "가방";
			_plh.x = 50;
			_plh.y = 505;
			break;
		case dr_mig:
			str = "마법";
			_plh.x = 50;
			_plh.y = 535;
			break;
		}
	}
	return str;
}
void battle_scene::pl_att(int i)
{
	int a = _enemy->get_temp()[i].def;
	int b = _pl->get_pl()[_plcount].att;
	int sun = a - b;
	if (sun > 0)
	{
		sun = -20;
		_enemy->set_turn(i, false);
	}
	_enemy->set_hp(i, sun);
	if (_enemy->get_temp()[i].hp < 0)
	{
		_enemy->set_life(i, false);
	}
}
void battle_scene::en_temp(void)
{
	IMAGEMANAGER->findImage("파판손_소")->render(getMemDC(),
		_enemy->get_temp()[em_count].x + _enemy->get_e_x() ,
		_enemy->get_temp()[em_count].y + _enemy->get_e_y());
}
void battle_scene::trun_a(void)
{
	if (_turn)
	{	//사람 움직여
		if ( _plcount != 4 && _pl->get_pl()[_plcount].str == "공격")//여기서 공방 활동
		{
			if (_pl->pl_turn_move(_plcount))return;
			_pl->set_trun(_plcount, false);
			pl_att(i_temp[_plcount]);
			_plcount++;
			if (_plcount == 4)
			{
				_plcount = 0;
				_turn = false;
				return;
			}
			if (!_enemy->get_temp()[i_temp[_plcount]].life)
			{
				int i = 0;
				while (i != _enemy->get_enmax())
				{
					if (!_enemy->get_temp()[i].life)i++;
					else if (_enemy->get_temp()[i].life)
					{
						i_temp[_plcount] = i;
						break;
					}
				}
			}
		}
		else if (_plcount != 4 && _pl->get_pl()[_plcount].str == "방어")
		{
			_pl->set_trun(_plcount, false);
			_plcount++;
			if (_plcount == 4)
			{
				_plcount = 0;
				_turn = false;
				return;
			}
		}

	}
	else if(!_turn&& _enemy->get_turn())
	{
		int j = 0;
		for (int i = 0; i < _enemy->get_enmax(); i++)
		{
			if (!_enemy->get_temp()[i].life) j++;
	    }
		entrun_count=entrun_count + j;

		if (entrun_count == _enemy->get_enmax())
		{//초기화
			_turn = true;
			_plcount = 0;
			_select = false;
			_pl->set_turn_count(0);

			for (int i = 0; i < _enemy->get_enmax(); i++)
			{
				if (!_enemy->get_temp()[i].life)continue;
				_enemy->set_turn(i, true);
			}
		}
		else if (entrun_count != _enemy->get_enmax())
		{
			entrun_count++;
			entrun_count -= j;
			em_att();
			_enemy->set_turn_stop(false);
		}
	}
}
void battle_scene::em_att(void)
{
	int i= RND->getInt(4);
	while (!_pl->get_pl()[i].life)
	{
		i = RND->getInt(4); 
		if (_pl->get_pl()[i].life)break;

		int k = 0;
		for (int j = 0; j < 4; j++)
		{
			if (_pl->get_pl()[j].life)continue;
			k++;
		}
		if (k == 4)
		{
			_die = true; break;
		}
	}
	if (_enemy->get_turn() && !_enemy->get_temp()[_enemy->get_icount()].life)
	{
		int j = 0;
		while (true)
		{
			if (!_enemy->get_temp()[j].turn)j++;
			else if (_enemy->get_temp()[j].turn)
			{
				break;
			}
			if (j == _enemy->get_enmax())break;
		}
		int a = _enemy->get_temp()[j].att;
		int b = _pl->get_pl()[i].def;
		int sun = a - b;
		if (sun > 0)
		{
			sun = -20;
		}
		_pl->set_hp(i, sun);
		if (_pl->get_pl()[i].hp < 0)
		{
			_pl->set_life(i, false);
		}
	}
	else if (_enemy->get_turn()&& _enemy->get_temp()[_enemy->get_icount()].life)
	{
		int a = _enemy->get_temp()[_enemy->get_icount()].att;
		int b = _pl->get_pl()[i].def;
		int sun = a - b;
		if (sun > 0)
		{
			sun = -20;
		}
		_pl->set_hp(i, sun);
		if (_pl->get_pl()[i].hp < 0)
		{
			_pl->set_life(i, false);
		}
	}

	int k = 0;
	for (int j = 0; j < 4; j++)
	{
		if (_pl->get_pl()[j].life)
		{
			k++;
		}
	}
	if (k == 0)
	{
		_die = true; 
	}

	//승리 표시와 뒤짐 표시 작업 남음
}