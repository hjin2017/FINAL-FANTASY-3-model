#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	_btnSceneChange = new button;
	_btnSceneChange->init("��ư", WINSIZEX / 2, WINSIZEY / 2 - 100,
		PointMake(0, 1), PointMake(0, 0), cbSceneChange);

	_btnAngleDown = new button;
	_btnAngleDown->init("��ư", WINSIZEX / 2 - 250, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbAngleDown);

	_btnAngleUp = new button;
	_btnAngleUp->init("��ư", WINSIZEX / 2 + 250, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbAngleUp);




	return S_OK;
}

void selectScene::release()
{

}

void selectScene::update()
{
	_btnSceneChange->update();
	_btnAngleDown->update();
	_btnAngleUp->update();

}

void selectScene::render()
{
	_btnSceneChange->render();
	_btnAngleDown->render();
	_btnAngleUp->render();
}

void selectScene::cbSceneChange(void)
{
	SCENEMANAGER->changeScene("��Ÿ��");
}

void selectScene::cbAngleUp(void)
{
	DATABASE->setElementDataAngle("battle", DATABASE->getElementData("battle")->angle += 0.2f);
}

void selectScene::cbAngleDown(void)
{
	DATABASE->setElementDataAngle("battle", DATABASE->getElementData("battle")->angle -= 0.2f);
}