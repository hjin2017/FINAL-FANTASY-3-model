#pragma once
#include "gameNode.h"
class character_hp_mp :public gameNode
{
	struct tagpl_hp
	{
		int hp;
		int maxhp;
		string name;
		int lv;
		image* image;
	};
private:
	image*_image;
	tagpl_hp _pl[4];
	int _x, _y;
	int _pcount;
	int _pointerX, _pointerY;
	bool _select;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	inline void set_x_y(int x, int y) { _x = x; _y = y; }
	inline void set_select(bool b) {  _select=b; }
	inline tagpl_hp get_hp(int i) { return _pl[i]; }
	void set_hp(int h);
	character_hp_mp();
	~character_hp_mp();
};

