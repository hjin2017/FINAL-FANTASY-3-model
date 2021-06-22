#pragma once
#include "gameNode.h"
class map_tool_obj_darw :public gameNode
{
	enum obj_save
	{
		p_n_w,
		coordinate,
		coordinate2,
		coordinate3,
		w_dr,
		obj_job,
		obj_text,
		obj_num,
		obj_View,
		obj_end
	};
	enum button_dr
	{
		dr_left,
		dr_right,
		dr_wall,
		dr_graound,
		dr_obj,
		dr_new_obj,
		dr_button_end
	};
	struct tagcurrentobj
	{
		int x, y;
		bool sir;
	};
	struct tagobjtext
	{
		string number, name;
		
	};
private:
	tagobjtext _objtext;
	obj_save _objs;
	int _button_num;
	string _obj_save;
	string _itemName;
	int _itemcount;
	int _item_num;
	int _count;
	string _fileName;
	tagcurrentobj _currentobj;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void obj_draw(void);
	void obj_control(void);
	string set_obj_save(string str, bool one);
	void creat_obj_save(void);
	void set_obj_num(vector<string> vs, int fori, string str1, string str2, int lv, int pos);
	void set_obj_mouse_right(void);


	inline void set_button_num(int i) { _button_num = i; }
	inline void set_fileName(string fileName) { _fileName = fileName; }
	inline obj_save get_obj(void) {return _objs;}
	inline void set_obj(int i) { _objs= (obj_save)i; }
	inline void set_obj_str(string str) { _obj_save += str; }
	inline string get_str(void) { return _obj_save; }
	inline tagcurrentobj get_currentobj(void) { return _currentobj; }
	inline int get_button_num(void) { return _button_num; }
	map_tool_obj_darw();
	~map_tool_obj_darw();
};

