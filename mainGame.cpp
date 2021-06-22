#include "stdafx.h"
#include "mainGame.h"

//======================================
// �����ڶ� �Ҹ��ڴ� ���� �ʴ´�
//======================================
mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}


//======================================
// �����ڶ� �Ҹ��ڴ� ���� �ʴ´�
//======================================


//�ʱ�ȭ�� ������ ���⿡�ٰ� �ض�
HRESULT mainGame::init(void)
{
	gameNode::init(true);
	setupimage();

	vector<string>vs;
	//������ ���
	vs.push_back("����");
	TXTDATA->txtSave("�׽�/����.txt", vs);
    TXTDATA->txtSave("���Ƿα�/mapSave.txt",vs);
	vs.clear();

	SCENEMANAGER->addScene("�޴�", new menu_scene);
	SCENEMANAGER->addScene("����", new map_tool_scene);
	SCENEMANAGER->addScene("�׽�Ʈ", new txttest);
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

//�޸� ������ ������ ���⿡�ٰ� �ض�
void mainGame::release(void)
{
	gameNode::release();
	SCENEMANAGER->release();
}

//������(��) ������ ���⿡�ٰ� �ض�
void mainGame::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();

}

//������ ���⿡�� �׷��� 
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//PatBlt(getMemDC(), 600, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ������� ================

	SCENEMANAGER->render();
	
	
	//===============�Ʒ��� �ǵ������� =================
	this->getBackBuffer()->render(getHDC(),0,0);
}
void mainGame::setupimage(void)
{
	IMAGEMANAGER->addFrameImage("����_1_��", "�����̹���/����_map/1_map.bmp", 0, 0, TILESIZE*SAMPLETILEX, TILESIZE*SAMPLETILEY, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����_1_��", "�����̹���/����_map/1_map.bmp", 0, 0, TILESIZE_05*SAMPLETILEX, TILESIZE_05*SAMPLETILEY, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ݸ޴�", "�����̹���/�޴�/���ݸ޴�.bmp", 0, 0, 585, 565, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("�˻�1", "�����̹���/���ΰ�/��1.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�2", "�����̹���/���ΰ�/��2.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�3", "�����̹���/���ΰ�/��3.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�4", "�����̹���/���ΰ�/��4.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("�˻�_1", "�����̹���/���ΰ�/����1.bmp", 676, 52, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�_2", "�����̹���/���ΰ�/����2.bmp", 676, 52, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�_3", "�����̹���/���ΰ�/����3.bmp", 676, 50, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�_4", "�����̹���/���ΰ�/����4.bmp", 676, 50, 13, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("�׽�Ʈ������", "�����̹���/������/�������׽�Ʈ.bmp", 112, 16, 6, 1, true, RGB(255, 0, 255));
	

	IMAGEMANAGER->addImage("�޴��̹���", "�����̹���/�޴�/���θ޴�.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���Ǽ�", "�����̹���/�޴�/ǥ��.bmp", 0, 0, 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���Ǽ�_��", "�����̹���/�޴�/ǥ��_��.bmp", 0, 0, 30, 30, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�κ��޴�", "�����̹���/�޴�/�κ��޴�.bmp", 0, 0, 585, 565, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����Ƹ޴�", "�����̹���/�޴�/�����Ƹ޴�.bmp", 0, 0, 585 - 40, 565 / 2 + 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��", "�����̹���/�޴�/��.bmp", 0, 0, 152 + 80, 32 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��2", "�����̹���/�޴�/�������.bmp", 0, 0, 400, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��3", "�����̹���/�޴�/�������.bmp", 0, 0, 585/1.6, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��4", "�����̹���/�޴�/�������.bmp", 0, 0, 585 / 3, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ĳ��â", "�����̹���/�޴�/����.bmp", 0, 0, 585 - 40, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "�����̹���/�޴�/�����Ƹ޴�.bmp", 0, 0, 585 - 40, 565-20, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��������","�����̹���/����_map/b_grond.bmp", 585, 805, 1, 11, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("���޶���", "�����̹���/button/button_save.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��", "�����̹���/button/button_load.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "�����̹���/button/button_wall.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ȭ��Ʈ", "�����̹���/button/button_ground.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ü��", "�����̹���/button/button_obj.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "�����̹���/button/button_eraser.bmp", 63, 70, 1, 2, true, RGB(255, 0, 255));

	objinit();

}
void mainGame::objinit(void)
{
	IMAGEMANAGER->addFrameImage("�ڽ�", "�����̹���/obj/�ڽ�.bmp", 32 * 2, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "�����̹���/obj/����.bmp", 32, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ֹ�", "�����̹���/obj/�ֹ�.bmp", 24, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��", "�����̹���/obj/��.bmp", 90, 32, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("enemy0", "�����̹���/enemy/enemy0.bmp", 264, 392, 4, 4, true, RGB(255, 0, 255));

}