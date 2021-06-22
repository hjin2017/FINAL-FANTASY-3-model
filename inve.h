#pragma once
#include "gameNode.h"
#include"text_box.h"
class inve :public gameNode
{
	enum mymenu
	{
		tool,
		spell,
		equipment,
		state,
		move,
		job,
		save,
		gold,
		end
	};
	struct tagplay
	{
		image* image;
		int mp, hp, maxhp,maxmp;
		string name;
		string job;
		bool move;
	};
private:
	image* _image;
	text_draw_c* _text;
	int _count, _pcount;
	int _y2,_y,_glod;
	bool _select;
	string str_menu[end] = { "도구","마법","장비","상태","이동","직업","저장","골드" };
	tagplay _p[4];
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void set_pointer(void);
	void set_character(void);
	void character_draw(void);
	void set_select(void);
	inve();
	~inve();
};

