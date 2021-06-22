#pragma once
#include "gameNode.h"
#include "button.h"

class selectScene : public gameNode
{
private:
	button* _btnSceneChange;
	button* _btnAngleDown;
	button* _btnAngleUp;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	static void cbSceneChange(void);
	static void cbAngleUp(void);
	static void cbAngleDown(void);

	selectScene();
	~selectScene();
};

