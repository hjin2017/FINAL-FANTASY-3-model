#pragma once
#include "gameNode.h"

class Save_load : public gameNode
{
private:
	vector<string> savedata;

public:
	virtual HRESULT init(bool load);
	virtual void release(void);
	void mapTool_save(char* cint, char* map);
	string mapTool_load(string cint);
	string mapTool_item_load(string str);
	Save_load();
	~Save_load();
};

class Save_load_bag : public gameNode
{
private:
	vector<string> savedata;

public:
	void bag_save(string itemName, int num,int count);
	Save_load_bag();
	~Save_load_bag();
};