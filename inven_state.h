#pragma once
#include "gameNode.h"
#include "text_box.h"
class inven_state :public gameNode
{

private:
	string _name;
	string _job;
	int _lv;
	int _att;
	int _matt;
	int _def;
	int _mdef;
	int _hp;
	int _mp;
	int _power;
	int _Int;
	int _dex;
	int _wis;
	int _pl;
	int _ex;
	text_box* _text_box;
	text_draw_c* _text;
	int _handle_1;
	int _handle_2;
	int _arm;
	int _haed;
	int _body;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void set_init(void);
	
	inven_state();
	~inven_state();
};

