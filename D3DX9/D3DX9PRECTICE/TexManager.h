#pragma once
#include "Singleton.h"

struct Texture
{
	LPDIRECT3DTEXTURE9 tex;
	D3DXIMAGE_INFO info;
};

struct Color
{
	int r, g, b, a;
	Color(int _r, int _g, int _b, int _a)
		: r(_r), g(_g), b(_b), a(_a)
	{

	}
	Color() { }
};

class TexManager :
	public Singleton<TexManager>
{
public:
	TexManager();
	virtual ~TexManager();
private:
	map<string, Texture*> mTexture;
	LPD3DXSPRITE sprite;

public:
	Texture *AddTexture(string str, string route);
	vector<Texture*> AddAnimeTexture(string route, int low, int high);
	Texture *GetTexture(string str);
	void RenderSprite(Texture *tex, Vector2 pos, Vector2 src, Vector2 scale = Vector2( 1, 1 ), 
		float rotation = 0,
		Color color = Color(255, 255, 255, 255));
	void Release();
};

#define TEXMANAGER TexManager::GetInstance()