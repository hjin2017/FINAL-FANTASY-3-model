#pragma once
#include "obj_npc.h"
class obj_npc_door :public obj_npc
{
public:
	virtual void update(void);
	obj_npc_door();
	~obj_npc_door();
};

