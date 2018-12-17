#include "DXUT.h"
#include "MainProc.h"


MainProc::MainProc()
{
}


MainProc::~MainProc()
{
}

void MainProc::Init()
{
	CAMERAMANAGER->Init();
	MESHMANAGER->AddMesh("bigship1", "./Resource/bigship1.X");
}

void MainProc::Update()
{
}

void MainProc::Render()
{
	MESHMANAGER->RenderMesh("bigship1");
}

void MainProc::Release()
{
	CameraManager::ReleaseInstance();
	MeshManager::ReleaseInstance();
}
