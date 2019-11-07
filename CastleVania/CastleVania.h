#pragma once
#include "Game.h"
#include "Textures/Textures.h"
#include "GameObjects/Simon.h"
#include "SpriteManagements/Sprites.h"
#include "Animations/Animations.h"
#include "WindowUtil.h"
#include "Screens/ScreenBase.h"
#include "ScreenManager.h"
#include "Screens/MenuScreen.h"
#include "Screens/GameplayScreen.h"

class CastleVania : public Game
{
private:
	HINSTANCE hInstance;
	int nCmdShow;
	ScreenManager* screenmanager;
	MenuScreen* menuscreen;
	GameplayScreen* gameplayscreen;

public:
	CastleVania();
	void Init(HINSTANCE hInstance, int nCmdShow);
	void loadResource();
	void renderObjects();
	void update(DWORD dt);
	void run();
	~CastleVania();
};
