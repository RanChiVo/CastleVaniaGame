#include "Cross.h"
#include "../ResourceManagement.h"

constexpr float CROSS_GRAVITY = 0.0006f;

Cross::Cross(D3DXVECTOR2 position)
{
	id = ID_ENTITY_CROSS;
	SetPosition(position);
	//AddAnimation(CROSS_ANI);
	currentAnimation = CROSS_ANI;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	liveTime = GetTickCount();
}

void Cross::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += CROSS_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny;
		float Dx = dx, Dy = dy;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (int i = 0; i < coEvents.size(); i++)
		{
			switch (coEvents[i]->obj->getID())
			{
			case ID_ENTITY_FLOOR:
				if (ny < 0) vy = 0;
				Dy = min_ty * dy;
				break;
			}
		}
		x += Dx;
		y += Dy;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (GetTickCount() - liveTime > 4000)
	{
		state = STATE_DETROY;
		liveTime = 0;
	}
}

void Cross::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Cross::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip = normal;
	animation_set->at(currentAnimation)->Render(position.x, position.y, flip);
}

Cross::~Cross()
{
}
