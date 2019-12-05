#include "StaticObject.h"
#include "./GameObjects/WeaponReward.h"
#include "./GameObjects/Heart.h"
#include "./GameObjects/Dagger.h"
#include "./GameObjects/SmallHeart.h"
#include "./GameObjects/Cross.h"
#include "./GameObjects/FireBomb.h"
#include "./GameObjects/MiraculousBag.h"
#include "./Axe.h"

constexpr int FIRE_LIVE_TIME = 300;

StaticObject::StaticObject()
{
}

void StaticObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	if (state == STATE_EFFECT)
	{
		if (GetTickCount() - liveTime > FIRE_LIVE_TIME)
		{
			state = STATE_DETROY;
			liveTime = 0;
			GameObject* item = nullptr;
			idHiddenItem = ResourceManagement::GetInstance()->getStringToEntity()[getIdHiddenItem()];
			switch (idHiddenItem)
			{
			case ID_ENTITY_WEAPON_REWARD:
				item = new WeaponReward(this->getPosition());
				break;
			case ID_ENTITY_HEART:
				item = new Heart(this->getPosition());
				break;
			case ID_ENTITY_AXE:
				item = new Axe(this->getPosition());
				break;
			case ID_ENTITY_DAGGER:
				item = new Dagger(this->getPosition());
				break;
			case ID_ENTITY_SMALL_HEART:
				item = new SmallHeart(this->getPosition());
				break;
			case ID_ENTITY_CROSS:
				item = new Cross(this->getPosition());
				break;
			case ID_ENTITY_FIRE_BOMB:
				item = new FireBomb(this->getPosition());
				break;
			case ID_ENTITY_RED_100_MIRACULOUS_BAG:
			case ID_ENTITY_BLUE_400_MIRACULOUS_BAG:
			case ID_ENTITY_WHITE_700_MIRACULOUS_BAG:
			case ID_ENTITY_BONUS_1000_MIRACULOUS_BAG:
				item = new MiraculousBag(idHiddenItem, this->getPosition());
				break;
			}
			if(item)
			coObjects->push_back(item);
		}
	}
}

void StaticObject::Render(Viewport * viewport)
{
	if (state == STATE_EFFECT)
	{
		AddAnimation(ANI_EFFECT);
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = flip_horiz;
		animations.find(ANI_EFFECT)->second->Render(position.x, position.y, flip);
	}
}

StaticObject::~StaticObject()
{
}
