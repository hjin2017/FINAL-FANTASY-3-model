#pragma once
#include "gameNode.h"
#include "knight.h"

class ghostScene : public gameNode
{
private:
	knight* _knight;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	ghostScene();
	~ghostScene();
};

