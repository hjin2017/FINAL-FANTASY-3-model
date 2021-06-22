#include "stdafx.h"
#include "temp_node.h"


temp_node::temp_node()
{
}


temp_node::~temp_node()
{
}
HRESULT temp_node::init(void)
{
	vector<string> vs;
	bool set = true;
	char temp[123];
	vs = TXTDATA->txtLoad("파판로그/mapSave.txt");
	for (int i = 0; i < vs.size(); i++)
	{
		if (vs[i] == "/"&&atoi(vs[i + 1].c_str()) == DATABASE->get_map_num())
		{
			set = false;
		}
	}
	vs.clear();
	if (set)
	{
		vs = TXTDATA->txtLoad(set_map_load_obj(DATABASE->get_map_num(), false).c_str());//
		TXTDATA->txtSave(set_map_load_obj(DATABASE->get_map_num(), true).c_str(), vs);
		vs.clear();
	}	
	return S_OK;
}
void temp_node::release(void)
{
	
}
void temp_node::update(void)
{
	SCENEMANAGER->changeScene("play");
}
void temp_node::render(void)
{

}