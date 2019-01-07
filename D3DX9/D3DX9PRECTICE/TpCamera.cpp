#include "DXUT.h"
#include "TpCamera.h"


TpCamera::TpCamera(Object * _target)
{
	target = _target;
	distance = 10.0f;
	current = { 0, 0 };

	prevQ = { 0, 0, 0, 1 };
	ShowCursor(false);
}

TpCamera::~TpCamera()
{

}

void TpCamera::CamUpdate()
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

	current.x -= deltaCursor.y * 0.0002f;
	current.y += deltaCursor.x * 0.0002f;

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

	m_Eye += target->GetPos();
	m_Eye.y += 1;
	m_At = target->GetPos();
	m_At.y += 1;

	Camera::Init();
	SetCursorPos(center.x, center.y);
}
