#include "Textures.h"

Textures *Textures::__instance = nullptr;

void Textures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}
	//Initialize Direct 3DDevice thought Game->CastleVania
	LPDIRECT3DDEVICE9 d3ddv = Direct3DManager::getInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		nullptr,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	textures[id] = texture;

	DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s \n", id, filePath);
}

std::pair<int, int> Textures::GetSizeObject(int id)
{
	return sizeObject.at(id);
}

void Textures::setSizeObject(int id, int widthObject, int heightObject)
{
	sizeObject.emplace(id, std::make_pair(widthObject, heightObject));
}

LPDIRECT3DTEXTURE9 Textures::Get(unsigned int i)
{
	return textures[i];
}

void Textures::Clear()
{
	for (auto x : textures)
	{
		LPDIRECT3DTEXTURE9 tex = x.second;
		if (tex != NULL) tex->Release();
	}

	textures.clear();
}

Textures * Textures::GetInstance()
{
	if (__instance == nullptr) __instance = new Textures();
	return __instance;
}
