#include "DXUT.h"
#include "TpCamera.h"

#define ZOOMDISTANCE 2.5f
#define ZOOMDISTANCEX 3.0f
#define ZOOMDISTANCEY 1.5f

TpCamera::TpCamera(Object * _target)
{
	target = _target;
	current = { 0, 0 };

	m_Eye = { 0.0f, 0.0f, -13.0f };
	m_At = { 0, 0, 0 };
	
	prevQ = { 0, 0, 0, 1 };
	ShowCursor(false);

	distance = 3.5f;
	zoomDisX = 2;
	zoomDisY = 2;

	targetPos = target->GetPos();

	fixtargetoffset = Vector3(0.4f, 0.5f, -2.0f);
	fixpivotoffset = Vector3(0.0f, 2.0f, -2.0f);
}

TpCamera::~TpCamera()
{

}

void TpCamera::LerpToTarget()
{
	targetPos = d3d::Lerp<Vector3>(targetPos, target->GetPos(), 0.1f);
}

void TpCamera::LerpToZoom()
{
	targetPos = d3d::Lerp<Vector3>(targetPos, target->GetPos(), 0.1f);

	distance = d3d::Lerp<float>(distance, ZOOMDISTANCE, 0.1f);
	zoomDisX = d3d::Lerp<float>(zoomDisX, ZOOMDISTANCEX, 0.1f);
	zoomDisY = d3d::Lerp<float>(zoomDisY, ZOOMDISTANCEY, 0.1f);
}

D3DXVECTOR2 TpCamera::GetAxisMouse()
{
	RECT screenRe;
	GetWindowRect(DXUTGetHWND(), &screenRe);

	POINT center;
	center.x = (screenRe.right - screenRe.left) * 0.5f + screenRe.left;
	center.y = (screenRe.bottom - screenRe.top) * 0.5f + screenRe.top;

	POINT cursor;
	GetCursorPos(&cursor);

	POINT deltaCursor;
	deltaCursor.x = cursor.x - center.x;
	deltaCursor.y = cursor.y - center.y;

	current.x += deltaCursor.x * 0.0005f;
	current.y += deltaCursor.y * 0.0005f;

	if (current.y > D3DX_PI * 0.25f)
	{
		current.y = D3DX_PI * 0.25f;
	}
	if (current.y < -D3DX_PI * 0.25f)
	{
		current.y = -D3DX_PI * 0.25f;
	}

	SetCursorPos(center.x, center.y);

	return current;
}

void TpCamera::QuaternionLerpCam()
{
	if (INPUTMANAGER->IsKeyPress(VK_RBUTTON))
		LerpToZoom();
	else
		LerpToTarget();
	RECT screenRe;
	GetWindowRect(DXUTGetHWND(), &screenRe);
	POINT center;
	center.x = (screenRe.right - screenRe.left) * 0.5f + screenRe.left;
	center.y = (screenRe.bottom - screenRe.top) * 0.5f + screenRe.top;

	POINT cursor;
	GetCursorPos(&cursor);

	POINT deltaCursor;
	deltaCursor.x = cursor.x - center.x;
	deltaCursor.y = cursor.y - center.y;

	current.x -= deltaCursor.y * 0.0002f;
	current.y += deltaCursor.x * 0.0002f;

	if (current.x > 0)
	{
		current.x = 0;
	}
	if (current.x < -D3DX_PI * 0.5f)
	{
		current.x = -D3DX_PI * 0.5f;
	}

	m_Eye = Vector3(0, 0, distance);
	D3DXMATRIX cMatR, cMatX, cMatY;
	D3DXMatrixRotationX(&cMatX, current.x);
	D3DXMatrixRotationY(&cMatY, current.y);
	cMatR = cMatX * cMatY;

	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, &cMatR);
	D3DXQuaternionSlerp(&prevQ, &prevQ, &currQ, 0.1f);
	D3DXMATRIX mRQ;
	D3DXMatrixRotationQuaternion(&mRQ, &prevQ);
	D3DXVec3TransformCoord(&m_Eye, &m_Eye, &mRQ);

	m_Eye += targetPos;
	m_Eye.y += 1;
	//m_At = targetPos;
	//m_At.y += 1;
	D3DXVECTOR3 _disFromTarget = m_Eye - targetPos;

	D3DXVec3Normalize(&_disFromTarget, &_disFromTarget);
	D3DXVec3Cross(&_disFromTarget, &_disFromTarget, &m_Up);
	m_At = targetPos + _disFromTarget * zoomDisX;
	m_At.y = current.x * D3DX_PI;

	Camera::Init();
	SetCursorPos(center.x, center.y);
}

void TpCamera::TargetOffsetCam()
{
	LerpToTarget();
	GetAxisMouse();
	D3DXMATRIX matH, matV;
	D3DXMatrixRotationY(&matH, current.x);
	D3DXMatrixRotationX(&matV, -current.y);
	matV *= matH;

	D3DXQUATERNION camYRotation, aimRotation;
	D3DXQuaternionRotationMatrix(&camYRotation, &matH);
	D3DXQuaternionRotationMatrix(&aimRotation, &matV);

	Vector3 noCollisionOffset = fixtargetoffset;
	Vector3 targetPivotOffset = fixpivotoffset;
	D3DXVec3TransformCoord(&noCollisionOffset, &noCollisionOffset, &matV);
	D3DXVec3TransformCoord(&targetPivotOffset, &targetPivotOffset, &matH);
	m_Eye = targetPos + noCollisionOffset + targetPivotOffset;

	RECT rect;
	GetClientRect(M_HWND, &rect);

	D3DXMATRIX vMat, vMatR;
	//D3DXVec3TransformCoord(&m_At, &m_At, &matH);
	Vector3 targetPivot = Vector3(3, 0, 0);
	D3DXVec3TransformCoord(&targetPivot, &targetPivot, &matH);
	m_At = targetPos + targetPivot;
	m_At.y = current.y * D3DX_PI;
	D3DXMatrixLookAtLH(&vMat, &m_Eye, &m_At, &m_Up);

	DEVICE->SetTransform(D3DTS_VIEW, &vMat);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI * 0.5f, (float)SCREEN_X / (float)SCREEN_Y, 1.0f, 100000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);
}

void TpCamera::CamUpdate()
{
	TargetOffsetCam();
	//QuaternionLerpCam();
}
