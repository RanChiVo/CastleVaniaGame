#include "MiraculousBag.h"
#include "../ResourceManagement.h"

constexpr float MIRACULOUSBAG_GRAVITY = 0.0006f;
constexpr int TIME_EFFECT = 500;

MiraculousBag::MiraculousBag(EntityID id, D3DXVECTOR2 pos)
{
	SetPosition(pos);
	this->id = ID_ENTITY_MIRACULOUS_BAG;
	state = STATE_SHOW;
	AddAnimation(RED_MIRACULOUSBAG_ANI);
	AddAnimation(EFFECT_100_MONEY_ANI);
	AddAnimation(BLUE_MIRACULOUSBAG_ANI);
	AddAnimation(EFFECT_400_MONEY_ANI);
	AddAnimation(WHITE_MIRACULOUSBAG_ANI);
	AddAnimation(EFFECT_700_MONEY_ANI);
	AddAnimation(BONUS_MIRACULOUSBAG_ANI);
	AddAnimation(EFFECT_1000_MONEY_ANI);
	switch (id)
	{
	case ID_ENTITY_RED_100_MIRACULOUS_BAG:
		currentAnimation = RED_MIRACULOUSBAG_ANI;
		break;
	case ID_ENTITY_BLUE_400_MIRACULOUS_BAG:
		currentAnimation = BLUE_MIRACULOUSBAG_ANI;
		break;
	case ID_ENTITY_WHITE_700_MIRACULOUS_BAG:
		currentAnimation = WHITE_MIRACULOUSBAG_ANI;
		break;
	case ID_ENTITY_BONUS_1000_MIRACULOUS_BAG:
		currentAnimation = BONUS_MIRACULOUSBAG_ANI;
		break;
	}
	liveTime = GetTickCount();
	width = 30;
	height = 30;
}

void MiraculousBag::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);
	if (state == STATE_EFFECT && startMoneyEffectTime == 0)
	{
		startMoneyEffectTime = GetTickCount();
	}
	if (state == STATE_EFFECT && (GetTickCount() - startMoneyEffectTime > TIME_EFFECT))
	{
		state = STATE_DETROY;
		startMoneyEffectTime = 0;
	}
	if (state == STATE_SHOW) {
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			y += min_ty * dy + ny * 0.4f;
			if (ny != 0) vy = 0;
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		if (GetTickCount() - liveTime > 4000)
		{
			state = STATE_DETROY;
			liveTime = 0;
		}
		vy += MIRACULOUSBAG_GRAVITY * dt;
	}
}

void MiraculousBag::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void MiraculousBag::Render(Viewport * viewport)
{
	if (state == STATE_EFFECT)
	{
		switch (currentAnimation)
		{
		case RED_MIRACULOUSBAG_ANI:
			currentAnimation = EFFECT_100_MONEY_ANI;
			break;
		case BLUE_MIRACULOUSBAG_ANI:
			currentAnimation = EFFECT_400_MONEY_ANI;
			break;
		case WHITE_MIRACULOUSBAG_ANI:
			currentAnimation = EFFECT_700_MONEY_ANI;
			break;
		case BONUS_MIRACULOUSBAG_ANI:
			currentAnimation = EFFECT_1000_MONEY_ANI;
			break;
		}
	}
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip = normal;
	animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
}

MiraculousBag::~MiraculousBag()
{
}
