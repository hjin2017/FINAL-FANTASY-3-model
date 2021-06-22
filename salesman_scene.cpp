#include "stdafx.h"
#include "salesman_scene.h"


salesman_scene::salesman_scene()
{
}


salesman_scene::~salesman_scene()
{
}
HRESULT salesman_scene::init(void)
{
	SetWindowPos(_hWnd, NULL, 0, 0, 600, 600, SWP_NOMOVE);
	_gold = DATABASE->get_gold();
	_text_draw_c = new text_draw_c;
	_text_draw_c->init();
	_count = 0;
	_dr_x= _pcount= _salecount=0;
	_dr_select = false;
	set_item();
	
	return S_OK;
}
void salesman_scene::release(void)
{
	_tbx->removeall();
	_tbx->release();
	SAFE_DELETE(_tbx);
	SAFE_DELETE(_text_draw_c);

	int x = _itv.size();
	for (int i = 0; i < x; i++)
	{
		SAFE_DELETE(_itv[i]);
	}
	for (int i = 0; i < x; i++)
	{
		_itiv = _itv.begin();
		_itv.erase(_itiv);
	}
	_itv.clear();
	DATABASE->set_gold(_gold);
}
void salesman_scene::update(void) 
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)&&!_dr_select)
	{
		_count--;
		if (_count < dr_buy)
		{
			_count = dr_exit;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)&&!_dr_select)
	{
		_count++;
		if (_count > dr_exit)
		{
			_count = dr_buy;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		switch (_count)
		{
		case dr_buy:
			_pcount--;
			if (0 > _pcount)
			{
				_pcount = item_count - 1;
			}
			break;
		case dr_sale:
			_salecount--;
			if (0 > _salecount)
			{
				_salecount = 7;
				//
			}
		break;
		}
		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		switch (_count)
		{
		case dr_buy:
		_pcount++;
		if (item_count - 1 < _pcount)
		{
			_pcount = 0;
		}
		break;
		case dr_sale:
			_salecount++;
			if (_salecount > 7)
			{
				_salecount = 0;
				//
			}
		break;
		}
	}
	item_update();
	update_bag();
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_dr_select)
		{
			_dr_select = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (!_dr_select)
		{
			
			_dr_select = true;
			init_bag();
			if (_count == dr_exit)
			{
				SCENEMANAGER->changeScene("play");
			}
		}
		else
		{
			_dr_select = false;
			select_item();
		}
		
		
	}
	
