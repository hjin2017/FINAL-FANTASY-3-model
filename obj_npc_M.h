#pragma once
#include "gameNode.h"
#include "obj_npc.h"
#include "obj_npc_box.h"
#include "obj_npc_stand.h"
#include  "obj_npc_door.h"
class obj_npc_M :public gameNode
{
	typedef vector<obj_npc*> NPCV;
	typedef vector<obj_npc*>::iterator NPCVI;
private:
	NPCV _npcV;
	NPCVI _npcVi;
public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void set_obj_box(string txtname, int x, int y,int num);
	void set_npc_stand(string imageName, int x, int y, string t, int num);
	void set_npc_imagine(string str,int x, int y, int x2, int y2, int num);
	inline NPCV get_npcV(void) {return _npcV;}
	inline NPCVI get_npcVI(void) { return _npcVi; }
	void removeall(void);
	obj_npc_M();
	~obj_npc_M();
};

