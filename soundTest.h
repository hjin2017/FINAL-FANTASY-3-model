#pragma once
#include "gameNode.h"
#include <commdlg.h>		//이것이 있으면 OPENFILENAME 함수를 쓸수있다

class soundTest : public gameNode
{
private:
	RECT _rc;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	soundTest();
	~soundTest();
};

