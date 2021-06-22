#include "stdafx.h"
#include "obj_npc_door.h"


obj_npc_door::obj_npc_door()
{
}


obj_npc_door::~obj_npc_door()
{
}
void obj_npc_door::update(void)
{
	if (_select)
	{
		set_frame_x(1);
	}
	else
	{
		set_frame_x(2);
	}
}