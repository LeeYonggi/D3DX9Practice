#pragma once
#include "Camera.h"

class TpCamera :
	public Camera
{
public:
	TpCamera(Object *_target);
	virtual ~TpCamera();
private:
	Object *target;
	Vector3 targetPos;
	Vector3 smoothPivot;
	Vector3 fixtargetoffset;
	Vector3 fixpivotoffset;
	float distance;
	D3DXVECTOR2 current;
	D3DXQUATERNION prevQ;
	float zoomDisX;
	float zoomDisY;

public:
	void LerpToTarget();
	void LerpToZoom();
	D3DXVECTOR2 GetAxisMouse();
	void QuaternionLerpCam();
	void TargetOffsetCam();
	virtual void CamUpdate() override;

public:
	Vector3 GetTargetPos() { return targetPos; }
};

