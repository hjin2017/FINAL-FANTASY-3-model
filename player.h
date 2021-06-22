#pragma once
#include "gameNode.h"
class player : public gameNode
{
	enum PR
	{
		PR_DOWN,
		PR_LEFT,
		PR_UP,
		PR_RIGHT
	};

private:
	image* _image;
	int _count,_pcount;
	PR _pr;
	int _fameY;
	int _x, _y;
	RECT _rc;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void move(void);
	void job(string job,int num);

	inline int get_x(void) { return _x; }
	inline int get_y(void) { return _y; }
	inline RECT get_rc(void) { return _rc; }
	inline PR get_pr(void) { return _pr; }
	void set_x(int a) { _x = a; }
	void set_y(int a) { _y = a; }
	
	player();
	~player();
};

