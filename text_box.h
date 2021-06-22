#pragma once
#include "gameNode.h"
class text_box :public gameNode
{
private:
	int _x, _y, _tx, _ty, _fontsize;
	string _k;
	string _s;
public:
	virtual HRESULT init(string str,string fileName, int w, int h);
	virtual void render(void);
	void text_box_draw(void);
	void set_text_box_op(int x, int y, int tx, int ty, string s, int fontsize);
	text_box();
	~text_box();
};
class text_box_M :public gameNode
{
	typedef vector<text_box*> vb;
	typedef vector<text_box*>::iterator vib;
private:
	vb _vb;
	vib _vib;
public:
	virtual HRESULT init();
	virtual void render(void);
	virtual void release(void);
	void set_text_box(string key,int w, int h, int x, int y, int tx, int ty, string s, int fontsize);
	void removeall(void);
	text_box_M();
	~text_box_M();
};
class text_draw_c :public gameNode
{
private:

public:
	void text_draw(int x, int y, string s, int fontsize);
	void text_draw_int(int x, int y, string s, int num, int fontsize);
	text_draw_c();
	~text_draw_c();
};
