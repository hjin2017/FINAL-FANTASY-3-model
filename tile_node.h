#pragma once
#include "stdafx.h"



#define SAMPLESIZE 32
#define SAMPLETILEX 39
#define SAMPLETILEY 9

#define TILESIZE 32
#define TILESIZE_05 16
#define TILESIZE_2 64
enum tileobj
{
	OBJ_PLAYER,
	OBJ_BOX_01,
	OBJ_NPC,
	OBJ_WURP_01,
	OBJ_TUNNEL,
	OBJ_NORMAL,
	OBJ_SP
};

struct tagtile
{
	RECT rc;
	tileobj obj;
	int tile_frameX, tile_frameY;
	int obj_frameX, obj_frameY;
	int battle_num;
	bool move;
};

struct tagcurrent
{
	int x, y;
};
