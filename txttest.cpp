#include "stdafx.h"
#include "txttest.h"



txttest::txttest()
{
}


txttest::~txttest()
{
}

HRESULT txttest::init(void)
{
	obj = new obj_npc_M;
	obj->init();
	for (int i = 0;i < 10000; i++)
	{
		obj->set_obj_box("°Ë", i*100, 100, 1);
	}

	return S_OK;
}

void txttest::release(void)
{
	obj->removeall();
	obj->release();
	SAFE_DELETE(obj);
}
void txttest::update(void)
{
	obj->update();

	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		SCENEMANAGER->changeScene("¸Ş´º");
		
	}
	if (KEYMANAGER->isOnceKeyDown('9'))
	{
		
	}

	
	
}

void txttest::render(void)
{
	obj->render();
}
