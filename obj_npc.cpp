#include "stdafx.h"
#include "obj_npc.h"


obj_npc::obj_npc()
{
}


obj_npc::~obj_npc()
{
}
 HRESULT obj_npc::init(string imageName, int x, int y, int x2, int y2, int num)
{
	 _image = IMAGEMANAGER->findImage(imageName.c_str());
	 _x = x;
	 _y = y;
	 _x2 = x2;
	 _y2 = y2;

	 c_x = 0;
	 c_y = 0;
	 map_num = num;
	 _frame_x = 2;
	 _frame_y = 0;

	 _text = "����";
	 _rc = RectMake(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	 _select = false;
	 if (_select)
	 {
		 set_frame_x(1);
	 }

	return S_OK;
}
HRESULT obj_npc::init(string imageName, int x, int y, string t,int num,bool select)
{
	//�ʱ�ȭ �Ӽ�
	_image = IMAGEMANAGER->findImage(imageName.c_str());
	//Ÿ�� ��ǥ
	_x = x;
	_y = y;
	//��
	_text = t;
	//�Ⱦ��� �����\
	set_num = num;
	//�̰� ��
	c_x = 0;
	c_y = 0;
	//�̰� ������
	_frame_x = 0;
	_frame_y = 0;
	_rc = RectMake(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	//��� �ߴ���?
	_select = select;
	if (_select)
	{
		set_frame_x(1);
	}
	return S_OK;
}
void obj_npc::release(void)
{
	SAFE_DELETE(_image);
	SAFE_RELEASE(_image);
}
void obj_npc::update(void) 
{
	
}
void obj_npc::render(void) 
{
	
	_image->frameRender(getMemDC(), _x - c_x, _y - c_y, _frame_x, _frame_y);
	//Rectangle(getMemDC(), , _y+c_y, _rc.right, _rc.bottom);
}
void obj_npc::text(void)
{
	if (_select)
	{
		IMAGEMANAGER->findImage("��")->render(getMemDC(), 0, 400);
		char str[258];
		sprintf(str, _text.c_str());
		TextOut(getMemDC(), 100, 415, str, strlen(str));
	}
		
	
}
