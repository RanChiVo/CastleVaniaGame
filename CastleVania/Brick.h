#pragma once
#include "./StaticObject.h"

class CBrick : public StaticObject
{
private:
	bool isBroken;

public:
	CBrick(std::string name, D3DXVECTOR2 pos, int height, int width);
	virtual void Render(Viewport* viewport);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CBrick();
};