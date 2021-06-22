#include "stdafx.h"
#include "inven_job.h"


inven_job::inven_job()
{
}


inven_job::~inven_job()
{
}
HRESULT inven_job::init(void)
{
	return S_OK;
}
void inven_job::release(void)
{
}
void inven_job::update(void) 
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		SCENEMANAGER->changeScene("inven");
	}
}
void inven_job::render(void) 
{
}