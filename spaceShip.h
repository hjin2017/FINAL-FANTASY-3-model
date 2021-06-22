#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"

//�ڼ��� ������ �����Ѵ� �׳��̴� �Ʊ�׳�
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

	//�̹��� �� ��ȯ �Լ�
	image* getShipImage() { return _ship; }

	spaceShip();
	~spaceShip();
};

