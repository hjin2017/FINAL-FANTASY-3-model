#pragma once
#include "gameNode.h"
#include "text_box.h"
class b_player :public gameNode
{
	struct tagplayer
	{
		string name;
		string imageName;
		string str;
		int att, def, hp,hpmax;
		int framex, framey, x, y;
		int num;
		bool turn;
		bool life;
	};

private:
	tagplayer _pl[4];
	text_draw_c _txt;
	int pl_count;
	int turn_count;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void set_trun(int i, bool turn) { _pl[i].turn = turn; }
	void set_str(int i, string str) { _pl[i].str = str; }
	void pl_state_draw(void);
	void pl_init(void);
	bool pl_turn_move(int i);
	void set_turn_count(int i) { turn_count = i; }
	inline tagplayer* get_pl(void) { return _pl; }
	void set_hp(int i, int hp) { _pl[i].hp += hp; }
	void set_life(int i, bool life) { _pl[i].life= life; }
	b_player();
	~b_player();
};

