#pragma once
#include "gameNode.h"
#include "Save_load.h"
#include "tile_node.h"
class _tile_map :public gameNode
{
private:
	Save_load* _load;
	image* _image;
	image* _image2;
	tagtile* _tile;
	int TILEX, TILEY, TILEMAX;
	int _x, _y;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void load(void);
	void draw(void);
	_tile_map();
	~_tile_map();
};

