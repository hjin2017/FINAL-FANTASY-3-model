#pragma once
#include "gameNode.h"

class characterSelectScene : public gameNode
{
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


	characterSelectScene();
	~characterSelectScene();
};

