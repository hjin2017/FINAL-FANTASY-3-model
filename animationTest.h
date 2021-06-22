#pragma once
#include "gameNode.h"
#include "animation.h"

class animationTest : public gameNode
{
private:
	image* _camel;

	animation* _ani1;	//디폴트 애니
	animation* _ani2;	//배열 애니
	animation* _ani3;	//구간 애니

public:
	HRESULT init();
	void release();
	void update();
	void render();


	animationTest();
	~animationTest();
};

