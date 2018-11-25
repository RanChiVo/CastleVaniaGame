#include "GameplayScreen.h"
#include "../WindowUtil.h"
#include "../Direct3DManager.h"

void GameplayScreen::init()
{
	Direct3DManager* direct3D = Direct3DManager::getInstance();
	viewport = direct3D->getViewport();
}

void GameplayScreen::update(float dt)
{
	updateViewport(dt);
	vector< LPGAMEOBJECT> staticObjects;

	for (int i = 0; i < objects.size(); i++)
	{
		staticObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &staticObjects);
	}
}

void GameplayScreen::updateViewport(float dt)
{
	D3DXVECTOR2 pos_Simon = simon->getPosition();

	D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};

	newPosViewport.x = simon->getPosition().x - viewport->getWidth() / 2;
	newPosViewport.y = viewport->getY();

	newPosViewport.x = min(tile_map->getWidthWorld() - viewport->getWidth(), newPosViewport.x);
	newPosViewport.y = min(tile_map->getHeightWorld() - viewport->getHeight(), newPosViewport.y);
	newPosViewport.x = max(0, newPosViewport.x);
	newPosViewport.y = max(0, newPosViewport.y);

	viewport->SetPosition(float(newPosViewport.x), float(newPosViewport.y));
}

void GameplayScreen::renderObject()
{
	tile_map->draw(viewport);

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render(viewport);
	}
}

void GameplayScreen::loadResources()
{
	resourceManagement->textures->Add(ID_TEX_GAMEPLAYSCREEN, L"TiledMap\\Entrance.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 textPlayScreen = resourceManagement->textures->Get(ID_TEX_GAMEPLAYSCREEN);

	tile_map->readMapfromfile("TiledMap\\Entrance.tmx", textPlayScreen);

	simon->loadResource();
	objects.push_back(simon);

	D3DXVECTOR2 posEntrance;

	for (auto object : tile_map->getObjectInfo())
	{
		if (object.first.second == "BurnBarrel")
		{
			BurnBarrel* burnbarrel = new BurnBarrel(object.second);
			objects.push_back(burnbarrel);
		}
		else if (object.first.second == "Entrance")
		{
			posEntrance = object.second;
		}
	}

	Heart* heart = new Heart(D3DXVECTOR2(0, -100));
	objects.push_back(heart);

	WeaponReward* weaponReward = new WeaponReward(D3DXVECTOR2(0, -100));
	objects.push_back(weaponReward);

	heart = new Heart(D3DXVECTOR2(0, -100));
	objects.push_back(heart);

	weaponReward = new WeaponReward(D3DXVECTOR2(0, -100));
	objects.push_back(weaponReward);

	Katana* katana = new Katana(D3DXVECTOR2(0, -100));
	objects.push_back(katana);

	MiraculousBag* miraculousBag = new MiraculousBag(D3DXVECTOR2(0, -100));
	objects.push_back(miraculousBag);

	Floor* floor = new Floor();
	floor->SetPosition(D3DXVECTOR2(0, 350));
	objects.push_back(floor);
	
	for (int i = 0; i < 2; i++)
	{
		CBrick* brick = new CBrick();
		brick->SetPosition(D3DXVECTOR2(0 + i*1500, 0));
		objects.push_back(brick);
	}

	Entrance* entrance = new Entrance(D3DXVECTOR2(-200, -100));
	entrance->setNewposition(posEntrance);
	objects.push_back(entrance);

	KatanaWeapon * katanaWeapon = new KatanaWeapon(D3DXVECTOR2(-200, -100));
	objects.push_back(katanaWeapon);
}

GameplayScreen::GameplayScreen()
{
	tile_map = new TiledMap();

	directInput = DirectInput::getInstance();

	simon = new Simon();

	resourceManagement = ResourceManagement::GetInstance();
}

GameplayScreen::~GameplayScreen()
{
	delete simon;
}
