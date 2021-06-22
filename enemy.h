#pragma once
#include "gameNode.h"
#define kind 4
#include "text_box.h"
class enemy : public gameNode
{
	enum enemyposy
	{   eny_first,
		eny_one,
		eny_two,
		eny_three
	};
	enum enemyposx
	{
		enx_first,
		enx_one,
		enx_two,
		enx_three,
		enx_four,
		enx_five
	};
	struct tagenemy
	{
		string name;
		string imageName;
		int att, def, hp;
		int framex, framey, x, y;
		int num;
		bool turn;
		bool life;
	};

private:
	int enx, eny, enmax;
	text_draw_c _txt;
	string _Name[kind];
	tagenemy* _enemy;
	int icount;
	int _enmeynum;
	int _turncount;
	bool _turn_stop ;
	int en_y;
	int en_x;
	int _num;
	void udate_turn(void);
	void set_up(void);
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	 void set_num(int i) { _num= i; }
	 inline tagenemy* get_temp(void) { return _enemy; }
	  void set_life(int i,bool b) {  _enemy[i].life= b; }
	  void set_hp(int i, int hp) { _enemy[i].hp+= hp; }
	  void set_turn(int i, int turn) { _enemy[i].turn = turn; }
	 inline int get_e_x(void) { return en_x; }
	 inline int get_e_y(void) { return en_y; }
	 inline int get_enmax(void) { return enmax; }
	 inline int get_turn(void) { return _turn_stop; }
	 inline int get_icount(void) { return icount; }
	 void set_turn_stop(bool b) { _turn_stop = b; }
	enemy();
	virtual ~enemy();
};

