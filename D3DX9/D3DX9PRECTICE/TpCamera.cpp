#include "DXUT.h"
#include "TpCamera.h"

#define ZOOMDISTANCE 2.5f
#define ZOOMDISTANCEX 3.0f
#define ZOOMDISTANCEY 1.5f

TpCamera::TpCamera(Object * _target)
{
	target = _target;
	current = { 0, 0 };

	m_Eye = { 4.0f, 4.0f, -13.0f };
	
	prevQ = { 0, 0, 0, 1 };
	ShowCursor(false);

	distance = 3.5f;
	zoomDisX = 2;
	zoomDisY = 2;

	targetPos = target->GetPos();
}

TpCamera::~TpCamera()
{

}

void TpCamera::LerpToTarget()
{
	targetPos = d3d::Lerp<Vector3>(targetPos, target->GetPos(), 0.1f);

	distance = d3d::Lerp<float>(distance, 3.5f, 0.1f);
	zoomDisX = d3d::Lerp<float>(zoomDisX, 2, 0.1f);
	zoomDisY = d3d::Lerp<float>(zoomDisY, 2, 0.1f);
}

void TpCamera::LerpToZoom()
{
	targetPos = d3d::Lerp<Vector3>(targetPos, target->GetPos(), 0.1f);

	distance = d3d::Lerp<float>(distance, ZOOMDISTANCE, 0.1f);
	zoomDisX = d3d::Lerp<float>(zoomDisX, ZOOMDISTANCEX, 0.1f);
	zoomDisY = d3d::Lerp<float>(zoomDisY, ZOOMDISTANCEY, 0.1f);
}

void TpCamera::CamUpdate()
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
	m_At.y += zoomDisY;

	Camera::Init();
	SetCursorPos(center.x, center.y);
}
