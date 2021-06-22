#include "stdafx.h"
#include "obj_npc_M.h"


obj_npc_M::obj_npc_M()
{
}


obj_npc_M::~obj_npc_M()
{
}
HRESULT obj_npc_M::init(void)
{
	return S_OK;
}
void obj_npc_M::release(void)
{

}
void obj_npc_M::update(void) 
{
	for (_npcVi = _npcV.begin(); _npcVi < _npcV.end(); _npcVi++)
	{
		(*_npcVi)->update();
	}
}
void obj_npc_M::render(void) 
{
	for (_npcVi = _npcV.begin(); _npcVi < _npcV.end(); _npcVi++)
	{
		(*_npcVi)->render();
	}
}
void obj_npc_M::set_obj_box(string txtname, int x, int y,int num)
{
	if (txtname != "없음")
	{
	vector<string> vs;
	vs = TXTDATA->txtLoad("테스/아이탬.txt");

	string str;
	string temp;
	for (int i = 0; i < vs.size(); i++)
	{
		if (vs[i] == txtname&&atoi(vs[i+1].c_str())==num)
		{
			str = vs[i + 10];
			temp = vs[i + 2];
			break;
		}
	}
	vs.clear();
	obj_npc* ob;
	ob = new obj_npc_box;
	ob->init(str, x, y, temp, num,false);
	_npcV.push_back(ob);
	str.clear();
	}
	else if (txtname == "없음")
	{
		obj_npc* ob;
		ob = new obj_npc_box;
		ob->init("박스", x, y, "없음", num,true);
		_npcV.push_back(ob);
	}
}
void obj_npc_M::set_npc_stand(string imageName, int x, int y, string t, int num)
{
	obj_npc* ob;
	ob = new obj_npc_stand;
	ob->init(imageName, x, y, t, num, false);
	_npcV.push_back(ob);
}
void obj_npc_M::set_npc_imagine(string str,int x, int y,int x2,int y2,int num)
{
	string s;
	s = str;
	if (str != "문")
	{
		s.clear();
		s = "문";
	}
	obj_npc* ob;
	ob = new obj_npc_door;
	ob->init(s, x, y, x2, y2, num);
	_npcV.push_back(ob);
}
void obj_npc_M::removeall(void)
{
	int x = _npcV.size();
	for (int i = 0; i < x; i++)
	{
		SAFE_DELETE(_npcV[i]);
		SAFE_RELEASE(_npcV[i]);
	}
	for (int i = 0; i < x; i++)
	{
		_npcVi = _npcV.begin();
		_npcV.erase(_npcVi);
	}
	_npcV.clear();
}