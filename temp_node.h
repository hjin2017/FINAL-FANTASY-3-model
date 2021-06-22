#pragma once
#include "gameNode.h"
class temp_node :public gameNode
{
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	temp_node();
	~temp_node();
};

