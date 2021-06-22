#pragma once
#include "ship.h"

class battle : public ship
{
private:
	missilePF* _missile;

public:
	virtual HRESULT init(const char* imageName, int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();
	
	virtual void keyControl();

	virtual void missileFire();
	virtual void missileMove();
	virtual void missileDraw();


	battle();
	~battle();
};

