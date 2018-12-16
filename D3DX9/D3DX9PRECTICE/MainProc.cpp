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
	MESHMANAGER->AddMesh("aa");
}

void MainProc::Update()
{
}

void MainProc::Render()
{
	MESHMANAGER->RenderMesh("aa");
}

void MainProc::Release()
{
	CameraManager::ReleaseInstance();
	MeshManager::ReleaseInstance();
}
