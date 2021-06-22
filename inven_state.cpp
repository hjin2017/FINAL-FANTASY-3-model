#include "stdafx.h"
#include "inven_state.h"


inven_state::inven_state()
{
}


inven_state::~inven_state()
{
}
HRESULT inven_state::init(void)
{
	_text_box = new text_box;
	_text_box->init("상태","파판이미지/메뉴/말.bmp", 150, 50);
	_text_box->set_text_box_op(20, 0, 20, 10, "상   태", 30);
	_text = new text_draw_c;
	set_init();

	return S_OK;
}
void inven_state::release(void)
{
	SAFE_DELETE(_text_box);
	SAFE_DELETE(_text);
}
void inven_state::update(void) 
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		SCENEMANAGER->changeScene("inven");
	}
}
void inven_state::render(void) 
{
	IMAGEMANAGER->findImage("상태")->render(getMemDC(), 20, 0);
	_text_box->text_box_draw();
	IMAGEMANAGER->findImage(imageName(_job, _pl, true).c_str())->
		frameRender(getMemDC(), 180, 20);
	_text->text_draw(270, 30, _name, 20);
	_text->text_draw(420, 30, _job, 20);
	_text->text_draw_int(70, 100, "레벨       ", _lv, 20);
	_text->text_draw_int(270, 100, "경험                 ", _ex, 20);
	_text->text_draw_int(270, 150, "다음 레벨         ", experience(_lv)- _ex, 20);
	_text->text_draw_int(70, 200, "HP       ", _hp, 20);
	_text->text_draw_int(180, 200, "/   ", set_st(_power, _dex, _Int)*_lv, 20);
	_text->text_draw_int(70, 250, "MP       ", _mp, 20);
	_text->text_draw_int(180, 250, "/   ", set_st(_wis, _Int, _dex)*_lv, 20);
	_text->text_draw_int(70, 300, "힘        :   ", _power, 20);
	_text->text_draw_int(70, 350, "민첩성  :   ", _dex, 20);
	_text->text_draw_int(70, 400, "지성     :   ", _Int, 20);
	_text->text_draw_int(70, 450, "정신력  :   ", _wis, 20);
	_text->text_draw_int(270, 300, "공격력  :   ", set_st(_power,0,0)+ _handle_1, 20);
	_text->text_draw_int(270, 350, "마법공격력  :   ", set_st(_Int, 0, 0), 20);
	_text->text_draw_int(270, 400, "방어력  :   ", set_st(_dex, 0, 0) + _haed + _arm + _body, 20);
	_text->text_draw_int(270, 450, "마법방어력  :   ", set_st(_wis, 0, 0), 20);

}
void inven_state::set_init(void)
{
	_name = DATABASE->getElementData(DATABASE->get_player())->name;
	_job= DATABASE->getElementData(DATABASE->get_player())->job;
	_pl = DATABASE->get_player()+1;
	_lv= DATABASE->getElementData(DATABASE->get_player())->lv;
	_att= DATABASE->getElementData(DATABASE->get_player())->att;
	_matt= DATABASE->getElementData(DATABASE->get_player())->matt;
	_def= DATABASE->getElementData(DATABASE->get_player())->def;
	_mdef= DATABASE->getElementData(DATABASE->get_player())->mdef;
	_hp= DATABASE->getElementData(DATABASE->get_player())->hp;
	_mp= DATABASE->getElementData(DATABASE->get_player())->mp;
	_power= DATABASE->getElementData(DATABASE->get_player())->power;
	_Int= DATABASE->getElementData(DATABASE->get_player())->Int;
	_dex= DATABASE->getElementData(DATABASE->get_player())->dex;
	_wis= DATABASE->getElementData(DATABASE->get_player())->wis;
	_ex= DATABASE->getElementData(DATABASE->get_player())->ex;
	_handle_1 = 0;
	_handle_2 = 0;
	_arm = 0;
	_haed = 0;
	_body = 0;

	char temp[123];
	vector<string> vs;
	vs = TXTDATA->txtLoad("테스/아이탬.txt");
	for (int i=0;i<vs.size();i++)
	{
		if (DATABASE->getElementData(DATABASE->get_player())->handle_1.name == vs[i]&&
			vs[i+1]== itoa(DATABASE->getElementData(DATABASE->get_player()) ->handle_1.num, temp,10))
		{
			_handle_1=atoi(vs[i + 3].c_str());
		}
		if (DATABASE->getElementData(DATABASE->get_player())->handle_2.name == vs[i] &&
			vs[i + 1] == itoa(DATABASE->getElementData(DATABASE->get_player())->handle_2.num, temp, 10))
		{
			_handle_2 = atoi(vs[i + 3].c_str());
		}

		if (DATABASE->getElementData(DATABASE->get_player())->haed.name == vs[i] &&
			vs[i + 1] == itoa(DATABASE->getElementData(DATABASE->get_player())->haed.num, temp, 10))
		{
			_haed = atoi(vs[i + 4].c_str());
		}

		if (DATABASE->getElementData(DATABASE->get_player())->arm.name == vs[i] &&
			vs[i + 1] == itoa(DATABASE->getElementData(DATABASE->get_player())->arm.num, temp, 10))
		{
			_arm = atoi(vs[i + 4].c_str());
		}

		if (DATABASE->getElementData(DATABASE->get_player())->body.name == vs[i] &&
			vs[i + 1] == itoa(DATABASE->getElementData(DATABASE->get_player())->body.num, temp, 10))
		{
			_body = atoi(vs[i + 4].c_str());
		}
	
	}
}
