#pragma once
#include "gameNode.h"
#include "map_creat.h"
#include "tile_node.h"
#include "drag.h"
#include "button.h";
#include "map_tool_obj_darw.h"
#define buttonmax 8
class map_tool_scene :public gameNode
{
	enum mouse_select
	{
		mouse_one,
		mouse_drag,
		mouse_set_map_drag
	}; 
	enum buttonset
	{
		left,
		right,
		wall,
		graound,
		obj,
		new_obj,
		battle_num_F,
		battle_num_M,
		button_end
	};
	enum save_load
	{
		save,
		load,
		end
	};
	enum obj_item
	{
		item_sword,
		item_potion,
		item_helmet,
		item_Body,
		item_arm,
		item_stick,
		item_end
	};
	enum obj_dr
	{
		dr_p_n_w,
		dr_coordinate,
		dr_coordinate2,
		dr_coordinate3,
		dr_w_dr,
		dr_obj_job,
		dr_obj_text,
		dr_obj_num,
		dr_obj_View,
		dr_obj_end
	};
private:
	map_tool_obj_darw* _objD;
	button* _button[buttonmax];
	map_creat* _map_creat;
	map_load* _map_load;
	tagtile _sample[SAMPLETILEX*SAMPLETILEY];
	tagtile _current;
	tagtile _settile;

	drag* _drag;
	save_load _saveload;
	int current_tilex;
	int current_tiley;
	tagtile* current_tile;
	int _x, _y;
	int _x2, _y2;
	bool _map_select_1;
	int _count, _select_num;
	int _map_count;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void set_up_sample(void);
	void keyboard(void);
	void mouse(void);
	void set_map(void);
	void set_sample(void);
	void current_map(void);
	void drag_draw(void);
	void save_load_draw(void);
	void key_save_load(void);
	void init_map_tool(void);
	void set_button(void);
	void mouse_set_tile(int x, int y, int cx, int cy);
	void set_obj_mouse(void);
	map_tool_scene();
	~map_tool_scene();
};

