#include "stdafx.h"
#include "map_tool1.h"


map_tool1::map_tool1()
{
}


map_tool1::~map_tool1()
{
}
 HRESULT map_tool1::init(void)
{
	 TILEX = 100;
	 TILEY = 100;
	 TILEMAX = TILEX + TILEY;
	 _image = IMAGEMANAGER->addImage("map", TILEX*TILESIZE_05, TILEY*TILESIZE_05);
	 _x = 0;
	 _y = 0;
	 for (int i = 0; i < TILEY; i++)
	 {
		 for (int j = 0; j < TILEX; j++)
		 {
			 IMAGEMANAGER->findImage("파판_1_소")->frameRender(_image->getMemDC(),
				 TILESIZE_05*j, TILESIZE_05*i, 1, 1);
		 }
	 }

	 return S_OK;
}
 void map_tool1::release(void)
{
	 _image = NULL;
}
 void map_tool1::update(void)
{
	 if (KEYMANAGER->isOnceKeyDown('S'))
	 {
		 SCENEMANAGER->changeScene("메뉴");
	 }
}
 void map_tool1::render(void)
{
	 IMAGEMANAGER->findImage("파판_1_소")->render(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("파판_1_소")->getWidth() - 16, 0);
	
	 _image->render(getMemDC(), 0, 0, _x, _y, WINSIZEX/2, WINSIZEY);
}