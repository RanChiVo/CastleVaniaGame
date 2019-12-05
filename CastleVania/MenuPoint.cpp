#include "MenuPoint.h"
#include "../CastleVania/EntityID.h"


MenuPoint::MenuPoint()
{
	startTime = GetTickCount();
	resourceManagement = ResourceManagement::GetInstance();
}

void MenuPoint::loadResource()
{
	heart = resourceManagement->getSprite(ID_ENTITY_HEART)->Get("heartMenuPoint");
	HP = resourceManagement->getSprite(ID_ENTITY_HP)->Get("HP1");
	enemy_HP1 = resourceManagement->getSprite(ID_ENTITY_HP_ENEMY)->Get("enemy_HP1");
	lost_HP = resourceManagement->getSprite(ID_ENTITY_LOST_HP)->Get("lost_HP1");
	place_item1 = resourceManagement->getSprite(ID_ENTITY_PLACE)->Get("place_item1");
	resourceManagement->loadFont(L"Resources\\Fonts\\prstart.ttf");
	spriteHandler = Direct3DManager::getInstance()->GetSpriteHandler();
	R = RECT{ 15, 20, 550, 528 };
	font = resourceManagement->getFont();
}

void MenuPoint::update()
{
	gameTime = 300 - (GetTickCount() - startTime) / 1000;
}

void MenuPoint::Draw()
{
	timeString = std::to_string(gameTime);
	content = "SCORE_000000 TIME " + timeString + " STAGE 01\n";
	content += "PLAYER				                    -62\n";
	content += "ENEMY                    P-03\n";
	heart->Draw(D3DXVECTOR2(435.0f, 35.0f), Flip::normal);
	for (int i = 0; i < 16; i++)
	{

		HP->Draw(D3DXVECTOR2(125.0f + 12.0f * i, 39.0f), Flip::normal);
		enemy_HP1->Draw(D3DXVECTOR2(125.0f + 12.0f * i, 59.0f), Flip::normal);
	}
	place_item1->Draw(D3DXVECTOR2(360.0f, 38.0f), Flip::normal);
	if (font)
		font->DrawTextA(spriteHandler, content.c_str(), -1, &R, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

MenuPoint::~MenuPoint()
{
}
