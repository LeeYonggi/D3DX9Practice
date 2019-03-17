#pragma once

#include "Camera.h"

class CameraManager
	: public Singleton<CameraManager>
{
public:
	CameraManager();
	virtual ~CameraManager();

private:
	Camera *nowCamera;

public:
	void Init(Camera *nextCamera);
	void Translate(D3DXVECTOR3 eye, D3DXVECTOR3 at);
	void SetPosition(Vector3 eye, Vector3 at);
	void SetCamera();
	void CamUpdate();
	void RotationToChar(Object *obj);

	Vector3 GetEye() { if(nowCamera) return nowCamera->GetEye(); }
	Vector3 GetAt()	 { if(nowCamera) return nowCamera->GetAt(); }
	Vector3 GetUp()  { if(nowCamera) return nowCamera->GetUp(); }
	Camera *GetCamera() { return nowCamera; }
};

#define CAMERAMANAGER CameraManager::GetInstance()