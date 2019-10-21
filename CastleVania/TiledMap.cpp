#include "TiledMap.h"
#include <d3dx9.h>
#include <sstream>
#include "EntityID.h"
#include "SpriteManagements/Sprite.h"

constexpr int EXTRA_HEIGHT_SCREEN = 90;

//handle string
void eraseAllSubStr(std::string & mainStr, const std::string & toErase)
{
	size_t pos = std::string::npos;
	while ((pos = mainStr.find(toErase)) != std::string::npos)
	{
		mainStr.erase(pos, toErase.length());
	}
}

void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
	size_t pos = data.find(toSearch);
	while (pos != std::string::npos)
	{
		data.replace(pos, toSearch.size(), replaceStr);
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}

TiledMap::TiledMap(std::string resourcepath, LPDIRECT3DTEXTURE9 IDtex)
{
	this->resourcepath = resourcepath;
	this->IDtex = IDtex;
	this->readMapfromfile();
}

void TiledMap::checkGoodFile()
{
	this->isGoodFile = doc.load_file(resourcepath.c_str());
	if (!isGoodFile)
	{
		OutputDebugString(L"[ERROR] Reading failed\n");
		return;
	}
	this->rootNode = doc.child("map");
}

void TiledMap::readMapfromfile()
{
	this->checkGoodFile();
	tilesInMapHeight = rootNode.attribute("height").as_int();
	tilesInMapWidth = rootNode.attribute("width").as_int();
	tileWidth = rootNode.attribute("tilewidth").as_int();
	tileHeight = rootNode.attribute("tileheight").as_int();
	//size of the game world
	widthWorld = tilesInMapWidth * tileWidth;
	heightWorld = tilesInMapHeight * tileHeight;

	//create tileset
	tileSetWidth = rootNode.child("tileset").child("image").attribute("width").as_float();
	tileSetHeight = rootNode.child("tileset").child("image").attribute("height").as_float();
	tileset = new TileSet(IDtex, tileWidth, tileHeight);
	int rowsTileSet = tileSetHeight / tileHeight;
	int colsTileSet = tileSetWidth / tileWidth;
	tileset->createTileSet(rowsTileSet, colsTileSet);

	this->readMatrixMap();
}

void TiledMap::readMatrixMap()
{
	auto layerNode = rootNode.child("layer");
	auto dataNote = layerNode.child("data");
	mapIndices = dataNote.first_child().value();
	//Take data into matrix map
	eraseAllSubStr(mapIndices, "\n");
	findAndReplaceAll(mapIndices, ",", " ");
	std::string line;
	matrixMap = new std::string*[tilesInMapHeight];
	for (int i = 0; i < tilesInMapHeight; i++)
	{
		matrixMap[i] = new std::string[tilesInMapWidth];
	}
	int row = 0;
	int col = 0;
	std::stringstream spliter;
	spliter << mapIndices;
	while (!spliter.eof())
	{
		std::string str;
		spliter >> str;
		matrixMap[row][col] = str;
		col++;
		if (col >= tilesInMapWidth)
		{
			col = 0;
			row++;
		}
	}
}

std::vector<ObjectInfo*> TiledMap::getObjectInfo()
{
	for (auto objectGroupNode : rootNode.children("objectgroup"))
	{
		for (auto objectNode : objectGroupNode.children("object"))
		{
			int id = objectNode.attribute("id").as_int();
			std::string objectType = objectGroupNode.attribute("name").as_string();
			std::string name = objectNode.attribute("name").as_string();
			float x = objectNode.attribute("x").as_float();
			float y = objectNode.attribute("y").as_float() + EXTRA_HEIGHT_SCREEN;
			int width = objectNode.attribute("width").as_int();
			int height = objectNode.attribute("height").as_int();
			auto properties = objectNode.child("properties");
			std::string idHiddenItemString = properties.first_child().attribute("value").as_string();
			std::string objectId = properties.last_child().attribute("value").as_string();
			ObjectInfo* info_object = new ObjectInfo(id, name, height, width, D3DXVECTOR2(x, y), idHiddenItemString, objectId);
			objectInfo.push_back(info_object);
		}
	}
	return objectInfo;
}

void TiledMap::draw(Viewport* viewport)
{
	int beginCol = viewport->getX() / tileWidth;
	int endCol = viewport->getX() + viewport->getWidth() / tileWidth + 1;
	int beginRow = viewport->getY() / tileHeight;
	int endRow = viewport->getY() + viewport->getHeight() / tileHeight + 1;

	beginCol = (beginCol < 0) ? 0 : ((beginCol > (tilesInMapWidth)) ? (tilesInMapWidth) : beginCol);
	endCol = (endCol < 0) ? 0 : ((endCol > (tilesInMapWidth)) ? (tilesInMapWidth) : endCol);
	beginRow = (beginRow < 0) ? 0 : ((beginRow > (tilesInMapHeight)) ? (tilesInMapHeight) : beginRow);
	endRow = (endRow < 0) ? 0 : ((endRow > (tilesInMapHeight)) ? (tilesInMapHeight) : endRow);

	for (int row = beginRow; row < endRow; row++)
	{
		for (int col = beginCol; col < endCol; col++)
		{
			auto tile = tileset->getPositionTile(matrixMap[row][col]);
			worldPosition.x = tileWidth * col;
			worldPosition.y = tileHeight * row + EXTRA_HEIGHT_SCREEN;
			viewPosition = viewport->WorldToScreen(worldPosition);
			tile.Draw(viewPosition);
		}
	}
}

float TiledMap::getHeightWorld()
{
	return heightWorld;
}

float TiledMap::getWidthWorld()
{
	return widthWorld;
}

TiledMap::~TiledMap()
{
	delete tileset;

	for (int i = 0; i < tilesInMapHeight; i++)
		delete[] matrixMap[i];
	delete[] matrixMap;
}
