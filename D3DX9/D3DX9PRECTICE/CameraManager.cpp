#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
	m_Eye = { 4.0f, 4.0f, -13.0f };
	m_At = { 0, 0, 0 };
	m_Up = { 0, 1.0f, 0 };
	degree = 0.0f;
	upDegree = 0.0f;
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
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI * 0.5f, (float)SCREEN_X / (float)SCREEN_Y, 1.0f, 100000.0f);
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

void CameraManager::RotationToChar(Object * obj)
{
	RECT wRect;
	GetWindowRect(DXUTGetHWND(), &wRect);
	POINT center = { wRect.left + SCREEN_X * 0.5, wRect.top + SCREEN_Y * 0.5 };
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(DXUTGetHWND(), &cursor);

	if (cursor.x > SCREEN_X * 0.5f - 7)
	{
#pragma region Cross Product
		//D3DXVECTOR3 nUp, nDir, nLeft;
		//D3DXVec3Normalize(&nUp, &m_Up);
		//D3DXVec3Normalize(&nDir, &(m_At - m_Eye));
		//D3DXVec3Cross(&nLeft, &nUp, &nDir);
		//m_Eye += nLeft;
#pragma endregion
		degree += 2;
	}
	if (cursor.x < SCREEN_X * 0.5f - 10)
	{
#pragma region Cross Product
		//D3DXVECTOR3 nUp, nDir, nRight;
		//D3DXVec3Normalize(&nUp, &m_Up);
		//D3DXVec3Normalize(&nDir, &(m_At - m_Eye));
		//D3DXVec3Cross(&nRight, &nUp, &nDir);
		//m_Eye -= nRight;
#pragma endregion
		degree -= 2;
	}
	if (cursor.y > SCREEN_Y * 0.5f - 31)
	{
		//m_Eye.y += 0.05f;
	}
	if (cursor.y < SCREEN_Y * 0.5f - 31)
	{
		//m_Eye.y -= 0.05f;
	}
	m_At = { obj->GetPos().x, obj->GetPos().y + 3, obj->GetPos().z };
	m_Eye.x = sin(D3DXToRadian(degree)) * 3 + obj->GetPos().x;
	m_Eye.z = cos(D3DXToRadian(degree)) * 3 + obj->GetPos().z;
	
	//m_Eye.y = cos(D3DXToRadian(upDegree)) * 3 + obj->GetPos().y;

	SetCursorPos((int)center.x, (int)center.y);
	D3DXMATRIX cMatT, cMatRX, cMatRY, cMatRZ;
	D3DXMatrixTranslation(&cMatT, obj->GetPos().x, obj->GetPos().y, obj->GetPos().z);
	D3DXMatrixRotationX(&cMatRX, obj->GetRotation().x);
	D3DXMatrixRotationY(&cMatRY, obj->GetRotation().y);
	D3DXMatrixRotationZ(&cMatRZ, obj->GetRotation().z);

	//Init
	RECT rect;

	GetClientRect(M_HWND, &rect);

	D3DXMATRIX vMat;
	D3DXMatrixLookAtLH(&vMat, &m_Eye, &m_At, &m_Up);

	DEVICE->SetTransform(D3DTS_VIEW, &vMat);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI * 0.5f, (float)SCREEN_X / (float)SCREEN_Y, 1.0f, 100000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);
}
