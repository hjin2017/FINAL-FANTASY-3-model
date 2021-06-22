#pragma once
#include "gameNode.h"

class fontTest : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();


	fontTest();
	~fontTest();
};

