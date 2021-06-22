#pragma once
#include "gameNode.h"
#include "text_box.h"
class salesman_scene :public gameNode
{
	enum itemName
	{
		ite_weapon,
		ite_armor,
		ite_portion,
		ite_spell
	};
	enum direction_salesman
	{
		dr_buy,
		dr_sale,
		dr_exit,
	};
	struct tagitem
	{
		string itemName;
		string Name;
		int itnum, att, def, hp, mp, framex, framey,gold ,itcount;
		image* iamge;

		RECT rc;
	};

	typedef vector<tagitem*> itemv;
	typedef vector<tagitem*>::iterator itemvi;
	typedef vector<tagitem*> vbag;
	typedef vector<tagitem*>::iterator vibag;
private:
	RECT _rc;
	itemv _itv;
	itemvi _itiv;
	vbag _vabg;
	vibag _vibag;
	text_box_M* _tbx;
	text_draw_c* _text_draw_c;
	int _count;
	int _pcount;
	int _salecount;
	int _dr_x, item_count;
	bool _dr_select;
	int _gold;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void set_item(void);
	void text_draw(void);
	void item_update(void);
	void item_draw(void);
	void select_item(void);
	void set_bag(string itemName, int inum);
	void init_bag(void);
	void draw_bag(void);
	void update_bag(void);
	void del_bag(string itemName, int inum);
	salesman_scene();
	~salesman_scene();
};

