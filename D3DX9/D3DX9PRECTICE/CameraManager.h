#pragma once

class CameraManager
	: public Singleton<CameraManager>
{
public:
	CameraManager();
	virtual ~CameraManager();

private:
	D3DXVECTOR3 m_Eye, m_At, m_Up;
	float degree;
	float upDegree;

public:
	void Init();
	void Translate(D3DXVECTOR3 eye, D3DXVECTOR3 at);
	void SetPosition(Vector3 eye, Vector3 at);
	void SetCamera();
	void RotationToChar(Object *obj);
};

#define CAMERAMANAGER CameraManager::GetInstance()