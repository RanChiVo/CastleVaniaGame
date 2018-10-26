#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "../SpriteManagements/Sprite.h"
#include <string>

using namespace std;


class AnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	AnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef AnimationFrame *LPANIMATION_FRAME;

class Animation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	Animation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(std::string  spriteId, DWORD time = 0);
	void Render(float x, float y);
};

typedef Animation *LPANIMATION;
