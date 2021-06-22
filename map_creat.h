#pragma once
#include "gameNode.h"
#include "tile_node.h"
#include "Save_load.h"
class map_creat :public gameNode
{
private:
	Save_load* _save;
	image* _image;
	tagtile* _tile;
	int _x, _y;
	int TILEX, TILEY, TILEMAX;
	string _FileName;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void render(void);
	void set_up_map(void);
	void set_tile(tagtile temp, int i);
	void save(char* num, char* str);
	void load(void);
	void changeName(int i);
	void set_up_load_map(void);
	void set_obj(int i, int framex, int framey) { _tile[i].obj_frameX = framex; _tile[i].obj_frameY = framey; _tile[i].obj = OBJ_NPC; }
	inline void set_x(int i) { _x = i; }
	inline void set_y(int i) { _y = i; }
	inline tagtile get_tile(int i) { return _tile[i]; }
	inline int get_tilex(void) { return TILEX; }
	inline string get_fileName(void) {   return _FileName; }

	map_creat();
	~map_creat();
};

class map_load :public gameNode
{
private:
	Save_load* _load;
	image* _image_load;
	tagtile* _tile;
	int TILEX, TILEY, TILEMAX;
	int _x, _y;
	string _FileName;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void render(void);
	void set_up_map(void);
	void load(void);
	void changeName(int i);
	inline tagtile get_tile(int i) { return _tile[i]; }
	void set_x(int i) { _x = i; }
	void set_y(int i) { _y = i; }
	inline int get_tilex(void) { return TILEX; }
	inline int get_num(void) { return set_num(_FileName.c_str()); }
	map_load();
	~map_load();
};

class tile_map :public gameNode
{
private:
	Save_load* _load;
	image* _image_map;
	tagtile* _tile;
	int TILEX, TILEY, TILEMAX;
	int _x, _y;
	string _FileName;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void render(void);
	void load(void);
	void set_up_map(void);
	void set_x(int i) { _x = i; }
	void set_y(int i) { _y = i; }
	inline tagtile  get_tile(int i) { return _tile[i]; }
	 void update_tile(tileobj obj, bool b, int i){ _tile[i].obj = obj; _tile[i].move = b; }
	tile_map();
	~tile_map();
};
