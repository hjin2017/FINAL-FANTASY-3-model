#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "b_player.h"
#include "text_box.h"
class battle_scene :public gameNode
{

	enum pldr
	{
		dr_att,
		dr_def,
		dr_run,
		dr_bag,
		dr_mig
	};

private:
	POINT _plh;
	b_player* _pl;
	enemy* _enemy;
	text_draw_c _txt;
	int i_temp[4];
	bool _select;
	int _selectcount;
	int _plcount, em_count,entrun_count;
	bool _turn, _die;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void pl_trun_txt(void);
	void en_temp(void);
	void trun_a(void);
	void pl_att(int i);
	void em_att(void);
	string pl_trun_dr(void);
	battle_scene();
	~battle_scene();
};

