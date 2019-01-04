#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
	m_Eye = { 4.0f, 4.0f, -13.0f };
	m_At = { 0, 0, 0 };
	m_Up = { 0, 1.0f, 0 };
}


CameraManager::~CameraManager()
{
}

void CameraManager::Init()
{
	RECT rect;

	GetClientRect(M_HWND, &rect);

	D3DXMATRIX vMat;
	D3DXMatrixLookAtLH(&vMat, &m_Eye, &m_At, &m_Up);

	DEVICE->SetTransform(D3DTS_VIEW, &vMat);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI * 0.5f, (float)SCREEN_X / (float)SCREEN_Y, 1.0f, 1000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CameraManager::Translate(D3DXVECTOR3 eye, D3DXVECTOR3 at)
{
	
	m_Eye += eye;
	m_At += at;

	Init();
}

void CameraManager::SetPosition(Vector3 eye, Vector3 at)
{
	m_Eye = eye;
	m_At = at;

	Init();
}

void CameraManager::SetCamera()
{
}
