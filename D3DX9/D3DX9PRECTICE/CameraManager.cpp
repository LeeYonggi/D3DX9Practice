#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
}

void CameraManager::Init()
{
	RECT rect;

	GetClientRect(M_HWND, &rect);

	m_Eye = { 4.0f, 4.0f, -13.0f };
	m_At  = { 0, 0, 0 };
	m_Up  = { 0, 1.0f, 0 };

	D3DXMATRIX vMat;
	D3DXMatrixLookAtLH(&vMat, &m_Eye, &m_At, &m_Up);

	DEVICE->SetTransform(D3DTS_VIEW, &vMat);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI * 0.5f, (float)SCREEN_X / (float)SCREEN_Y, 1.0f, 100.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CameraManager::SetCamera()
{
}
