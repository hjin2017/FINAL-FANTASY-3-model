#pragma once
#include "gameNode.h"

class button : public gameNode
{
private:
	string _imageName;
	string _direction;
	RECT _rc;
	int _x, _y;
	int _framex, _framey;
	bool _select;
	int _num;
	int centerx, centery;
public:
	HRESULT init(string imageName, int x, int y,int cx,int cy, string direction, int num);
	void release();
	void update();
	void render();
	void set_slect(bool b) { _select = b; }
	inline bool get_select(void) { return _select; }
	inline int get_num(void) { return _num; }
	inline RECT get_rc(void) { return _rc; }


	button();
	~button();
};

