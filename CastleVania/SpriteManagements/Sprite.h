#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <string.h>
#include <unordered_map>
#include "../DebugOut/DebugOut.h"
#include "../Direct3DManager.h"

class Sprite
{
private:
	std::string id;
	RECT rect;
	LPDIRECT3DTEXTURE9 texture;

public:
	Sprite();

	Sprite(std::string id, RECT r, LPDIRECT3DTEXTURE9 tex);
	
	void SetRECT( RECT r);

	RECT getRect();
		
	void Draw(D3DXVECTOR2 position);
};

typedef Sprite * LPSPRITE;
