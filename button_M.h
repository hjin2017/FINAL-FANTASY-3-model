#pragma once
#include "gameNode.h"
#include "button.h"
class button_M :public gameNode
{
	typedef vector<button*> buV;
	typedef vector<button*>::iterator buVI;
private:
	buV _buV;
	buVI _buVI;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void set_bu(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		int num, const char* Name);
	inline buV get_buV(void) { return _buV; }
	inline buVI get_buVI(void) { return _buVI; }
	button_M();
	~button_M();
};

