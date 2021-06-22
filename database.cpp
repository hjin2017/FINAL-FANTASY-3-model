#include "stdafx.h"
#include "database.h"


database::database()
{
}


database::~database()
{

}

HRESULT database::init()
{
	_pos.x = 0;
	_pos.y = 0;
	_gold = 0;
	_salesman = 0;
	_itemLV = 0;
	_map_num = 0;
	loadDatabase("테스/잡.txt");
	return S_OK;
}

void database::release()
{

}


void database::loadDatabase(string name)
{
	vs vTemp;
	vTemp = TXTDATA->txtLoad("테스/잡.txt");
	char temp[500];
	ZeroMemory(temp, sizeof(temp));
	int power;
	int Int;
	int dex;
	int wis;

	for (int j = 0; j < vTemp.size(); j++)
	{
		if (vTemp[j] == "검사")
		{
			power = atoi(vTemp[j + 1].c_str());
			dex = atoi(vTemp[j + 2].c_str());
			Int = atoi(vTemp[j + 3].c_str());
			wis = atoi(vTemp[j + 4].c_str());
		}
	}
	for (int i = 0; i < 4; i++)
	{
		elements* em = new elements;
		_mTotalElement.insert(pair<int, elements*>(i, em));

		iterElement mIter = _mTotalElement.find(i);

		mIter->second->job = "검사";
		mIter->second->lv = 1;
		mIter->second->name = mIter->second->job;
		mIter->second->name += "_";
		mIter->second->name += itoa(i, temp,10);
		mIter->second->power = power;
		mIter->second->dex = dex;
		mIter->second->Int = Int;
		mIter->second->wis = wis;
		mIter->second->hp = set_st(mIter->second->power, mIter->second->dex, mIter->second->Int);
		mIter->second->mp = set_st(mIter->second->wis, mIter->second->Int, mIter->second->dex);
		mIter->second->pos = false;
		mIter->second->haed.selecst = false;
		mIter->second->handle_1.selecst = false;
		mIter->second->handle_2.selecst = false;
		mIter->second->body.selecst = false;
		mIter->second->arm.selecst = false;
		mIter->second->ex = 0;
		mIter->second->def = 0;
		mIter->second->att = 0;

	}
	vTemp.clear();
}

//설정자
bool database::setElementDataCurrentHP(int hp, int p)
{
	iterElement mIter = _mTotalElement.find(p);
	mIter->second->hp = hp;
	if (mIter->second->hp < 0) return false;
	else return true;
		
}

bool database::setElementDataCurrentMP(int mp, int p)			   
{
	iterElement mIter = _mTotalElement.find(p);
	mIter->second->mp = mp;
	if (mIter->second->hp < 0) return false;
	else return true;
}
void database::setElementDataCurrentEX(int ex, int p)
{
	iterElement mIter = _mTotalElement.find(p);
	mIter->second->lv = ex;
}
void database::setElementDataCurrentLV(int lv, int p)			   
{
	iterElement mIter = _mTotalElement.find(p);
	mIter->second->lv += lv;

}

void database::setElementDataCurrent_job(string job, int p)		   
{
	iterElement mIter = _mTotalElement.find(p);
	mIter->second->job = job;

}
void database::setElementDataCurrent_name(string name, int p)	   
{
	iterElement mIter = _mTotalElement.find(p);

	mIter->second->name = name;
}
void database::setElementDataCurrentatt(int att, int p)
{
	iterElement mIter = _mTotalElement.find(p);

	mIter->second->att = att;
}
void database::setElementDataCurrentdef(int def, int p)
{
	iterElement mIter = _mTotalElement.find(p);

	mIter->second->def = def;
}

void database::setElementDataCurrent_handle_1(string handle_1,int itnum, int p, bool select)
{
	iterElement mIter = _mTotalElement.find(p);
	mIter->second->handle_1.name = handle_1;
	mIter->second->handle_1.num = itnum;
	mIter->second->handle_1.selecst = select;
}
void database::setElementDataCurrent_handle_2(string handle_2, int itnum, int p, bool select)
{
	iterElement mIter = _mTotalElement.find(p);
	mIter->second->handle_2.name = handle_2;
	mIter->second->handle_2.num = itnum;
	mIter->second->handle_2.selecst = select;
}
void database::setElementDataCurrent_haed(string haed, int itnum, int p, bool select)
{
	iterElement mIter = _mTotalElement.find(p);
	mIter->second->haed.name = haed;
	mIter->second->haed.num = itnum;
	mIter->second->haed.selecst = select;
}
void database::setElementDataCurrent_arm(string arm, int itnum, int p, bool select)
{
	iterElement mIter = _mTotalElement.find(p);
	mIter->second->arm.name = arm;
	mIter->second->arm.num = itnum;
	mIter->second->arm.selecst = select;
}
void database::setElementDataCurrent_body(string body, int itnum, int p, bool select)
{
	iterElement mIter = _mTotalElement.find(p);
	mIter->second->body.name = body;
	mIter->second->body.num = itnum;
	mIter->second->body.selecst = select;
}
void database::setElementDataCurrent_pos(bool pos, int p)
{
	iterElement mIter = _mTotalElement.find(p);
	mIter->second->pos = pos;
}
