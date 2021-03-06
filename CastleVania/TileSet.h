#pragma once
#include <map>
#include "SpriteManagements/Sprite.h"
#include "../CastleVania/SpriteManagements/Sprites.h"
#include "Textures/Textures.h"

class TileSet
{
private:
	int tileWidth;
	int tileHeight;
	Sprite tile;
	std::map<string, Sprite> tiles;
	LPDIRECT3DTEXTURE9 IDTex;

public:
	TileSet(LPDIRECT3DTEXTURE9 IDTex, int tileWidth, int tileHeight);
	void createTileSet(int rows, int columns);
	Sprite& getPositionTile(std::string);
	~TileSet();
};

