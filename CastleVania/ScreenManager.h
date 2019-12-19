#pragma once
#include <vector>
#include "Screens/ScreenBase.h"
#include "DebugOut/DebugOut.h"
#include "TiledMap.h"

class ScreenManager
{
private:
	std::vector<ScreenBase*> screens;
	ScreenBase* screen;
	EntityID currentScreenID;

	ScreenBase* previousScreen;
	ScreenBase* nextScreen;
	ScreenBase* currentScreen;

public:
	ScreenManager();

	bool init();
	void loadResources();
	void update(DWORD dt);
	void renderObject(Viewport* viewport);
	void addScreen(ScreenBase* scene);
	void removeScreen();
	void changeScreen(int level);
	void clearScreen();

	ScreenBase* getScene();

	~ScreenManager();
};

