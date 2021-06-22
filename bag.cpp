#include "stdafx.h"
#include "bag.h"


bag::bag()
{
}


bag::~bag()
{
}
HRESULT bag::init(void)
{
	_image = IMAGEMANAGER->findImage("���Ǽ�_��");
	_countY = _countX = 0;
	_Save_load_bag = new Save_load_bag;
	_Save_load_bag->init();
	load();
	return S_OK;
}
void bag::release(void)
{
	SAFE_DELETE(_Save_load_bag);
	_bag.clear();

}
void bag::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_countY--;
		if (_countY < 0)
		{
			_countY = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_countY++;
		if (_countY > 6)
		{
			_countY = 6;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_countX = 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_countX = 0;
	}

		int j = 0;
		int k = 0;
		for (int i = 0; i < _bag.size(); i++)
		{
			_bag[i].rc = RectMake((_x + 30) + j % 2 * 280, (_y + 20) + k * 40, _bag[i].image->getFrameWidth(), _bag[i].image->getFrameHeight());
			j++;
			if (j % 2 == 0)
			{
				k++;
			}
		}
		_rc = RectMake((_x)+_countX * 280, (20 + _y) + _countY * 40, 100, _image->getHeight());
}
void bag::render(void)
{
	IMAGEMANAGER->findImage("�����Ƹ޴�")->render(getMemDC(), _x, _y);
	_image->render(getMemDC(), _x+_countX*280, (20+_y)+_countY*40);
	char str[123];
	for (int i = 0; i < _bag.size(); i++)
	{
		_bag[i].image->frameRender(getMemDC(), _bag[i].rc.left, _bag[i].rc.top,_bag[i].frameX,_bag[i].frameY);
		
		sprintf(str,_bag[i].name.c_str());
		TextOut(getMemDC(), _bag[i].rc.left + 40, _bag[i].rc.top, str, strlen(str));
		sprintf(str, "���� : %d", _bag[i].count);
		TextOut(getMemDC(), _bag[i].rc.left + 120, _bag[i].rc.top, str, strlen(str));
	}

}
void bag::set_bag(string itemName, int num)
{
	char temp[128];
	bool stop = false;
	vector<string> vs;
	string str;
	vs = TXTDATA->txtLoad("�׽�/������.txt");
	for (int i = 0; i < vs.size(); i++)
	{
		//�̸��� �ѹ��� ���� �ؽ�Ʈ�� ã�Ƽ�
		if ((vs[i] == itemName) && vs[i + 1] == itoa(num, temp, 10))
		{
			//�� �̸���
			str = vs[i + 2];
			for (int j = 0; j < _bag.size(); j++)
			{
				//���濡 ���� �̸��� ���°� ����?
				if (_bag[j].name == str)
				{
					//ī��Ʈ�� ������
					_bag[j].count++;
					//������
					stop = true;
					break;
				}
			}
			// ���� �� ������
			if (!stop)
			{
				//�����
				tagbag bg;
				bg.count = 1;
				bg.image = IMAGEMANAGER->findImage("�׽�Ʈ������");
				bg.frameX=(atoi(vs[i + 7].c_str()));
				bg.frameY=(atoi(vs[i + 8].c_str()));
				bg.name = vs[i+2];
				bg.att = atoi(vs[i + 3].c_str());
				bg.def = atoi(vs[i + 4].c_str());
				bg.hp = atoi(vs[i + 5].c_str());
				bg.mp = atoi(vs[i + 6].c_str());
				bg.itemName = itemName;
				bg.num = num;
				_bag.push_back(bg);
				break;
			}
		}
	}
	vs.clear();
}
void bag::save(void)
{
	for (int i = 0; i < _bag.size(); i++)
	{
		_Save_load_bag->bag_save(_bag[i].itemName, _bag[i].num, _bag[i].count);
	}	
}
void bag::load(void)
{
	vector<string>vs;
	vs = TXTDATA->txtLoad("�׽�/����.txt");
	for (int i = 0; i < vs.size(); i++)
	{
		// /�̰� ��������
		if (vs[i] == "/")
		{
			// 3��° �Ӽ��� ������ŭ 
			for (int j = 0; j < atoi(vs[i + 3].c_str()); j++)
			{
				//�ݺ��ؼ� ���濡 �־���
				set_bag(vs[i+1].c_str(), atoi(vs[i + 2].c_str()));
			}
		}
	}
	vs.clear();
}
void bag::use_potion(void)
{
	string s;
	for (int i = 0; i < _bag.size(); i++)
	{
		s = _bag[i].itemName;
		RECT rc;
		//���� �̳�
		if (s == "����" && IntersectRect(&rc, &_bag[i].rc, &_rc))
		{
			//Ŀ��Ʈ�� �ȱ��
			current_bag.att = _bag[i].att;
			current_bag.def = _bag[i].def;
			current_bag.frameX = _bag[i].frameX;
			current_bag.frameY = _bag[i].frameY;
			current_bag.hp = _bag[i].hp;
			current_bag.mp = _bag[i].mp;
			current_bag.name = _bag[i].name;
			current_bag.image = _bag[i].image;
			current_bag.itemName = _bag[i].itemName;
			//���� ����
			if (_bag[i].count < 2)
			{
				_bag.erase(_bag.begin() + i);
				_Save_load_bag->bag_save("����", NULL, 0);
			}
			else  _bag[i].count--;
		}
	}
	s.clear();
}
void bag::set_eq(void)
{
	string s;
	for (int i = 0; i < _bag.size(); i++)
	{
		s = _bag[i].itemName;
		RECT rc;
		//������ �ƴϸ� �����
		if (s != "����" &&IntersectRect(&rc, &_bag[i].rc, &_rc))
		{
			//Ŀ��Ʈ�� �ȱ��
			current_bag.itemName = _bag[i].itemName;
			current_bag.num = _bag[i].num;
			//���� ����
			if (_bag[i].count < 2)
			{
				_bag.erase(_bag.begin() + i);
				_Save_load_bag->bag_save("����", NULL, 0);
			}
			else  _bag[i].count--;
		}
	}
	s.clear();
}