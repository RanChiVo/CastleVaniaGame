#pragma once
#include "Enemy.h"
#include "GameObjects/Simon.h"

class FishMan : public Enemy
{
private:
	DWORD timeWalk;
	DWORD timeShoot;
	Simon* simon;
	D3DXVECTOR2 posRevival;
	bool isActivated = false;
public:
	enum stateFishMan
	{
		FISH_MAN_STATE_IDLE,
		FISH_MAN_STATE_WALK,
		FISH_MAN_STATE_SHOOT,
		FISH_MAN_STATE_HIDDEN
	};

	FishMan(D3DXVECTOR2 position, int height, int width);
	virtual void Render(Viewport* viewport);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void setTimeRevival(DWORD timeRevival);
	void handleState();
	~FishMan();
};

