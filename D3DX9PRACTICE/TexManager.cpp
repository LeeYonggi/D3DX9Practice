#include "DXUT.h"
#include "TexManager.h"


TexManager::TexManager()
{
	D3DXCreateSprite(DEVICE, &sprite);
}


TexManager::~TexManager()
{
	Release();
}

Texture * TexManager::AddTexture(string str, string route)
{
	auto iter = mTexture.find(str);
	if (iter != mTexture.end()) return iter->second;
	
	Texture *tex = new Texture;
	D3DXCreateTextureFromFileExA(DEVICE, 
		route.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		0, 0,
		D3DFMT_A8B8G8R8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		NULL, 
		&tex->info, 
		0, 
		&tex->tex);

	mTexture.insert(make_pair(str, tex));
	
	return tex;
}

vector<Texture*> TexManager::AddAnimeTexture(string route, int low, int high)
{
	vector<Texture*> vTexture;

	for (int i = low; i < high; i++)
	{
		CHAR ctr[64];
		sprintf(ctr, route.c_str(), i);
		Texture *temp = AddTexture(ctr, ctr);
		vTexture.push_back(temp);
	}
	return vTexture;
}

Texture * TexManager::GetTexture(string str)
{
	auto iter = mTexture.find(str);
	if (iter == mTexture.end()) nullptr;
	return iter->second;
}

void TexManager::RenderSprite(Texture *tex, Vector2 pos, Vector2 src, Vector2 scale, float rotation, Color color)
{
	D3DXMATRIX matW, matT, matR, matS;
	D3DXMatrixScaling(&matS, scale.x, scale.y, 1);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rotation));
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	matW = matS * matR * matT;

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->SetTransform(&matW);

	Vector3 center = { (float)tex->info.Width * 0.5f, (float)tex->info.Height * 0.5f, 0 };
	RECT srcRect = { 0, 0, (float)tex->info.Width * src.x, (float)tex->info.Height * src.y };

	sprite->Draw(tex->tex, &srcRect, &center, nullptr, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));

	sprite->End();
}

void TexManager::Release()
{
	for (auto iter : mTexture)
	{
		if (iter.second)
			iter.second->tex->Release();
		SAFE_DELETE(iter.second);
	}
	mTexture.clear();

	sprite->Release();
}
