#include "stdafx.h"
#include "menu_scene.h"


menu_scene::menu_scene()
{
}


menu_scene::~menu_scene()
{
}
HRESULT menu_scene::init(void)
{
	vector<string>vs;
	//초기화 전체 돌리기
	DATABASE->setpos(PointMake(0, 0));
	vs = TXTDATA->txtLoad(set_map_load_obj(DATABASE->get_map_num(), false).c_str());
	TXTDATA->txtSave(set_map_load_obj(DATABASE->get_map_num(), true).c_str(), vs);
	vs.clear();
	_count = 0;

	SetWindowPos(_hWnd, NULL, 0, 0, WINSIZEX, WINSIZEY, SWP_NOMOVE);
	
	return S_OK;
}
void menu_scene::release(void)
{
	
}
void  menu_scene::update(void)
{
	if (_count < 0)
	{
		_count = 0;
	}
	else if (_count > 1)
	{
		_count = 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_count -= 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_count += 1;
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		switch (_count)
		{
		case menu_map_tool:
			SCENEMANAGER->changeScene("맵툴");
			break;
		case menu_play:
			SCENEMANAGER->changeScene("play");
			break;

			
		}
	}
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		SCENEMANAGER->changeScene("테스트");
	}

}
void menu_scene::render(void) 
{

	HFONT _hfont;
	HFONT _old;
	char str[126];
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	_hfont = CreateFont(50, 0, 0,0, 0, 0, true, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
	_old = (HFONT)SelectObject(getMemDC(), _hfont);

	IMAGEMANAGER->render("메뉴이미지", getMemDC(), 0, 0);

	switch (_count)
	{
	case menu_map_tool:
		IMAGEMANAGER->render("파판손", getMemDC(), WINSIZEX / 2-200, WINSIZEY / 2+40);
		break;
	case menu_play:
		IMAGEMANAGER->render("파판손", getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2 + 100);
		
		break;
	}
	
	sprintf(str, "맵툴");
	TextOut(getMemDC(), WINSIZEX / 2 - 120, WINSIZEY / 2 + 40, str, strlen(str));
	sprintf(str, "play");
	TextOut(getMemDC(), WINSIZEX / 2 - 120, WINSIZEY / 2 + 100, str, strlen(str));
	
	//_TEXTstart = false;
	//sprintf(str, textchar);
	//TextOut(getMemDC(), 100, 100, str, strlen(str));

	SelectObject(getMemDC(), _old);
	DeleteObject(_hfont);
	DeleteObject(SetTextColor);
}