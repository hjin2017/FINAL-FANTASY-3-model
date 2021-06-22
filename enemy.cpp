#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(void)
{
	set_up();
	return S_OK;
}

void enemy::release(void)
{
	SAFE_DELETE(_enemy);	
}

void enemy::update(void)
{
	udate_turn();

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_turn_stop = true;
		for (int i = 0; i < enmax; i++)
		{
			if (_enemy[i].framey == 0)continue;
			_enemy[i].framey = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_turn_stop = false;
	}
}

void enemy::render(void)
{
	char str[123];
	for (int i = 0; i < enmax; i++)
	{
		if (!_enemy[i].life)continue;
		IMAGEMANAGER->findImage(_enemy[i].imageName)->frameRender(getMemDC(),
			_enemy[i].x + en_x,
			_enemy[i].y + en_y,
			_enemy[i].framex,
			_enemy[i].framey / 2.5);
	}
	for (int i = 0;i < kind; i++)
	{
		_txt.text_draw(60,30*i+430,_Name[i].c_str(),20);
	}
}
void enemy::udate_turn(void)
{    
	if (!_turn_stop)
	{
		//������ �������̸�
		if (_enemy[icount].num == _enmeynum && _enemy[icount].turn)
		{
			//����� ���� ���̸� ������
			_enemy[icount].framey++;
			if (_enemy[icount].framey == 10)
			{
				_enemy[icount].framey = 0;
				_enemy[icount].turn = false;
				_enmeynum = RND->getInt(enmax);
				_turncount++;
				icount = 0;
				_turn_stop = true;
			}
		}//������ �������� �ƴϰ� ���� �ʳ�������
		else if (_enemy[icount].num == _enmeynum && !_enemy[icount].turn&&_turncount != enmax)
		{//������ �������� �ƴϸ� ã��
			int i = 0;
			while (!_enemy[_enmeynum].turn)
			{
				if (!_enemy[_enmeynum].turn)i++;
				//���� ������
				_enmeynum = RND->getInt(enmax);
				// �� �迭�� ���� Ȱ���� ���Ѱ� ã���� ����
				if (_enemy[_enmeynum].turn)break;
				if (i == enmax)break;
			}
			icount = 0;
		}//���� �� ����ϸ� �ʱ�ȭ
		else if (_turncount == enmax)
		{
			_turn_stop = true;
			icount = 0;
			_enmeynum = RND->getInt(enmax) ;
			_turncount = 0;
			for (int i = 0; i < enmax; i++)
			{
				_enemy[i].turn = true;
			}
		}//�̵� ���� �ƴϸ� ī��Ʈ++
		else
		{
			_enemy[icount].framey = 0;
			icount++;
			if (icount == enmax)
			{
				icount = 0;
			}
		}
	}
}
void enemy::set_up(void)
{
	//���ʹ� �����Ҵ�
	//enx = RND->getFromIntTo(1, 5);
	//eny = RND->getFromIntTo(1, 3);
	enx = 5;
	eny = 1;
	enmax = enx*eny;
	_enemy = new tagenemy[enmax];
	//�ʱ�ȭ
	_enmeynum = RND->getInt(enmax);
	icount = 0;
	_turncount = 0;
	_turn_stop = true;
	//�ڸ����
	int q = 0;
	int rnd = RND->getInt(kind);
	for (int i = 0; i < eny; i++)
	{
		for (int j = 0; j < enx; j++)
		{
			_enemy[i*enx + j].x = 65 * j;
			_enemy[i*enx + j].y = 100 * i;
			_enemy[i*enx + j].num = q;
			q++;
		}
	}
	//���ʹ� �������� �Ӽ��ޱ�
	q = 0;
	vector<string> vs;
	string simagName = "enemy";
	vs = TXTDATA->txtLoad("�׽�/b_enemy.txt");
	for (int i = 0; i < enmax; i++)
	{
		for (int j = 0; j < vs.size(); j++)
		{//�Ӽ��ޱ�

			if (vs[j] == "/"&& atoi(vs[j + 2].c_str()) == rnd&&atoi(vs[j + 1].c_str()) == _num)
			{
				_enemy[i].framex = atoi(vs[j + 7].c_str());
				_enemy[i].framey = atoi(vs[j + 8].c_str());
				_enemy[i].imageName = simagName + vs[j + 1];
				_enemy[i].name = vs[j + 3];
				_enemy[i].att = atoi(vs[j + 4].c_str());
				_enemy[i].def = atoi(vs[j + 5].c_str());
				_enemy[i].hp = atoi(vs[j + 6].c_str());
				_enemy[i].turn = true;
				_enemy[i].life = true;
				rnd = RND->getInt(kind);
				break;
			}
		}
		//�̸� â�� ���� ���
		bool stop = false;
		for (int k = 0; k < q + 1; k++)
		{//����ִ� �Ӽ��� ���� �Ӽ������� ��ħ �ƴϸ� ���� ����
			if (_Name[k] != _enemy[i].name)continue;
			stop = true;
			break;
		}
		//������ �������� 
		if (stop)continue;
		//�̸� â�� �̸��� ����
		_Name[q] = _enemy[i].name;
		q++;
	}
	//����
	string	temp;
	while (true)
	{
		if (_Name[1].size() == 0)break;
		bool stop = true;

		for (int i = 0; i < kind; i++)
		{
			//���̸� ����
			if (i == kind - 1)break;
			//������ ū�� �ڿ������� ������ ����
			if (_Name[i].size() < _Name[i + 1].size())
			{
				temp = _Name[i];
				_Name[i] = _Name[i + 1];
				_Name[i + 1] = temp;
				//���
				stop = false;
			}
		}
		//����
		if (stop)break;
	}
	switch (eny)
	{
	case eny_one:
		en_y = 200;
		break;
	case eny_two:
		en_y = 150;
		break;
	case eny_three:
		en_y = 100;
		break;
	}
	switch (enx)
	{
	case enx_one:
		en_x = 200;
		break;
	case enx_two:
		en_x = 200;
		break;
	case enx_three:
		en_x = 150;
		break;
	case enx_four:
		en_x = 100;
		break;
	case enx_five:
		en_x = 50;
		break;
	}
}