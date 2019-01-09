#include "DXUT.h"
#include "TexManager.h"


TexManager::TexManager()
{
}


TexManager::~TexManager()
{
	Release();
}

Texture * TexManager::AddTexture(string str, string route)
{
	auto iter = mTexture.find(str);
	if (iter != mTexture.end()) iter->second;
	
	Texture *tex = new Texture;
	D3DXCreateTextureFromFileExA(DEVICE, 
		route.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, 0,
		D3DFMT_A8B8G8R8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		NULL, 
		&tex->info, 
		0, 
		&tex->tex);

	mTexture.insert(make_pair(str, tex));
	
	return tex;
}

Texture * TexManager::GetTexture(string str)
{
	auto iter = mTexture.find(str);
	if (iter == mTexture.end()) nullptr;
	return iter->second;
}

void TexManager::Release()
{
	for (auto iter : mTexture)
	{
		SAFE_RELEASE(iter.second->tex);
		SAFE_DELETE(iter.second);
	}
	mTexture.clear();
}
