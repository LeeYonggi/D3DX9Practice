#include "DXUT.h"
#include "TpCamera.h"


TpCamera::TpCamera(Object * _target)
{
	target = _target;
	distance = 10.0f;
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

	Vector3 dir = Vector3(0, 0, -distance);
	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, );

	SetCursorPos(center.x, center.y);
}
