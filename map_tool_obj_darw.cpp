#include "stdafx.h"
#include "map_tool_obj_darw.h"


map_tool_obj_darw::map_tool_obj_darw()
{
}


map_tool_obj_darw::~map_tool_obj_darw()
{
}
HRESULT map_tool_obj_darw::init(void)
{
	_objs = p_n_w;
	_itemcount = 0;
	_item_num = 0;
	_currentobj.x = _currentobj.y = 0;;
	return S_OK;
}
void map_tool_obj_darw::release(void)
{
}
void map_tool_obj_darw::update(void)
{
}
void map_tool_obj_darw::render(void)
{
}
void map_tool_obj_darw::obj_draw(void)
{
	char str[500];

	if (_button_num == dr_obj || _button_num == dr_new_obj)
	{
		Rectangle(getMemDC(), _ptMouse.x, _ptMouse.y, _ptMouse.x + 200, _ptMouse.y + 200);
		switch (_objs)
		{
		case p_n_w:
			sprintf(str, "1. PLAYER");
			TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 20, str, strlen(str));
			sprintf(str, "2. NPC");
			TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 40, str, strlen(str));
			sprintf(str, "3. WARP");
			TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 60, str, strlen(str));
		break;
		case coordinate:
			sprintf(str, "좌표 클릭");
			TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 20, str, strlen(str));
		break;
		case w_dr:
			sprintf(str, _objtext.number.c_str());
			TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 20 + 20 * atoi(_objtext.number.c_str()), str, strlen(str));
			sprintf(str, _objtext.name.c_str());
			TextOut(getMemDC(), _ptMouse.x + 20, _ptMouse.y + 20 + 20 * atoi(_objtext.number.c_str()), str, strlen(str));
		break;
		case obj_job:
			sprintf(str, "1. box");
			TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 20, str, strlen(str));
			sprintf(str, "2. NPC_STAND");
			TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 40, str, strlen(str));
			sprintf(str, "3. NPC_MOVE");
			TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 60, str, strlen(str));
		break;
		case obj_text:
			for (int i = 0; i < _obj_save.size(); i++)
			{
				//상자면
				if (_obj_save[i] == 'b'&&_obj_save[i + 2] == '1')
				{
					sprintf(str, "우클릭");
					TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 150, str, strlen(str));
					vector<string> vs;
					vs = TXTDATA->txtLoad("테스/아이탬.txt");
					for (int j = 0; j < vs.size(); j++)
					{
						if (vs[j] == _itemName)
						{
							sprintf(str, vs[j + 2].c_str());
							TextOut(getMemDC(), _ptMouse.x + 20, _ptMouse.y + 20 + (atoi(vs[j + 1].c_str())) * 20, str, strlen(str));
							sprintf(str, vs[j + 1].c_str());
							TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 20 + (atoi(vs[j + 1].c_str())) * 20, str, strlen(str));
						}
					}
					vs.clear();
				}
				if (_obj_save[i] == 'm')
				{
					sprintf(str, "텍스트 입력");
					TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 20, str, strlen(str));
				}
			}
		break;
		case obj_num:
		{
			vector<string> vs;
			vs = TXTDATA->txtLoad("테스/npc.txt");
			int temp;
			for (int i = 0; i < vs.size(); i++)
			{
				temp = 0;
				if (vs[i] == "/"&&_itemcount == temp&&vs[i + 1] == "npc"&&vs[i + 3] == "상인")
				{
					sprintf(str, vs[i + 2].c_str());
					TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 20 + 20 * (atoi(vs[i + 2].c_str())), str, strlen(str));
					sprintf(str, vs[i + 4].c_str());
					TextOut(getMemDC(), _ptMouse.x + 20, _ptMouse.y + 20 + 20 * (atoi(vs[i + 2].c_str())), str, strlen(str));
				}
				temp = 1;
				if (vs[i] == "#"&&_itemcount == temp&&vs[i + 1] == "npc"&&vs[i + 3] == "주민")
				{
					sprintf(str, vs[i + 2].c_str());
					TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 20 + 20 * (atoi(vs[i + 2].c_str())), str, strlen(str));
					sprintf(str, vs[i + 4].c_str());
					TextOut(getMemDC(), _ptMouse.x + 20, _ptMouse.y + 20 + 20 * (atoi(vs[i + 2].c_str())), str, strlen(str));
				}
			}
			vs.clear();
		}
		break;
		case obj_View:
			sprintf(str, "저장");
			TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 20, str, strlen(str));
		break;
		}
	}
}
void map_tool_obj_darw::obj_control(void)
{
	if (_objs == p_n_w&&_button_num == dr_obj)
	{
		_obj_save += set_obj_save("/", true);
	}
	if (_objs == p_n_w&&_button_num == dr_new_obj)
	{
		creat_obj_save();
		_obj_save += set_obj_save("/", true);
	}
	int int_temp;
	char temp[123];
	char str[258];
	if (_button_num == dr_obj || _button_num == dr_new_obj)
	{
		switch (_objs)
		{
		case p_n_w:
			switch (atoi(textchar))
			{
			case 1:
				_obj_save += set_obj_save("p", false);
				_currentobj.x = 12;
				_currentobj.y = 0;
				_objs = coordinate;
				textchar[0] = '\0';
				_TEXTstart = false;
			break;
			case 2:
				_obj_save += set_obj_save("n", false);
				_currentobj.x = 4;
				_currentobj.y = 2;
				_objs = coordinate;
				textchar[0] = '\0';
				_TEXTstart = false;
			break;
			case 3:
				_obj_save += set_obj_save("w", false);
				_currentobj.x = 11;
				_currentobj.y = 0;
				_objs = w_dr;
				textchar[0] = '\0';
				_TEXTstart = true;
				_objtext.number ="0";
				_objtext.name = "우클릭";
			break;
			}
		break;
		case w_dr:
		{
			int_temp = atoi(textchar);
			vector<string> vs;
			vs = TXTDATA->txtLoad("테스/w_dr.txt");
			for (int i = 0; i < vs.size(); i++)
			{
				_count = 1;
				if (vs[i] == "/"&&_itemcount == _count&&int_temp== atoi(vs[+1].c_str()))
				{
					_currentobj.x = atoi(vs[i+3].c_str());
					_currentobj.y = atoi(vs[i+4].c_str());
					_obj_save += set_obj_save(vs[i+1], false);
					_obj_save += set_obj_save(vs[i + 2], false);
					_obj_save += set_obj_save(vs[i + 3], false);
					_obj_save += set_obj_save(vs[i + 4], false);
					_currentobj.sir=false; 
					_objs = coordinate;
					textchar[0] = '\0';
				break;
				}
				_count = 2;
				if (vs[i] == "!"&&_itemcount == _count&&int_temp == atoi(vs[+1].c_str()))
				{
					_currentobj.x = atoi(vs[i+3].c_str());
					_currentobj.y = atoi(vs[i+4].c_str());
					_obj_save += set_obj_save(vs[i + 1], false);
					_obj_save += set_obj_save(vs[i + 2], false);
					_obj_save += set_obj_save(vs[i + 3], false);
					_obj_save += set_obj_save(vs[i + 4], false);
					_currentobj.sir = true;
					_objs = coordinate;
					textchar[0] = '\0';
				break;
				}
			}
		}
		break;
		case obj_job:
			switch (atoi(textchar))
			{
			case 1:
				int_temp = atoi(textchar);
				_obj_save += set_obj_save("b", false);
				_obj_save += set_obj_save(itoa(int_temp, temp, 10), false);
				_objs = obj_text;
				textchar[0] = '\0';
			break;
			case 2:
				int_temp = atoi(textchar);
				_obj_save += set_obj_save("m", false);
				_obj_save += set_obj_save(itoa(int_temp, temp, 10), false);
				_objs = obj_text;
				textchar[0] = '\0';
			break;
			case 3:
				int_temp = atoi(textchar);
				_obj_save += set_obj_save("m", false);
				_obj_save += set_obj_save(itoa(int_temp, temp, 10), false);
				_objs = obj_text;
				textchar[0] = '\0';
			break;
			}
		break;
		case obj_text:
			for (int i = 0; i <_obj_save.size(); i++)
			{
				if (_obj_save[i] == 'b'&&_obj_save[i + 2] == '1')
				{
					vector<string> vs;
					vs = TXTDATA->txtLoad("테스/아이탬.txt");
					for (int j = 0; j < vs.size(); j++)
					{
						if (vs[j] == _itemName&&atoi(textchar) == atoi(vs[j + 1].c_str()))
						{
							_obj_save += set_obj_save(vs[j], false);
							_obj_save += set_obj_save(vs[j + 1], false);
							_objs = obj_View;
							textchar[0] = '\0';
							break;
						}
					}
					vs.clear();
				}
				if (_obj_save[i] == 'm')
				{
					temp[0] = '\0';
					strcpy_s(temp, textchar);
					for (int i = 0; i < sizeof(temp); i++)
					{
						if (temp[i] == VK_RETURN)
						{
							temp[i] = NULL;
							break;
						}
					}
					_obj_save += set_obj_save(temp, false);
					textchar[0] = '\0';
					_objs = obj_num;
				}
			}
		break;
		case obj_num:
		{
			vector<string> vs;
			vs = TXTDATA->txtLoad("테스/npc.txt");
			for (int i = 0; i < vs.size(); i++)
			{
				set_obj_num(vs, i, "/", "상인", 0, 0);
				set_obj_num(vs, i, "#", "주민", 0, 1);
			}
			vs.clear();
			textchar[0] = '\0';
		}
		_TEXTstart = false;
		_objs = obj_View;
		break;
		case obj_View:
		{
			string s;
			s += "파판obj/";
			for (int i = 0; i < _fileName.size(); i++)
			{
				if (_fileName[i] == '/')
				{
					for (int j = 1; j < 10; j++)
					{
						if (_fileName[i + j] != '.')
						{
							s += _fileName[i + j];
						}
						if (_fileName[i + j] == '.')
						{
						break;
						}
					}
				}
			}
			s += ".txt";
			vector<string> vtemp;
			vtemp = TXTDATA->txtLoad(s.c_str());
			vtemp.push_back(_obj_save.c_str());
			TXTDATA->txtSave(s.c_str(), vtemp);
			vtemp.clear();
			_obj_save.clear();
			textchar[0] = '\0';
		}
		_itemcount = 0;
		textchar[0] = '\0';
		_TEXTstart = false;
		_button_num = 6;
		_objs = p_n_w;
		break;
		}
	}
}
string map_tool_obj_darw::set_obj_save(string str, bool one)
{
	string s;
	if (one)
	{
		s += ",";
	}
	s += str;
	s += ",";
	return s;
}
void map_tool_obj_darw::creat_obj_save(void)
{
	string s;
	vector<string> vtemp;
	s += "파판obj/";
	for (int i = 0; i < _fileName.size(); i++)
	{
		if (_fileName[i] == '/')
		{
			for (int j = 1; j < 50; j++)
			{
				if (_fileName[i + j] != '.')
				{
					s += _fileName[i + j];
				}
				if (_fileName[i + j] == '.')
				{
					break;
				}
			}
		}
	}
	s += ".txt";
	vtemp.push_back(",obj,");
	TXTDATA->txtSave(s.c_str(), vtemp);
	vtemp.clear();
}
void map_tool_obj_darw::set_obj_num(vector<string> vs, int fori, string str1, string str2, int lv, int pos)
{
	int i = fori;
	char temp[123];
	if (vs[i] == str1&& vs[i + 3] == str2&&_itemcount == pos)
	{
		if (vs[i + 1] == "npc"&&atoi(vs[i + 2].c_str()) == atoi(textchar))
		{
			_obj_save += set_obj_save(vs[i + 3], false);
			_obj_save += set_obj_save(vs[i + 2], false);
			_obj_save += set_obj_save(itoa(lv, temp, 10), false);
			vs.clear();
		}
	}
}
void map_tool_obj_darw::set_obj_mouse_right(void)
{
	if (_objs == obj_text || _objs == obj_num ||_objs==w_dr)
	{
		_itemcount++;
		switch (_itemcount)
		{
		case 0:
			_itemName = "검";
			break;
		case 1:
			_itemName = "포션";
			break;
		case 2:
			_itemName = "머리";
			break;
		case 3:
			_itemName = "가슴";
			break;
		case 4:
			_itemName = "팔";
			break;
		case 6:
			_itemName = "지팡이";
			break;
		case 7:
			_itemName = "검";
			_itemcount = 0;
			break;
		}
	}

	if (_button_num == dr_obj || _button_num == dr_new_obj)
	{
		switch (_objs)

		{
		case w_dr:
			vector<string> vs;
			vs = TXTDATA->txtLoad("테스/w_dr.txt");
			for (int i = 0; i < vs.size(); i++)
			{
				_count = 1;
				if (vs[i] == "/"&&_itemcount == _count)
				{
					_objtext.number = vs[i + 1].c_str();
					_objtext.name = vs[i + 2].c_str();
				break;
				}
				_count = 2;
				if (vs[i] == "!"&&_itemcount == _count)
				{
					_objtext.number = vs[i + 1].c_str();
					_objtext.name = vs[i + 2].c_str();
				break;
				}
			}
			vs.clear();
		break;
		}
	}









}
