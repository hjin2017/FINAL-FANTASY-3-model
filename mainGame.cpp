#include "stdafx.h"
#include "mainGame.h"

//======================================
// 생성자랑 소멸자는 쓰지 않는다
//======================================
mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}


//======================================
// 생성자랑 소멸자는 쓰지 않는다
//======================================


//초기화는 앞으로 여기에다가 해라
HRESULT mainGame::init(void)
{
	gameNode::init(true);
	setupimage();

	vector<string>vs;
	//가방을 비움
	vs.push_back("없음");
	TXTDATA->txtSave("테스/가방.txt", vs);
    TXTDATA->txtSave("파판로그/mapSave.txt",vs);
	vs.clear();

	SCENEMANAGER->addScene("메뉴", new menu_scene);
	SCENEMANAGER->addScene("맵툴", new map_tool_scene);
	SCENEMANAGER->addScene("테스트", new txttest);
	SCENEMANAGER->addScene("play", new play_scene);
	SCENEMANAGER->addScene("inven", new inve);
	SCENEMANAGER->addScene("inven_bag", new inven_bag);
	SCENEMANAGER->addScene("inven_equipment", new inven_equipment);
	SCENEMANAGER->addScene("inven_state", new inven_state);
	SCENEMANAGER->addScene("inven_job", new inven_job);
	SCENEMANAGER->addScene("salesman", new salesman_scene);
	SCENEMANAGER->addScene("temp_node", new temp_node);
	SCENEMANAGER->addScene("battle_scene", new battle_scene);
	
	SCENEMANAGER->changeScene("battle_scene");
	return S_OK;
}

//메모리 해제는 앞으로 여기에다가 해라
void mainGame::release(void)
{
	gameNode::release();
	SCENEMANAGER->release();
}

//연산은(는) 앞으로 여기에다가 해라
void mainGame::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();

}

//앞으로 여기에다 그려라 
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//PatBlt(getMemDC(), 600, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지마라 ================

	SCENEMANAGER->render();
	
	
	//===============아래도 건들지마라 =================
	this->getBackBuffer()->render(getHDC(),0,0);
}
void mainGame::setupimage(void)
{
	IMAGEMANAGER->addFrameImage("파판_1_중", "파판이미지/파판_map/1_map.bmp", 0, 0, TILESIZE*SAMPLETILEX, TILESIZE*SAMPLETILEY, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("파판_1_소", "파판이미지/파판_map/1_map.bmp", 0, 0, TILESIZE_05*SAMPLETILEX, TILESIZE_05*SAMPLETILEY, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스텟메뉴", "파판이미지/메뉴/스텟메뉴.bmp", 0, 0, 585, 565, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("검사1", "파판이미지/주인공/플1.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사2", "파판이미지/주인공/플2.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사3", "파판이미지/주인공/플3.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사4", "파판이미지/주인공/플4.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("검사_1", "파판이미지/주인공/플전1.bmp", 676, 52, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사_2", "파판이미지/주인공/플전2.bmp", 676, 52, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사_3", "파판이미지/주인공/플전3.bmp", 676, 50, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사_4", "파판이미지/주인공/플전4.bmp", 676, 50, 13, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("테스트아이탬", "파판이미지/아이탬/아이탬테스트.bmp", 112, 16, 6, 1, true, RGB(255, 0, 255));
	

	IMAGEMANAGER->addImage("메뉴이미지", "파판이미지/메뉴/메인메뉴.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("파판손", "파판이미지/메뉴/표시.bmp", 0, 0, 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("파판손_소", "파판이미지/메뉴/표시_소.bmp", 0, 0, 30, 30, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("인벤메뉴", "파판이미지/메뉴/인벤메뉴.bmp", 0, 0, 585, 565, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이탬메뉴", "파판이미지/메뉴/아이탬메뉴.bmp", 0, 0, 585 - 40, 565 / 2 + 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("말", "파판이미지/메뉴/말.bmp", 0, 0, 152 + 80, 32 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("말2", "파판이미지/메뉴/상점배경.bmp", 0, 0, 400, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("말3", "파판이미지/메뉴/상점배경.bmp", 0, 0, 585/1.6, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("말4", "파판이미지/메뉴/상점배경.bmp", 0, 0, 585 / 3, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("캐릭창", "파판이미지/메뉴/스텟.bmp", 0, 0, 585 - 40, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상태", "파판이미지/메뉴/아이탬메뉴.bmp", 0, 0, 585 - 40, 565-20, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("전투지역","파판이미지/파판_map/b_grond.bmp", 585, 805, 1, 11, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("에메랄드", "파판이미지/button/button_save.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("블랙", "파판이미지/button/button_load.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("베이지", "파판이미지/button/button_wall.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("화이트", "파판이미지/button/button_ground.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("체리", "파판이미지/button/button_obj.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("레드", "파판이미지/button/button_eraser.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));

	objinit();

}
void mainGame::objinit(void)
{
	IMAGEMANAGER->addFrameImage("박스", "파판이미지/obj/박스.bmp", 32 * 2, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("상인", "파판이미지/obj/상인.bmp", 32, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("주민", "파판이미지/obj/주민.bmp", 24, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("문", "파판이미지/obj/문.bmp", 90, 32, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("enemy0", "파판이미지/enemy/enemy0.bmp", 264, 392, 4, 4, true, RGB(255, 0, 255));

}