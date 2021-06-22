#pragma once
#include "gameNode.h"
#include"text_box.h"
#include "bag.h"
#include"character_hp_mp.h"
class inven_bag :public gameNode
{
private:
	bag* _bag;
	text_box* _text_box;
	character_hp_mp* _hp;
	bool _select;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	inven_bag();
	~inven_bag();
};

