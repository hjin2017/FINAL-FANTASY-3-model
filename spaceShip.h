#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"

//자세한 설명은 생략한다 그놈이다 아까그놈
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;

	missile* _missile;
	ICBM* _icbm;

	enemyManager* _em;

	progressBar* _hpBar;
	float _maxHP, _currentHP;

	int _alphaValue;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void removeMissile(int arrNum);

	void collision();

	void setEnemyManagerMemoryAddressLink(enemyManager* em) { _em = em; }

	ICBM* getICBMMissile() { return _icbm; }

	void hitDamage(float damage);

	//이미지 값 반환 함수
	image* getShipImage() { return _ship; }

	spaceShip();
	~spaceShip();
};

