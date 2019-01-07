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

public:
	virtual void CamUpdate() override;
};

