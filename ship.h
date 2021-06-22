#pragma once
#include "gameNode.h"
#include "bullets.h"

//모선 == 마더쉽 == 부모클라스
class ship : public gameNode
{
protected:
	bullet* _bullet;

	image* _image;		//이미지 
	RECT _rc;			//쉽 렉트
	float _x, _y;		//좌표
	float _angle;		//각도
	float _speed;		//스피드
	float _radius;		//붼지름

public:
	virtual HRESULT init(const char* imageName, int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();
	
	virtual void draw();
	virtual void keyControl();
	virtual void move();

	virtual void bulletFire(void);
	virtual void bulletMove(void);
	virtual void bulletDraw(void);

	virtual void focusDraw(void);
	virtual void defaultDraw(RECT rcFocus);

	image* getImage(void) { return _image; }
	RECT getRect(void) { return _rc; }

	void setAngle(float angle) { _angle = angle; }
	float getAngle() { return _angle; }

	ship();
	virtual ~ship();
};

