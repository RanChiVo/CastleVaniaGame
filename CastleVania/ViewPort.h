#pragma once
#include <d3dx9.h>

class Viewport
{
protected:
	float x;
	float y;
	float width;
	float height;

public:

	Viewport(int x, int y, int width, int height);

	D3DXVECTOR2  WorldToScreen(D3DXVECTOR2 Object);

	D3DXVECTOR2  ScreenToWorld(D3DXVECTOR2 Object);

	D3DXVECTOR2	 GetPosition() { return D3DXVECTOR2(x, y); }

	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	
	float getWidth() { return width; }

	float getHeight() { return height; }

	float getX() { return x; }

	float getY(){ return y; }

	~Viewport();
};

