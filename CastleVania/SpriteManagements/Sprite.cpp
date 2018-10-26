#include "Sprite.h"
#include "../CastleVania.h"

Sprite::Sprite(std::string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

void Sprite::Draw(float x, float y)
{
	CastleVania * game = CastleVania::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom);
}