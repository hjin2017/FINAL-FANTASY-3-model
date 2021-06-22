#pragma once
#include "gameNode.h"
class drag :public gameNode
{
private:

	bool isdrag;
	RECT drag_rc;
	int _x;
	int _y;
	POINT _first;
	POINT _END;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void setdrag(void);
	void set_firstX(int i){}
	 void _isdrag(bool b) { isdrag= b; }

	inline int get_x(void) { return _x; }
	inline int get_y(void) { return _y; }
	void set_first(POINT first) { _first = first; }
	void set_END(POINT end) { _END = end; }
	inline POINT get_first(void) { return _first; }
	inline POINT get_end(void) { return _END; }
	drag();
	~drag();
};