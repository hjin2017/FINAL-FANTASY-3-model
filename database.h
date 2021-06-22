#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class elements
{

public:
	struct tageq
	{
		string name;
		int num;
		bool selecst;
	};
	string name;
	string job;
	int lv;
	int att;
	int matt;
	int def;
	int mdef;
	int hp;
	int mp;
	int power;
	int Int;
	int dex;
	int wis;
	int ex;
	tageq handle_1;
	tageq handle_2;
	tageq haed;
	tageq arm;
	tageq body;
	bool pos;

	elements(){};
	~elements(){};
};


class database : public singletonBase<database>
{
private:
	typedef vector<string> vs;
	typedef vector<string>::iterator vis;
	typedef map<int, elements*> arrElement;
	typedef map<int, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;
	POINT _pos;
	int _gold;
	int _player;
	int _salesman;
	int _itemLV;
	int _map_num;
public:
	HRESULT init();
	void release();

	void loadDatabase(string name);

	//접근자
	elements* getElementData(int num) { return _mTotalElement.find(num)->second; }

	//설정자
	bool setElementDataCurrentHP(int hp, int p);
	bool setElementDataCurrentMP(int mp, int p);
	void setElementDataCurrentEX(int ex, int p);
	void setElementDataCurrentLV(int lv, int p);
	void setElementDataCurrentatt(int att, int p);
	void setElementDataCurrentdef(int def, int p);
	void setElementDataCurrent_pos(bool pos, int p);
	void setElementDataCurrent_job(string job, int p);
	void setElementDataCurrent_name(string name, int p);
	void setElementDataCurrent_handle_1(string handle_1, int itnum, int p,bool select);
	void setElementDataCurrent_handle_2(string handle_2, int itnum, int p, bool select);
	void setElementDataCurrent_haed(string haed, int itnum, int p, bool select);
	void setElementDataCurrent_arm(string arm, int itnum, int p, bool select);
	void setElementDataCurrent_body(string body, int itnum, int p, bool select);

	void setpos(POINT pos) { _pos = pos; }
	POINT getpos() { return _pos; }
	void set_gold(int gold) { _gold = gold; }
	inline int get_gold(void) { return _gold; }
	void set_map_num(int map_num) { _map_num = map_num; }
	inline int get_map_num(void) { return _map_num; }
	void set_player(int player) { _player = player; }
	inline int get_player(void) { return _player; }
	void set_salesman(int salesman,int itemlv){_salesman = salesman; _itemLV = itemlv;}
	inline int get_salesman(void) { return _salesman; }
	inline int get_itemLV(void) { return _itemLV; }
	database();
	~database();
};

