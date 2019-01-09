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
	float distance;
	D3DXVECTOR2 current;
	D3DXQUATERNION prevQ;
	float zoomDisX;
	float zoomDisY;

public:
	virtual void CamUpdate() override;
};