///////////////////////////////////////////////////////////////////
	
}
void salesman_scene::render(void) 
{
    item_draw();
	text_draw();	
}
void salesman_scene::set_item(void)
{
		string itemName;
	    //상인의 정보 를 받고
		switch (DATABASE->get_salesman())
		{
		case ite_weapon:
			itemName = "무기";
			break;
		case ite_armor:
			itemName = "방어";
			break;
		case ite_portion:
			itemName = "물약";
			break;
		case ite_spell:
			itemName = "책";
			break;
		}
		vector<string> vs;
		vs = TXTDATA->txtLoad("테스/아이탬.txt");
		item_count = 0;
		for (int i = 0; i < vs.size(); i++)
		{   //구분해서
			if (itemName == vs[i] && atoi(vs[i + 2].c_str()) == DATABASE->get_itemLV())
			{
				tagitem* it;
				it = new tagitem;
				it->itemName = vs[i + 1];
				it->itnum = atoi(vs[i + 2].c_str());
				it->Name = vs[i + 3];
				it->att = atoi(vs[i + 4].c_str());
				it->def = atoi(vs[i + 5].c_str());
				it->hp = atoi(vs[i + 6].c_str());
				it->mp = atoi(vs[i + 7].c_str());
				it->framex = atoi(vs[i + 8].c_str());
				it->framey = atoi(vs[i + 9].c_str());
				it->gold = atoi(vs[i + 10].c_str());
				it->iamge = IMAGEMANAGER->findImage("테스트아이탬");
				_itv.push_back(it);
				item_count++;
				//백터에 담는다
			}
		}
		vs.clear();
			
			_tbx = new text_box_M;
			_tbx->set_text_box(itemName, 585, 75, 0, 0, 50, 25, itemName, 30);
			_tbx->set_text_box("어서오시오", 585 - 150, 75, 150, 0, 30, 25, "어서오시오", 30);
			_tbx->set_text_box("구매", 100, 75, 0, 75, 25, 25, "구매", 30);
			_tbx->set_text_box("판매", 100, 75, 100, 75, 25, 25, "판매", 30);
			_tbx->set_text_box("나가기", 125, 75, 100 * 2, 75, 25, 25, "나가기", 30);
			_tbx->set_text_box("골드", 260, 75, 100 * 3 + 24, 75, 15, 25, "골드", 30);
		itemName.clear();
	
}
void salesman_scene::text_draw(void)
{
	_tbx->render();
	_text_draw_c->text_draw_int(430, 100, "", _gold, 30);
	IMAGEMANAGER->findImage("파판손_소")->render(getMemDC(), _dr_x, 100);
	
	if (_dr_select)
	{
		switch (_count)
		{
		case dr_buy:
			IMAGEMANAGER->findImage("파판손_소")->render(getMemDC(), 0, 165+_pcount*50);
			//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		break;
		case dr_sale:
			IMAGEMANAGER->findImage("파판손_소")->render(getMemDC(), 0, 165 + _salecount * 50);
		break;
		case dr_exit:
			
		break;
		}
	}
}
void salesman_scene::item_update(void)
{
	if (_dr_select)
	{
		switch (_count)
		{
		case dr_buy:
			for (int i = 0; i < _itv.size(); i++)
			{
				_itv[i]->rc = RectMake(100, 165 + i * 50, _itv[i]->iamge->getFrameWidth(), _itv[i]->iamge->getFrameHeight());
			}
			_rc = RectMake(0, 165 + _pcount * 50, 200, 25);
			break;
		case dr_sale:

			_rc = RectMake(0, 165 + _pcount * 50, 200, 25);

			break;
		case dr_exit:

			break;
		}
	}
	else
	{
		switch (_count)
		{
		case dr_buy:
			_dr_x = 0;
			break;
		case dr_sale:
			_dr_x = 100;
			break;
		case dr_exit:
			_dr_x = 200;
			break;
		}
	}
}
void salesman_scene::item_draw(void)
{
	if (_dr_select)
	{
		switch (_count)
		{
		case dr_buy:
			IMAGEMANAGER->findImage("말2")->render(getMemDC(), 0, 150);
			for (int i = 0; i < _itv.size(); i++)
			{
				_itv[i]->iamge->frameRender(getMemDC(), 100, 165 + i * 50, _itv[i]->framex, _itv[i]->framey);
				_text_draw_c->text_draw_int(200, 165 + i * 50, _itv[i]->Name, _itv[i]->gold, 20);
				//Rectangle(getMemDC(), _itv[i]->rc.left, _itv[i]->rc.top, _itv[i]->rc.right, _itv[i]->rc.bottom);
			}
		break;
		case dr_sale:
			IMAGEMANAGER->findImage("말2")->render(getMemDC(), 0, 150);
			draw_bag();
		break;
		case dr_exit:

		break;
		}
	}
}
void salesman_scene::select_item(void)
{
	RECT temp;

	switch (_count)
	{
	case dr_buy:
		for (int i = 0; i < _itv.size(); i++)
		{
			if (IntersectRect(&temp, &_itv[i]->rc, &_rc))
			{
				//if (_gold < _itv[i]->gold)break;
				_gold -= _itv[i]->gold;
				set_bag(_itv[i]->itemName, _itv[i]->itnum);
			}
		}
		break;
	case dr_sale:
		for (int i = 0; i < _vabg.size(); i++)
		{
			if (IntersectRect(&temp, &_vabg[i]->rc, &_rc))
			{
				_gold += _vabg[i]->gold/10;
				del_bag(_vabg[i]->itemName, _vabg[i]->itnum);
			}
		}
		break;
	}
}
void salesman_scene::set_bag(string itemName, int inum)
{
	//가방 txt추가 
	vector<string> vs;
	vs = TXTDATA->txtLoad("테스/가방.txt");
	char temp[123];
	string item;
	int countnum = 0;
	for (int i = 0; i < vs.size(); i++)
	{
		// /이거 기준으로
		if (vs[i] == "/")
		{
			//탬이름이 같고 탬 넘버가 같으면
			if (vs[i + 1] == itemName&&vs[i + 2] == itoa(inum, temp, 10))
			{
				//탬이있으니 카운트 만 받아서 1더함
				countnum = atoi(vs[i + 3].c_str());
				countnum++;
				//카운트 변경
				vs[i + 3] = itoa(countnum, temp, 10);

			}
		}
	}
	if (countnum == 0)
	{
		//카운트가 0이면 없는거네 템 생성 해서 넣어둠
		countnum = 1;
		item += '/';
		item += ',';
		item += itemName;
		item += ',';
		item += itoa(inum, temp, 10);
		item += ',';
		item += itoa(countnum, temp, 10);
		item += ',';
		//백터생성
		vs.push_back(item);
	}
	//지금 까지 한거 저장
	TXTDATA->txtSave("테스/가방.txt", vs);
	vs.clear();
}
void salesman_scene::init_bag(void)
{
	int x = _vabg.size();
	for (int i = 0; i < x; i++)
	{
		SAFE_DELETE(_vabg[i]);
	}
	for (int i = 0; i < x; i++)
	{
		_vibag = _vabg.begin();
		_vabg.erase(_vibag);
	}
	_vabg.clear();

	vector<string> vs;
	vs = TXTDATA->txtLoad("테스/가방.txt");
	for (int i = 0; i < vs.size(); i++)
	{
		if (vs[i] == "/")
		{
			tagitem* tg;
			tg = new tagitem;
			tg->itemName = vs[i + 1];
			tg->itnum = atoi(vs[i + 2].c_str());
			tg->itcount= atoi(vs[i + 3].c_str());
			tg->iamge = IMAGEMANAGER->findImage("테스트아이탬");
			vector<string> vbs;
			vbs = TXTDATA->txtLoad("테스/아이탬.txt");
			for (int j = 0; j < vbs.size(); j++)
			{
				if (vbs[j] == tg->itemName&&atoi(vbs[j+1].c_str()) == tg->itnum)
				{
					tg->Name = vbs[j + 2];
					tg->framex = atoi(vbs[j + 7].c_str());
					tg->framey = atoi(vbs[j + 8].c_str());
					tg->gold = atoi(vbs[j + 9].c_str());
					_vabg.push_back(tg);
					
				}
			}
			vbs.clear();
		}
	}
	vs.clear();
}
void salesman_scene::draw_bag(void)
{
	for (int i = 0; i < _vabg.size(); i++)
	{
		_vabg[i]->iamge->frameRender(getMemDC(), _vabg[i]->rc.left, _vabg[i]->rc.top, _vabg[i]->framex, _vabg[i]->framey);
		_text_draw_c->text_draw_int(_vabg[i]->rc.left+50, _vabg[i]->rc.top, _vabg[i]->Name, _vabg[i]->gold/10, 20);
		_text_draw_c->text_draw_int(_vabg[i]->rc.left + 250, _vabg[i]->rc.top, "수량", _vabg[i]->itcount, 20);
	}
}
void salesman_scene::update_bag(void)
{
	for (int i = 0; i < _vabg.size(); i++)
	{
		_vabg[i]->rc=RectMake(80, 165 + i * 50, _vabg[i]->iamge->getFrameWidth(), _vabg[i]->iamge->getFrameHeight());
	}
}
void salesman_scene::del_bag(string itemName, int inum)
{
	int temp;
	char str[123];
	vector<string> vs;
	vs = TXTDATA->txtLoad("테스/가방.txt");
	for (int i = 0; i < vs.size();i++)
	{
		if (vs[i] == itemName&&atoi(vs[i + 1].c_str()) == inum)
		{
			temp = atoi(vs[i + 2].c_str());
			temp--;
			if (temp > 0)
			{
				vs[i + 2] = itoa(temp,str, 10);
			}
			else if (temp == 0)
			{
				vs[i-1].clear();
				vs[i].clear();
				vs[i+1].clear();
				vs[i+2].clear();
			}
		}
	}
	TXTDATA->txtSave("테스/가방.txt", vs);
	vs.clear();
}