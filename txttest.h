#pragma once
#include "gameNode.h"
#include "obj_npc_M.h"
class txttest :public gameNode
{
private:
	obj_npc_M* obj;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	txttest();
	~txttest();
};

