#pragma once
#include "GameObjects/GameObject.h"

class Boomerang : public GameObject
{
public:
	Boomerang(D3DXVECTOR2 pos);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~Boomerang();
};

