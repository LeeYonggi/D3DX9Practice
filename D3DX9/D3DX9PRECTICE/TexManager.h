#pragma once
#include "Singleton.h"

struct Texture
{
	LPDIRECT3DTEXTURE9 tex;
	D3DXIMAGE_INFO info;
};

class TexManager :
	public Singleton<TexManager>
{
public:
	TexManager();
	virtual ~TexManager();
private:
	map<string, Texture*> mTexture;

public:
	Texture *AddTexture(string str, string route);
	Texture *GetTexture(string str);
	void Release();
};

#define TEXMANAGER TexManager::GetInstance()