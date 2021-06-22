#pragma once
#include "gameNode.h"
class inven_job :public gameNode
{
private:

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	inven_job();
	~inven_job();
};

