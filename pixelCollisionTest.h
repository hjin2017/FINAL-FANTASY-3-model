#pragma once
#include "gameNode.h"

class pixelCollisionTest : public gameNode
{
private:
	image* _mountain;	//���	�̹���
	image* _ball;		//��		�̹���

	RECT _rc;			//��Ʈ
	float _x, _y;		//�� ��ǥ
	int _probeY;		//Y Axis Probe
	
public:
	HRESULT init();
	void release();
	void update();
	void render();

	pixelCollisionTest();
	~pixelCollisionTest();
};

