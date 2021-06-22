#pragma once
#include "gameNode.h"
#include "tile_node.h"
class map_tool1 :public gameNode
{
private:
	image* _image;
	tagtile* _tile;
	tagtile _sample[SAMPLETILEX*SAMPLETILEY];
	int TILEX, TILEY, TILEMAX;
	int _x, _y;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	map_tool1();
	~map_tool1();
};

