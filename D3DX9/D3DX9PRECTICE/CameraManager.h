#pragma once
class CameraManager
	: public Singleton<CameraManager>
{
public:
	CameraManager();
	virtual ~CameraManager();

private:

	D3DXVECTOR3 m_Eye, m_At, m_Up;

public:
	void Init();
	void SetCamera();
};

#define CAMERAMANAGER CameraManager::GetInstance()