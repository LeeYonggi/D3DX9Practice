#include "DXUT.h"
#include "Ground.h"


Ground::Ground()
{
	scale = { 0.1, 0.1, 0.1 };
	memset(mapArray, 0, sizeof(mapArray));

	for (int i = 0; i < MAPARRAYSIZE; i++)
	{
		mapArray[i][0] = 1;
	}
}


Ground::~Ground()
{
}

void Ground::Init()
{
	meshLoader = MESHMANAGER->AddObjMesh("Ground", L"./Resource/Map/Stage1/Background.obj");
}

void Ground::Update()
{
}

void Ground::Render()
{
	MESHMANAGER->RenderMesh(meshLoader, { 0, 0, 0 }, { 0, 0, 0 }, scale);
}

void Ground::Release()
{
}

D3DXVECTOR2 Ground::CollisionToArray(D3DXVECTOR2 target)
{

	return D3DXVECTOR2();
}
