#pragma once
#include "gameNode.h"
#include "tile_node.h"
#include "button_M.h"
#include "drag.h"
#include "Save_load.h"
class map_tool :public gameNode
{
private:
	enum buttonsave
	{
		button_save,
		button_load,
		button_GROUND,
		button_OBJ,
		button_WALL,
		button_ERASER,
		button_battle,
		button_end
	};

	enum mouse_num
	{
		mouse_01,
		mouse_02,
		mouse_03

	};
private:
	Save_load* _save_load;
	drag* _drag;
	image* _image;
	tagtile* _tile;
	tagtile _sample[SAMPLETILEX*SAMPLETILEY];
	tagtile _current;
	tagtile* _current_drag;
	int TILEX, TILEY, TILEMAX;
	//드레그 타일
	tagtile* _drtile;
	////카메라
	int _x, _y;
	bool s;
	/////버튼
	button_M* _button;
	int _select_num;
	////텍스트
	char *a;
	////드레그 
	bool _dragstart;
	mouse_num _mouse;
	////드레그 읽기
	int x;
	int y;
	bool _dragload;
	////마우스 전환
	int _mouse_num;
	//세이브 로드 인자
	char FileName[258];


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void  setup(void);
	void setmap(void);
	void save(void);
	void load(void);
	tileobj set_obj(int x, int y);
	void setView(void);
	void camera(void);
	void set_drag_samplemap(void);
	void set_drag_map(void);
	void set_button(void);
	void setmap_drag(void);
	map_tool();
	~map_tool();
};

