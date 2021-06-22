#pragma once
#include "gameNode.h"
#include"map_tool_scene.h"
#include "txttest.h"
#include "menu_scene.h"
#include "play_scene.h"
#include "inve.h"
#include "inven_bag.h"
#include "inven_state.h"
#include "inven_equipment.h"
#include "inven_job.h"
#include "salesman_scene.h"
#include "temp_node.h"
#include "battle_scene.h"

class mainGame : public gameNode
{
private:

public:
	virtual HRESULT init(void);		
	virtual void release(void);		
	virtual void update(void);		
	virtual void render(void);
	void setupimage(void);
	void objinit(void);
	
	mainGame();
	~mainGame();
};

