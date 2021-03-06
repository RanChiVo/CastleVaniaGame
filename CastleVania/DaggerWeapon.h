#pragma once
#include "GameObjects/GameObject.h"
#include "CombatWeapon.h"

class DaggerWeapon : public CombatWeapon
{
public:
	DaggerWeapon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~DaggerWeapon();
};

