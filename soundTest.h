#pragma once
#include "gameNode.h"
#include <commdlg.h>		//�̰��� ������ OPENFILENAME �Լ��� �����ִ�

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

