#pragma once
#include "gameNode.h"
#include "player.h"
#include "map_creat.h"
#include"obj_npc_M.h"
class play_scene :public gameNode
{
	enum dir
	{
		left,
		right,
		up,
		down
	};

private:
	dir _d;
	obj_npc_M* _obj;
	tile_map* _tile;
	player* _p;
	int _x, _y;
	int _end_obj;
	bool _text;
	bool _movescene;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void coil_wall(void);
	void coil_obj(void);
	void set_bag(string itemName, int i);
	void set_npc(void);
	void re_set(void);
	void bag_log(void);
	play_scene();
	~play_scene();
};

