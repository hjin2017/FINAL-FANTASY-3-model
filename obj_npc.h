#pragma once
#include "gameNode.h"
#include "text_box.h"
#include "tile_node.h"
class obj_npc :public gameNode
{
	enum objjob
	{
		box,
		npc,
		npc_m
	};
protected:
	text_box* _text_box;
	image* _image;
	RECT _rc;
	int _x, _y,_x2,_y2,map_num;
	int c_x, c_y;
	int _frame_x, _frame_y;
	int _npc_job;
	int _num;
	string _text;
	bool _select;
	int set_num;
	tileobj obj_j;
	string _bagname;
	int _bag_num;
	int _bag_lv;
public:
	virtual HRESULT init(string imageName, int x, int y,int x2,int y2, int num);
	virtual HRESULT init(string imageName, int x, int y, string t, int num, bool select);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	inline RECT get_rc(void) { return _rc; }
	void text(void);

	inline void set_xy(int x, int y) { c_x = x; c_y = y; }
	void set_obj(tileobj obj) { obj_j = obj; }
	inline tileobj get_obj(void) { return obj_j; }
	inline bool get_select(void) { return _select; }
	void set_select(bool b) { _select = b; }

	inline string get_bag_name(void) { return _bagname; }
	inline int get_bag_num(void) { return _bag_num; }
	inline int get_bag_lv(void) { return _bag_lv; }
	inline int get_x(void) { return  _x; }
	inline int get_y(void) { return  _y; }
	inline int get_x2(void) { return _x2; }
	inline int get_y2(void) { return _y2; }
	inline int get_map_num(void) { return map_num; }
	void set_frame_x(int i) {_frame_x = i;}
	void set_bag(int num, int lv, string itemname) {  _bag_num = num; _bag_lv = lv; _bagname = itemname;}

	obj_npc();
	~obj_npc();
};

