#include "stdafx.h"
#include "obj_npc_box.h"


obj_npc_box::obj_npc_box()
{
}


obj_npc_box::~obj_npc_box()
{
}
void obj_npc_box::update(void)
{
	obj_npc::update();
	if (_select)
	{
		set_frame_x(1);
	}
}