#pragma once
#include "gameNode.h"

class menu_scene :public gameNode
{
private:
	enum menu
	{
		menu_map_tool,
		menu_play,
		menu_end
	};
	menu _menu;
	int _count;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	menu_scene();
	~menu_scene();
};

