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
	mesh = MESHMANAGER->AddMesh("bigship1.X", "./Resource/");
}

void MainProc::Update()
{
}

void MainProc::Render()
{
	int numFaces = mesh->pmesh->GetNumFaces();
	if (GetAsyncKeyState('A') & 0x8000)
	{
		mesh->pmesh->SetNumFaces(numFaces + 10);
		if(mesh->pmesh->GetNumFaces() == numFaces)
			mesh->pmesh->SetNumFaces(numFaces + 20);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		mesh->pmesh->SetNumFaces(numFaces - 10);
	}
	MESHMANAGER->RenderMesh("bigship1.X");
}

void MainProc::Release()
{
	CameraManager::ReleaseInstance();
	MeshManager::ReleaseInstance();
}
