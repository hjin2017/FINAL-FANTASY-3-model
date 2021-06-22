#pragma once
#include "gameNode.h"
#include "Save_load.h"

class bag :public gameNode
{
	struct tagbag
	{
		image* image;
		int count;
		string name;
		RECT rc;
		int frameX, frameY;
		int def, att, hp, mp;
		string itemName;
		int num;
	};

	typedef vector<tagbag> bagV;
private:
	Save_load_bag* _Save_load_bag;
	bagV _bag;
	RECT _rc;
	image* _image;
	int _countX,_countY,_x,_y;
	bool select;
	tagbag current_bag;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void set_bag(string itemName, int num);
	void use_potion(void);
	void set_eq(void);
	void save(void);
	void load(void);
	tagbag get_currentItem(void) { return current_bag; }
	inline void set_currentitem(string s, int n) { current_bag.itemName = s; current_bag.num = n; }
	inline void set_xy(int x, int y) { _x = x; _y = y; }
	bag();
	~bag();
};

