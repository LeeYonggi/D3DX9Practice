#include "DXUT.h"
#include "Ground.h"


Ground::Ground()
{
}


Ground::~Ground()
{
}

void Ground::Init()
{
	meshLoader = MESHMANAGER->AddObjMesh("Ground", L"./Resource/Background/Background.obj");
}

void Ground::Update()
{
}

void Ground::Render()
{
	MESHMANAGER->RenderMesh(meshLoader, { 0, 0, 0 });
}

void Ground::Release()
{
}
