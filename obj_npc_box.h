#pragma once
#include "obj_npc.h"
class obj_npc_box :public obj_npc
{
public:
	virtual void update(void);
	obj_npc_box();
	~obj_npc_box();
};