#include "StopWatch.h"

constexpr float STOP_WATCH_GRAVITY = 0.0006f;


StopWatch::StopWatch(D3DXVECTOR2 position)
{
	id = ID_ENTITY_STOP_WATCH;
	state = STATE_SHOW;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	AnimationSets * animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(id);
	SetAnimationSet(ani_set);
	SetPosition(position);
	//AddAnimation(STOP_WATCH_ANI);
	state = STATE_SHOW;
	currentAnimation = STOP_WATCH_ANI;
}

void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	if (state == STATE_SHOW)
	{
		vy += STOP_WATCH_GRAVITY * dt;

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
			float rdx = 0;
			float rdy = 0;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			for (int i = 0; i < coEvents.size(); i++)
			{
				switch (coEvents[i]->obj->getID())
				{
				case ID_ENTITY_FLOOR:
					if (ny != 0) vy = 0;
					Dy = min_ty * dy + ny * 0.08f;
					break;
				}
			}
			y += Dy;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void StopWatch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void StopWatch::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	Flip flip = flip_horiz;

	animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);

	//	RenderBoundingBox(viewport);
}


StopWatch::~StopWatch()
{
}
