#pragma once
#include "gameNode.h"
#include "bag.h"
class inven_equipment :public gameNode
{
	struct tagplayer_eq
	{
		int att, def;
		string name;
		string itname;
		bool select;
		int frameX, frameY;
		image* image;
		RECT rc;
		int num;
	};
	enum eq
	{
		hand_1,
		haed,
		hand_2,
		body,
		clear,
		arm,
		end
	};
private:
	bag* _bag;
	RECT _rc;
	tagplayer_eq _eq[end];
	tagplayer_eq _pl;
	int _x, _y;
	bool _select;
	bool _clear;
	int _count;
	tagplayer_eq _current_eq;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void load_eq(string itName, int num, bool select, int eqnum);
	void key(void);
	void poinrect(void);
	void poincoli(void);
	void set_eq(void);
	inven_equipment();
	~inven_equipment();
};

