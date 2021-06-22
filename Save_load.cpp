#include "stdafx.h"
#include "Save_load.h"


Save_load::Save_load()
{
}


Save_load::~Save_load()
{
}
HRESULT Save_load::init(bool load)
{
	if (load)
	{
		savedata = TXTDATA->txtLoad("테스/ss.txt");
	}


	return S_OK;
}
void Save_load::release(void)
{

}
void Save_load::mapTool_save(char* cint, char* map)
{
	for (int i = 0; i < savedata.size(); i++)
	{
		if (savedata[i] == cint)return;
	}
	char str[258];
	ZeroMemory(str, sizeof(str));
	strcat(str, cint);
	strcat(str, ",");
	strcat(str, map);

	savedata.push_back(str);
	TXTDATA->txtSave("테스/ss.txt", savedata);
}
string Save_load::mapTool_load(string cint)
{
	vector<string>vs;
	vs= TXTDATA->txtLoad("테스/ss.txt");
	string str;
	for (int i = 0; i < vs.size(); i++)
	{

		if (vs[i] == cint)
		{
			return str+=vs[i+1];
			break;
		}
		else continue;
	}
	vs.clear();
}

Save_load_bag::Save_load_bag()
{
}


Save_load_bag::~Save_load_bag()
{
}

void Save_load_bag::bag_save(string itemName, int num,int count)
{
	if (count == NULL)
	{
		char temp[125];
		savedata.push_back("/");
		savedata.push_back("없음");
		savedata.push_back("0");
		savedata.push_back("0");
		TXTDATA->txtSave("테스/가방.txt", savedata);
	}
	else
	{
		char temp[125];
		savedata.push_back("/");
		savedata.push_back(itemName);
		savedata.push_back(itoa(num, temp, 10));
		savedata.push_back(itoa(count, temp, 10));
		TXTDATA->txtSave("테스/가방.txt", savedata);
	}
	   
}
