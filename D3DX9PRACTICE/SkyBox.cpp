#include "DXUT.h"
#include "SkyBox.h"


SkyBox::SkyBox()
{
	scale = { 1, 1, 1 };
	pos = { 0, 0, 0 };
}


SkyBox::~SkyBox()
{
}

void SkyBox::Init()
{
	meshLoader = MESHMANAGER->AddObjMesh("skyBox", L"./Resource/SkyBox/skybox.obj");

}

void SkyBox::Update()
{
	pos = CAMERAMANAGER->GetEye();
}

void SkyBox::Render()
{
	DEVICE->SetRenderState(D3DRS_ZENABLE, false);
	MESHMANAGER->RenderMesh(meshLoader, pos, rotation, scale);
	DEVICE->SetRenderState(D3DRS_ZENABLE, true);
}

void SkyBox::Release()
{

}
