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
	
	sphere = new Mesh;
	spherePosition = { 0, 0, 0 };
	float radius;
	MESHMANAGER->CreateBoundingSphere(mesh, &spherePosition, &radius);
	D3DXCreateSphere(
		DEVICE,
		radius,
		20,
		20,
		&sphere->mesh,
		0
	);
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

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	sphere->mesh->DrawSubset(0);
}

void MainProc::Release()
{
	sphere->mesh->Release();
	CameraManager::ReleaseInstance();
	MeshManager::ReleaseInstance();
}

void MainProc::ClockInit()
{

}

void MainProc::ClockUpdate()
{
}

void MainProc::ClockRender()
{
}
