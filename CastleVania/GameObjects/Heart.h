#pragma once
#include "../GameObjects/GameObject.h"

constexpr int HEART_STATE_HIDE = 1;
constexpr int HEART_STATE_SHOW = 2;
constexpr int HEART_ANI_HIDE = 18;
constexpr int HEART_ANI_SHOW = 19;
constexpr float HEART_GRAVITY = 0.05f;


class Heart: public GameObject
{
	int untouchable;
	DWORD untouchable_start;
public:
	Heart();
	Heart(D3DXVECTOR2 position);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);

	~Heart();
};

